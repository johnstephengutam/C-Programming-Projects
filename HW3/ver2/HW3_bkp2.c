#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_LINE_LENGTH 50

struct address_t{
 int octet[4];
 char alias[11];
 int height;
 int depth;
 struct address_t* left;
 struct address_t* right;
 struct address_t* parent;
};

struct address_t* newNode(char* line){
 struct address_t *ptr = (struct address_t *)malloc(sizeof(struct address_t));
 
 sscanf(line,"%d.%d.%d.%d %s",ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->octet+4);
 ptr->left=ptr->right=ptr->parent=NULL;
 return ptr;
}


char* aliasExtract(char* line){
 char *str = strchr(line,' ');
 return str;
}

struct address_t* add_to_tree(struct address_t* node, char* line){
 if(node == NULL) 
  return newNode(line);

 /*char *tempalias;
 if(line!=NULL){
  tempalias = strchr(line,' ');
 }*/

 if(strcmp(aliasExtract(line)/*tempalias*/,node->alias) > 0)
  node->left = add_to_tree(node->left, line);
 else
  node->right = add_to_tree(node->right, line);
 return node;
}

void aliasAlreadyExist(struct address_t* root,char* alias, int* flag){
 if(root!=NULL){
  aliasAlreadyExist(root->left, alias, flag);
  if(strcmp(root->alias,alias)==0){
   *flag = 1;
  }
  aliasAlreadyExist(root->right, alias,  flag);
 }
}

void ipAlreadyExists(struct address_t* root, int* count, int *val){
 if(root!=NULL){
  ipAlreadyExists(root->left, count, val);
  if((root->octet[0]== val[0]) && (root->octet[1]== val[1]) && (root->octet[2]== val[2]) && (root->octet[3]== val[3])){
   *count = 4;
  }
  ipAlreadyExists(root->right, count,  val);
 } 
}

bool checkIfIPAlreadyExist(struct address_t* root, int *val){
 struct address_t *ptr = root;
 bool flag = false;
 int count = 0;

 if(!flag){
  ipAlreadyExists(root,&count,val);  
  if(count == 4){
   printf("\terror: newly entered address is duplicate\n");
   return true;
  }
 }
 return false;
}

//1. Adding address to the linked list
void addAddress(struct address_t* root){
 char alias[11];
 char ipAddress[20];
 int b[4] = {0};
 printf("\tEnter alias: ");
 scanf("%s", alias);

 //check if this alias already exists in BST or not
 struct address_t *ptr = root;
 int flag1 = 0 ;
 aliasAlreadyExist(ptr,alias,  &flag1); 
 if(flag1 == 1)
  printf("\terror: %s already exists", alias);
 
 int flag2 = 1;
 while(flag2){
  printf("\tEnter IP address for %s: ", alias);
 
  scanf("%s",ipAddress);
  sscanf(ipAddress, "%d.%d.%d.%d %s",b, b+1, b+2, b+3,alias );

  bool isIPDuplicate = checkIfIPAlreadyExist(root, b) ;
  if(!isIPDuplicate){
   if(b[0] < 0 || b[0] > 255)
    printf("\terror: %s is an illegal address- please reenter\n",ipAddress);
   else if(b[1] < 0 || b[1] > 255)
    printf("\terror: %s is an illegal address- please reenter\n",ipAddress);
   else if(b[2] < 0 || b[2] > 255)
    printf("\terror: %s is an illegal address- please reenter\n",ipAddress);
   else if(b[3] < 0 || b[3] > 255)
    printf("\terror: %s is an illegal address- please reenter\n",ipAddress);
   else
    flag2 = 0;
  }else{
    return;
  }
 }
 char line[40];
 strcpy(line, ipAddress);
 strcat(line," ");
 strcat(line,alias);
 add_to_tree(root,line);
}

void aliasAlreadyExist_lookupaddress(struct address_t* root,char* alias, int* flag){
 if(root!=NULL){
  aliasAlreadyExist(root->left, alias, flag);
  printf("%s", root->alias);
 // if(strcmp(root->alias,alias)==0){
  // printf("\tAddress for the %s: %d.%d.%d.%d\n",root->alias, root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
 // }
  aliasAlreadyExist(root->right, alias, flag);
 }
}

//2. Display the address of the corresponding alias
void lookUpAddress(struct address_t* root){
 char alias[20];
 int flag = 0;
 printf("\tEnter alias: ");
 scanf("%s",alias);
 struct address_t *ptr = root;

 aliasAlreadyExist_lookupaddress(ptr,alias,&flag);
 
 //if alias does not exist
 if(flag ==0)
  printf("\terror: %s does not exist\n",alias);
}

//5. Displaying the tree inorder trversal
void display(struct address_t *root){
 if(root!=NULL){
  display(root->left);
   printf("\t%s: %d.%d.%d.%d\n",root->alias, root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
  display(root->right);
 }
}

//8. To quit the application
void quit(){
 printf("\nGood bye!\n");
}

int main(){
 struct address_t* root = NULL;
 char file_name[25];
 FILE *fp;
 strcpy(file_name,"CS531_Inet.txt");
 fp = fopen(file_name,"r");

 if(fp == NULL){
  perror("Error while opening the file. \n");
  exit(EXIT_FAILURE);
 }
 
 char line[100];
 while(fgets(line, MAX_LINE_LENGTH,fp)){
  root = add_to_tree(root, line);  
 }

 int flag = 1;
 int menu_option;
 while(flag){
  printf("\n");
  printf("1) Add address\n");
  printf("2) Look up address\n");
  printf("3) Update address\n");
  printf("4) Delete address\n");
  printf("5) Display list\n");
  printf("6) Display aliases for location\n");
  printf("7) Save to file\n");
  printf("8) Quit\n");

  printf("\nEnter option: ");
  scanf("%d", &menu_option);

  switch(menu_option){
   case 1: addAddress(root);
	   break;
   case 2: lookUpAddress(root);
	   break;
   case 3:
	   break;
   case 4:
	   break;
   case 5:
	   display(root);
	   break;
   case 6:
	   break;
   case 7:
	   break;
   case 8:
	   flag = 0;
	   break;
   default:{
            printf("\nInvalid Input");
	    flag = 0;
	   }
  }
 } 
 fclose(fp);
 return 0;
}
