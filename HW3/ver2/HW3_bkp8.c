#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_LINE_LENGTH 50

struct address_t{
 int octet[4];
 char alias[30];
 int height;
 int depth;
 struct address_t* left;
 struct address_t* right;
 struct address_t* parent;
};

struct address_t* newNode(char* line){
 struct address_t *ptr = (struct address_t *)malloc(sizeof(struct address_t));
 
 if(ptr == NULL){
  printf("\nNode creation failed\n");
  return NULL;
 }

 sscanf(line,"%d.%d.%d.%d %s",ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->alias);
 
 ptr->left=ptr->right=ptr->parent=NULL;
 return ptr;
}

struct address_t* add_to_tree(struct address_t* root, char* line){
 if(root == NULL)
  return newNode(line);

 struct address_t *ptr = (struct address_t*)malloc(sizeof(struct address_t));
 sscanf(line, "%d.%d.%d.%d %s", ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->alias);

 int res = strcmp(ptr->alias,root->alias);
 if(res < 0)
  root->left = add_to_tree(root->left, line);
 else if(res > 0)
  root->right = add_to_tree(root->right, line);
  
 return root;
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

void ipAlreadyExists(struct address_t* root, int* flag, int *val){
 if(root!=NULL){
  ipAlreadyExists(root->left, flag, val);
  if((root->octet[0]== val[0]) && (root->octet[1]== val[1]) && (root->octet[2]== val[2]) && (root->octet[3]== val[3])){
   *flag = 1;
  }
  ipAlreadyExists(root->right, flag,  val);
 } 
}

int checkIfIPAlreadyExist(struct address_t* root, int *val){
 int flag = 0;
 ipAlreadyExists(root, &flag, val);

 if(flag == 1)
  printf("\terror: newly entered address is duplicate\n");

 return flag;
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
 if(flag1 == 1){
  printf("\terror: %s already exists", alias);
  return;
 }
 int flag2 = 1;
 while(flag2){
  printf("\tEnter IP address for %s: ", alias);

  scanf("%s",ipAddress);
  sscanf(ipAddress, "%d.%d.%d.%d %s",b, b+1, b+2, b+3,alias );

  int isIPDuplicate = checkIfIPAlreadyExist(root, b) ;
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
  aliasAlreadyExist_lookupaddress(root->left, alias, flag);
   if(strcmp(root->alias,alias) == 0){
    printf("\tAddress for the %s: %d.%d.%d.%d\n",root->alias,root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
    *flag = 1;
   }
  aliasAlreadyExist_lookupaddress(root->right, alias,flag);
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
 if(flag == 0)
  printf("\terror: %s does not exist\n",alias);
}

void ipAlreadyExists_Update(struct address_t* root, int* flag, int *val){
 if(root!=NULL){
  ipAlreadyExists(root->left, flag, val);
  if((root->octet[0]== val[0]) && (root->octet[1]== val[1]) && (root->octet[2]== val[2]) && (root->octet[3]== val[3])){
   *flag = 1;
  }
  ipAlreadyExists(root->right, flag,  val);
 }
}

int checkIfIPAlreadyExist_Update(struct address_t* root, int *val){
 
 int flag = 0;

 ipAlreadyExists_Update(root, &flag, val);
 if(flag == 1)
  printf("\terror: newly entered address is duplicate\n");  

 return flag;
}

void updateAddressHelper(struct address_t* ptr, char* alias){
 if(ptr!=NULL){
  updateAddressHelper(ptr->left, alias);
  if(strcmp(ptr->alias,alias)==0){
   int val[4];
   printf("\tUpdate address for %s: %d.%d.%d.%d\n", ptr->alias,  ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);

   for(int i =0; i < 4; i++){
    int flag = 1;
    while(flag){
     if(i==0||i==1)
      printf("\tEnter location value # %d(0-255): ",i+1);
     else
      printf("\tEnter value # %d(0-255): ",i+1);
     scanf("%d",&val[i]);
     if(val[i]<0||val[i]>255)
      printf("\terror: %d is an illegal entry- please reenter\n",val[i]);
     else
      flag=0;
    }
   }

   int isDuplicate = checkIfIPAlreadyExist(ptr, val);

   if(!isDuplicate){
    ptr->octet[0] = val[0];
    ptr->octet[1] = val[1];
    ptr->octet[2] = val[2];
    ptr->octet[3] = val[3];
   }else
     return;
  }
  updateAddressHelper(ptr->right, alias);
 }
}

//3. Updating the address of the given alias
void updateAddress(struct address_t* root){
 char alias[20];
 int val[4];
 
 struct address_t* ptr1 = NULL;
 int flag1 = 0;

 if(!flag1){
  printf("\tEnter alias: ");
  scanf("%s",&alias);

  ptr1 = root;
  aliasAlreadyExist(ptr1,alias, &flag1);
  if(flag1 == 0){
   printf("\terror: alias does not exist in the list\n");
   return;
  }
 }

 struct address_t *ptr = root;
 updateAddressHelper(ptr, alias);
  
}

struct address_t *minValueNode(struct address_t* node){
 struct address_t* current = node;
 while(current && current->left != NULL)
  current = current->left;
 return current;
}

struct address_t* deleteAddress_Helper(struct address_t* root,char* alias){
 if(root == NULL)
  return root;
 int res = strcmp(alias, root->alias);
 if(res < 0)
  root->left = deleteAddress_Helper(root->left, alias);
 else if(res > 0)
  root->right = deleteAddress_Helper(root->right, alias);
 else{
  if(root->left == NULL){
   struct address_t* temp = root->right;
   free(root);
   return temp;
  }else if(root-> right == NULL){
   struct address_t* temp = root->left;
   free(root);
   return temp;
  }
  struct address_t* temp = minValueNode(root->right);
  strcpy(root->alias, temp->alias);
  root->right = deleteAddress_Helper(root->right,temp->alias);
 }
 return root;
}

//4. Deleting the particular IP address and alias from the linked list
void deleteAddress(struct address_t* root){
 char alias[20];

 printf("\tEnter alias: ");
 scanf("%s", alias);
 
 struct address_t *ptr = root;
 int flag1 = 0 ;
 aliasAlreadyExist(ptr,alias,  &flag1);
 if(flag1 == 0){
  printf("\terror:%s does not exist\n",alias);
  return;
 }
 printf("\tDelete %s?(y/n) ",alias);
 char ch[2];
 scanf("%s",ch);
 if(strcmp(ch,"y")==0){
  deleteAddress_Helper(root,alias);
  printf("\t%s deleted\n",alias);
 }else
   return;
}

//5. Displaying the tree inorder trversal
void display(struct address_t *root){
 if(root!=NULL){
  display(root->left);
  printf("\t%s: %d.%d.%d.%d\n",root->alias, root->octet[0],root->octet[1],root->octet[2],root->octet[3]);
  display(root->right);
 }
}

void displayAliasForLocation_Helper(struct address_t* root, int* flag,int* b){
 if(root != NULL){
  displayAliasForLocation_Helper(root->left, flag, b);
  if((root->octet[0]==b[0]) && (root->octet[1]==b[1])){
   *flag = 1;
   printf("\t%d.%d.%d.%d %s\n",root->octet[0],root->octet[1],root->octet[2],root->octet[3],root->alias);
  }
  displayAliasForLocation_Helper(root->right, flag, b); 
 }
}

//6. Displaying all the alias values for the given location address
void displayAliasForLocation(struct address_t* root){
 int b[4];

 for(int i = 0; i < 2; i++){
  int flag = 1;
  while(flag){
   printf("\tEnter location value # %d(0-255): ",i+1);
   scanf("%d",&b[i]);
   if(b[i]<0||b[i]>255)
    printf("\terror %d is an illegal entry - please reenter\n",b[i]);
   else
    flag = 0;
  }
 }
 
 int flag = 0;
 displayAliasForLocation_Helper(root, &flag, b);
 if(flag == 0)
  printf("\terror: location does not exist\n");
}

void saveToFile_helper(struct address_t* root, FILE* fptr){
 if(root!=NULL){
  saveToFile_helper(root->left, fptr);
  if(fptr != NULL){
   char temp[50];
   sprintf(temp, "%d.%d.%d.%d %s", root->octet[0],root->octet[1],root->octet[2],root->octet[3],root->alias);
   fputs(temp,fptr);
   fputs("\n",fptr); 
  }
  saveToFile_helper(root->right, fptr);
 }
}

//7. Saving the new linked list to the given file name
void saveToFile(struct address_t* root){
 char fileName[40];
 printf("\tEnter file name: ");
 scanf("%s", fileName);

 FILE *fptr;
 fptr = fopen(fileName, "w");

 if(fptr == NULL){
  printf("\tError while creating a file\n");
  exit(EXIT_FAILURE);
 } 
  
 saveToFile_helper(root, fptr);
 printf("\tFile saved. \n");
 fclose(fptr);
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
// if(root == NULL) 
 // root = add_to_tree(root, line);
 //else
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
   case 3: updateAddress(root);
	   break;
   case 4: deleteAddress(root);
	   break;
   case 5: display(root);
	   break;
   case 6: displayAliasForLocation(root);
	   break;
   case 7: saveToFile(root);
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
