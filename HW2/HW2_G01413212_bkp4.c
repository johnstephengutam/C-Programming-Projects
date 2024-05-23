#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>

//length of the each IP address and alias name in file
#define MAX_LINE_LENGTH 50

void displayList();

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
 //printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
 
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
 //printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);

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

char* lowerCase(char alias[]){
 for(int i = 0; alias[i]; i++){
  alias[i] = tolower(alias[i]);
 }
 return alias;
}

//add address to the linked list
void addAddress(){
 char alias[11];
 char ipAddress[20];
 int b[4] = {0};
 printf("\nEnter alias: ");
 scanf("%s",alias);
 
 strcpy(alias,lowerCase(alias));
 
 //check if this alias already exists in linked list
 struct address_t *ptr = head;
 while(ptr!=NULL){
  if(strcmp(ptr->alias,alias)== 0){
   printf("error: %s already exists");
   return;
  }
  ptr=ptr->next;
 } 
 int flag = 1;
 while(flag){
  printf("\nEnter IP address for %s:",alias);
  scanf("%s",ipAddress);
  sscanf(ipAddress, "%d.%d.%d.%d %s",b, b+1, b+2, b+3,alias );
  printf("values in %s: %d %d %d %d\n", alias, b[0], b[1], b[2], b[3]);
  if(b[0] < 0 || b[0] > 255)
   printf("\nerror: %s is an illegal address- please reenter:",ipAddress);
  else if(b[1] < 0 || b[1] > 255)
   printf("\nerror: %s is an illegal address- please reenter:",ipAddress);
  else if(b[2] < 0 || b[2] > 255)
   printf("\nerror: %s is an illegal address- please reenter:",ipAddress);
  else if(b[3] < 0 || b[3] > 255)
   printf("\nerror: %s is an illegal address- please reenter:",ipAddress);
  else
    flag = 0;
 }
 char line[40];
 strcpy(line, ipAddress);
 strcat(line," ");
 strcat(line,alias);
 add_to_list(line,true);
}

void lookUpAddress(){
 char alias[20];

 printf("\nEnter alias: ");
 scanf("%s",alias);
// printf("Here1 %s",alias);
 //strcpy(alias,lowerCase(alias));
 //printf("Here2 %s",alias);
 struct address_t *ptr = head;
 while(ptr != NULL){
  if(strcmp(ptr->alias,alias)== 0){
   printf( "%d.%d.%d.%d", ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
  }
 }
 if(ptr == NULL){
 }
}

void updateAddress(){
 char alias[20];
 int val[4];
 printf("\nEnter alias: ");
 scanf("%s",alias);

 struct address_t *ptr = head;
 while(ptr != NULL){
  if(strcmp(ptr->alias,alias)==0){
   printf("Update address for baker: %d.%d.%d.%d", ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
   
   for(int i =0; i < 4; i++){
    int flag = 1;
    while(flag){
     printf("\nEnter location value # %d(0-255): ",i+1);
     scanf("%d",&val[i]);
     if(val[i]<0||val[i]>255)
      printf("error: %d is an illegal entry- please reenter",val[i]);
     else
      flag=0;
    }
   }
   //printf("\nEnter location value # 2(0-255): ");
   //scanf("%d",&val[1]);
   //printf("\nEnter value # 3(0-255): ");
   //scanf("%d",&val[2]);
   //printf("\nEnter value # 4(0-255): ");
   //scanf("%d",&val[3]);
   
   ptr->octet[0] = val[0];
   ptr->octet[1] = val[1];
   ptr->octet[2] = val[2];
   ptr->octet[3] = val[3];
  }
  ptr=ptr->next;
 }
}

//6
void deleteAddress(){

}

//5
void displayList(){
 struct	address_t *ptr = head;
 printf("\n-------Printinting list Start------- \n");
 while(ptr!=NULL)
 {
  printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);	 
  ptr=ptr->next;
 }
 printf("\n-------Printing list	End------- \n");
 printf("\nTotal node count \n");
 return;
}

//6
void displayAliasForLocation(){
}

//7
void saveToFile(){
 char str[20]="/home/jgutam/";
 char fileName[40];
 printf("\nEnter file name:");
// fgets(fileName,sizeof(fileName),stdin);
 //printf("Filename entered: %s",fileName);
 scanf("%s",fileName);
 strcat(str, fileName);

 FILE *fptr;
 fptr = fopen(str,"w");

 if(fptr == NULL){
  printf("\nError while creating a file\n");
  exit(EXIT_FAILURE);
 }

 struct address_t *ptr = head;

 while(ptr!=NULL){
   char temp[50];
   sprintf(temp, "%d.%d.%d.%d %s", ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
   fputs(temp,fptr);
   fputs("\n",fptr);
   ptr = ptr->next;
 }
 fclose(fptr);
}

//8
void quit(){
 printf("\nGood bye!\n");
}

int main(){
 struct address_t *ptr=NULL;
 char file_name[25];
 FILE *fp;
 //char menu_option;

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

  printf("1) Add address\n");
  printf("2) Look up address\n");
  printf("3) Update address\n");
  printf("4) Delete address\n");
  printf("5) Display list\n");
  printf("6) Display aliases for location\n");
  printf("7) Save to file\n");
  printf("8) Quit\n");

 int flag = 1;
 int menu_option;
 while(flag){
  printf("\nEnter menu option: ");  
  scanf("%d",&menu_option);

  switch(menu_option){
   case 1:
	addAddress();
        break;
   case 2:
	lookUpAddress();
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
	break;
   case 7:
        saveToFile();
	break;
   case 8:
	flag = 0;
	break;
   default: 
	printf("\nInvalid Input\n");
        break;
  }

 }

 fclose(fp);
 return 0;
}
