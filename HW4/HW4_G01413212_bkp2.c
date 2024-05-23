/*
 *HW4-G01413212.c -- Design and implement a C program based on the given specifications.
 *Firstname: John Stephen
 *Lastname: Gutam
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_LINE_LENGTH 50

//Structure of an address
struct address_t{
 int octet[4];
 char alias[30];
 int height;
 int depth;
 int balFactor;
 struct address_t* left;
 struct address_t* right;
 struct address_t* parent;
};

//Calculating the height of the node
int height(struct address_t* node){
 if(node == NULL)
  return -1;
 else{
  int lheight = height(node->left);
  int rheight = height(node->right);
  if(lheight > rheight)
   return (lheight+1);
  else 
   return (rheight+1);
 }
}

//Calculating the height - helper method
void utilHeight(struct address_t* root){
 if(root != NULL){
  utilHeight(root->left);
  utilHeight(root->right);
 }
}

//Calculating the depth of the node
void utilDepth(struct address_t* root, int depth){
 if(root != NULL){
  root->depth = depth;
  utilDepth(root->left, depth+1);
  utilDepth(root->right, depth+1);
 }
}

struct address_t* newNode(struct address_t* root, char* line){
 struct address_t* ptr = (struct address_t *)malloc(sizeof(struct address_t));

 if(ptr == NULL){
  printf("\n Node creation failed\n");
  return NULL;
 }

 sscanf(line,"%d.%d.%d.%d %s",ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3, ptr->alias);

 ptr->left=ptr->right=ptr->parent=NULL;
 ptr->height = 0;
 return ptr;
}

int get_balance(struct address_t *node) {
 if (node == NULL)
  return 0;
 return height(node->left) - height(node->right);
}

//Below 4 UDF are for the balancing of the tree
struct address_t* rotateWithLeftChild(struct address_t* k2){
 struct address_t* k1 = k2->left;
 k2->left = k1->right;
 k1->right = k2;

 //updating heights
 k2->height = height(k2);
 k1->height = height(k1);

 //updating balance factor
 k1->balFactor = get_balance(k1);
 k2->balFactor = get_balance(k2);
 
 //updating parent
 k1->parent = k2->parent;
 k2->parent = k1;

 return k1;
}

struct address_t* rotateWithRightChild(struct address_t* N1){
 struct address_t* N2 = N1->right;
 N1->right = N2->left;
 N2->left = N1;

 //updating heights
 N1->height = height(N1);
 N2->height = height(N2);
 
 //updating balance factors
 N1->balFactor = get_balance(N1);
 N2->balFactor = get_balance(N2);
 
 //updating the parent 
 N2->parent = N1->parent;
 N1->parent = N2;

 return N2;
}


struct address_t* doubleRotateWithLeftChild(struct address_t* k3){
 k3->left = rotateWithRightChild(k3->left);
 return rotateWithLeftChild(k3);
}

struct address_t* doubleRotateWithRightChild(struct address_t* k3){
 k3->right = rotateWithLeftChild(k3->right);
 return rotateWithRightChild(k3);
}


struct address_t* add_to_tree(struct address_t* root, char* line){
 if(root == NULL)
  return newNode(root, line);

 struct address_t *ptr = (struct address_t*)malloc(sizeof(struct address_t));
 sscanf(line, "%d.%d.%d.%d %s", ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->alias);
 
 int res = strcmp(ptr->alias,root->alias);
 if(res < 0){
  root->left = add_to_tree(root->left, line);
  root->left->parent = root;
 }
 else if(res > 0){
  root->right = add_to_tree(root->right, line);
  root->right->parent = root;
 }
 else
  return root;

 //Update the height of ancestor node
 root->height = height(root);
 int balance = get_balance(root);
 root->balFactor = balance;
 
 if(balance > 1){
  if(get_balance(root->left) > 0)
   root = rotateWithLeftChild(root);
  else
   root = doubleRotateWithLeftChild(root);
 }else if(balance < -1){
  if(get_balance(root->right) > 0)
   root = doubleRotateWithRightChild(root);
  else
   root = rotateWithRightChild(root);
 }
 return root;
}


//Finding the min value
struct address_t *minValueNode(struct address_t* node){
 struct address_t* current = node;
 while(current && current->left != NULL)
  current = current->left;
 return current;
}

//Checking if alias already exists in the BST
void aliasAlreadyExist(struct address_t* root,char* alias, int* flag){
 if(root!=NULL){
  aliasAlreadyExist(root->left, alias, flag);
  if(strcmp(root->alias,alias)==0){
   *flag = 1;
  }
  aliasAlreadyExist(root->right, alias,  flag);
 }
}

//Checking the IP is already exists in the BST
void ipAlreadyExists(struct address_t* root, int* flag, int *val){
 if(root!=NULL){
  ipAlreadyExists(root->left, flag, val);
  if((root->octet[0]== val[0]) && (root->octet[1]== val[1]) && (root->octet[2]== val[2]) && (root->octet[3]== val[3])){
   *flag = 1;
  }
  ipAlreadyExists(root->right, flag,  val);
 } 
}

//Checking the error message if IP already exists
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

  //Cheking if IP is duplicate
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
 struct address_t* temp = add_to_tree(root,line);
}	

//5. Displaying the tree inorder trversal
void display(struct address_t *root){
 if(root!=NULL){
  display(root->left);
  printf("\t%s\t%d.%d.%d.%d\theight:%d\tdepth:%d\tbf:%d",root->alias, root->octet[0],root->octet[1],root->octet[2],root->octet[3],root->height,root->depth,root->balFactor);
  if(root->parent != NULL)
   printf("\tparent: %s\n",root->parent->alias);
  else
   printf("\tparent: NONE\n");
  display(root->right);
 }
}

//8. To quit the application
void quit(){
 printf("\nGood bye!\n");
}

//Main function called by OS
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

 utilHeight(root);
 utilDepth(root, 0);

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
   case 2:// lookUpAddress(root);
	   break;
   case 3:// updateAddress(root);
	   break;
   case 4:// deleteAddress(root);
	   break;
   case 5: display(root);
	   break;
   case 6:// displayAliasForLocation(root);
	   break;
   case 7:// saveToFile(root);
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





































































