#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

//structure of the node
struct address_t{
 int octet[4];
 char alias[11];
 struct address_t *leftChild, *rightChild, *parent;
 int height, depth;
};

struct address_t *head = NULL;

struct address_t *newNode(char* line){
 struct address_t *temp = (struct address_t *)malloc(sizeof(struct address_t));
 if(temp == NULL){
  printf("\nNode creation failed\n");
  return NULL;
 }
 
 sscanf(line, "%d.%d.%d.%d %s", temp->octet,temp->octet+1,temp->octet+2,temp->octet+3,temp->alias)
 temp->height = 0;
 temp->depth = 0 ;
 temp->leftChild = temp->rightChild = NULL;
 return temp; 
}

void inOrder(struct address_t *root){
 if(root != NULL){
  inOrder(root->leftChild);
  printf("%s %s", root->octet,root->alias,root->height, root->depth);
  inOrder(root->rightChild);
 }
}

struct address_t* insert(struct address_t* node, char* line){
 if(node == NULL)
  return newNode(line);
 if(key < node->key)
  node->leftChild = insert(node->leftChild, line);
 else
  node->rightChild = insert(node->rightChild, line);
 return node; 
}

struct address_t *minValueNode(struct addres_t* node){
 struct address_t* current = node;
 while(current && current->leftChild != NULL)
  current = current->left;
 return current;
}

//1. adding address tot he BST
void addAddress(struct address_t* root){
 char alias[11];
 char ipAddress[20];
 int b[4] = {0};
 printf("\tEnter alias: ");
 scanf("%s",alias);

 struct address_t *ptr = root;
 while(ptr!=NULL){
  if(strcmp(ptr->alias,alias)== 0){
   printf("\terror: %s already exists");
   return;
  }
  ptr=ptr->next;
 }
 int flag = 1;
 while(flag){
  printf("\tEnter IP address for %s: ",alias);
  scanf("%s",ipAddress);
  sscanf(ipAddress, "%d.%d.%d.%d %s",b, b+1, b+2, b+3,alias );

  bool isIPDuplicate = checkIfIPAlreadyExist(b) ;
  //validating the IP address values
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
    flag = 0;
  }else{
    return;
  }
 }
 char line[40];
 strcpy(line, ipAddress);
 strcat(line," ");
 strcat(line,alias);
 insert(root,line)
}

bool checkIfIPAlreadyExist(int *val){
 struct address_t *ptr2 = head;
 bool flag2 = false;
 int count = 0;

 if(!flag2){
  while(ptr2 != NULL){
   for(int i = 0; i < 4; i++)
    if(ptr2->octet[0]== val[0])
	   count++;
   ptr2 = ptr2->next;
  }
  if(count == 4){
   printf("\terror: newly entered address is duplicate\n");
   return true;
  }
 }
 return false;
}

//2. display the address of the corresponding alias
void lookUpAddress(struct address_t* root ){
 char alias[20];
 
 int flag =0;
 printf("\tEnter alias: ");
 scanf("%s",alias);
 struct address_t *ptr = head;
 flag = inOrderSearch(root,alias); 

 //if alias does not exist
 if(flag == 0)
  printf("\terror: %s does not exist\n",alias);
}

int inOrderSearch(struct address_t* root, char[] alias){
 if(roor != NULL){
  inOrderSearch(root->left);
  if(strcmp(ptr->alias,alias)== 0){
   printf("\tAddress for the %s: %d.%d.%d.%d\n",root->alias, root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
   return 1;
  }
  inOrderSearch(root->right);
 }
}

//8. To quit the application
void quit(){
 printf("\nGood bye!\n");
}

int main(){
 struct address_t *root = NULL;
 char file_name[25];
 FILE *fp;

 strcpy(file_name,"CS531_Inet.txt");
 fp = fopen(file_name,"r");

 if(fp == NULL){
  perror("Error while opening the file.\n");
  exit(EXIT_FAILURE);
 }

 char line[100];
 while(fgets(line,MAX_LINE_LENGTH,fp)){
  root = insert(root, line);
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
  scanf("%d",&menu_option);

  switch(menu_option){
   case 1:
	addAddress(root);
        break;
   case 2:
	lookUpAddress(root);
        break;
   case 3:
	updateAddress();
        break;
   case 4:
	deleteAddress();
        break;
   case 5:
	displayList();
        break;
   case 6:
	displayAliasForLocation();
	break;
   case 7:
        saveToFile();
	break;
   case 8:
	flag = 0;
	break;
   default:
	{
		printf("\nInvalid Input\n");
		flag=0;
	}

  }
 }
 
 fclose(fp);
 return 0;
}
