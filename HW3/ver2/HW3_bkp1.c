#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

/*
char* aliasExtract(char* line){
 char *str = strchr(line,' ');
 return str;
}*/

struct address_t* add_to_tree(struct address_t* node, char* line){
 if(node == NULL) 
  return newNode(line);

 char *tempalias;
 if(line!=NULL){
  tempalias = strchr(line,' ');
 }

 if(strcmp(/*aliasExtract(line)*/tempalias,node->alias) > 0)
  node->left = add_to_tree(node->left, line);
 else
  node->right = add_to_tree(node->right, line);
 return node;
}

void display(struct address_t *root){
 if(root!=NULL){
  display(root->left);
  printf("%s\n",root->alias);
  display(root->right);
 }
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
 } 

 return 0;
}
