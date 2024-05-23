#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//length of the each IP address and alias name in file
#define MAX_LINE_LENGTH 50

struct address_t{
 int octet[4];
 char alias[30];
 struct address_t *next; 
};

struct address_t *head=NULL;
struct address_t *curr=NULL;

//create a Node
struct address_t* createList(char *line){
 struct address_t *ptr = (struct address_t *)malloc(sizeof(struct address_t));
// printf("%s",line);
 if(ptr == NULL){
  printf("\nNode creation failed\n");
  return NULL;
 }
	 
 sscanf(line, "%d.%d.%d.%d %s", ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->alias);
 printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
 
 ptr->next = NULL;

 head=curr=ptr;
 return ptr;
}

struct address_t* add_to_list(char *line, bool add_to_end){
 if(NULL == head){
  return(createList(line));
 }
 
 struct address_t *ptr = (struct address_t*)malloc(sizeof(struct address_t));
 if(NULL == ptr){
  printf("\nNode creation failed\n");
  return NULL;
 }	 
 
 sscanf(line, "%d.%d.%d.%d %s", ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->alias);
 printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);

 ptr->next = NULL;

 if(add_to_end){
  curr->next = ptr;
  curr = ptr;
 }else{
  ptr->next = head;
  head = ptr;
 }
 
 return ptr;
}

//add address to the linked list
void addAddress(){
}

void lookUpAddress(){
}

void updateAddress(){
}

void deleteAddress(){
}

void displayList(){
 struct	address_t *ptr = head;
 printf("\n-------Printinting list Start------- \n");
 while(ptr!=NULL)
 {
  printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);	 
  ptr=ptr->next;
 }
 printf("\n-------Printing list	End------- \n");
 return;
}

void displayAliasForLocation(){
}

void saveToFile(){
}

void quit(){
}

int main(){
 struct address_t *ptr=NULL;
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
 // printf("%s",line);
  add_to_list(line,true); 
 }
 
 displayList();

 do{
  printf("1) Add address\n");
  printf("2) Look up address\n");
  printf("3) Update address\n");
  printf("4) Delete address\n");
  printf("5) Display list\n");
  printf("6) Display aliases for location\n");
  printf("7) Save to file");
  printf("8) Quit");
  scanf("%c",&menu_option);

  switch(menu_option){
   case '1':
        break;
   case '2':
        initials=get_intials();
        printf( "input initials:%c\n", initials) ;
        break;
   case '3':
        printf("case c");
        //difficulty = get_difficulty();
        break;
   case '4':
        break;
   case '5':
        break;
   case '6':
	break;
   case '7':
	break;
   case '8':
	break;
   default:
        printf("invalid input");
        break;
    }

  }while(menu_option !='e');

 fclose(fp)
 return 0;
}
