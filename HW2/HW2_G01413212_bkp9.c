#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>

//length of the each IP address and alias name in file
#define MAX_LINE_LENGTH 50

struct address_t* createList(char* line);
struct address_t* add_to_list(char *line, bool add_to_end);
char* lowerCase(char alias[]);

//8 functionalities
void addAddress();
void lookUpAddress();
void updateAddress();
struct address_t* search_in_list(char* alias, struct address_t **prev);
int deleteAddress();
void displayList();
void displayAliasForLocation();
void saveToFile();
void quit();

//structure of the IP Address and alias
struct address_t{
 int octet[4];
 char alias[30];
 struct address_t *next; 
};

struct address_t *head=NULL;
struct address_t *curr=NULL;

//create a Node
struct address_t* createList(char* line){
 struct address_t *ptr = (struct address_t *)malloc(sizeof(struct address_t));
 if(ptr == NULL){
  printf("\nNode creation failed\n");
  return NULL;
 }
	 
 sscanf(line, "%d.%d.%d.%d %s", ptr->octet,ptr->octet+1,ptr->octet+2,ptr->octet+3,ptr->alias);
 
 ptr->next = NULL;

 head=curr=ptr;
 return ptr;
}

//adding the nodes to the linked list
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

//converting the character array into lowercase
char* lowerCase(char alias[]){
 for(int i = 0; alias[i]; i++){
  alias[i] = tolower(alias[i]);
 }
 return alias;
}

//adding address to the linked list
void addAddress(){
 char alias[11];
 char ipAddress[20];
 int b[4] = {0};
 printf("\tEnter alias: ");
 scanf("%s",alias);
 
 strcpy(alias,lowerCase(alias));
 
 //check if this alias already exists in linked list
 struct address_t *ptr = head;
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
  
  //validating the IP address values
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
 }
 char line[40];
 strcpy(line, ipAddress);
 strcat(line," ");
 strcat(line,alias);
 add_to_list(line,true);
}

//2. display the address of the corresponding alias
void lookUpAddress(){
 char alias[20];
 
 int flag =0;
 printf("\tEnter alias: ");
 scanf("%s",alias);
 struct address_t *ptr = head;
 while(ptr != NULL){
  if(strcmp(ptr->alias,alias)== 0){
   flag = 1;
   printf("\tAddress for the %s: %d.%d.%d.%d\n",ptr->alias, ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
   break;
  }
  ptr=ptr->next;
 }
 //if alias does exist
 if(flag == 0)
  printf("\terror: %s does not exist\n",alias);
}

//3. Updating the address of the given alias
void updateAddress(){
 char alias[20];
 int val[4];
 printf("\tEnter alias: ");
 scanf("%s",alias);

 struct address_t *ptr = head;
 while(ptr != NULL){
  if(strcmp(ptr->alias,alias)==0){
   printf("\tUpdate address for baker: %d.%d.%d.%d\n", ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
   
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
   
   ptr->octet[0] = val[0];
   ptr->octet[1] = val[1];
   ptr->octet[2] = val[2];
   ptr->octet[3] = val[3];
  }
  ptr=ptr->next;
 }
}

//searching for the particular node address in the linked list through which we can delete the particular node
struct address_t* search_in_list(char* alias, struct address_t **prev)
{
 struct	address_t *ptr = head;
 struct	address_t *tmp =NULL;
 bool found = false;
 
 while(ptr != NULL)
 {
  
  if(strcmp(ptr->alias,alias)==0){
   found = true;
   break;
  }else{
   tmp = ptr;
   ptr = ptr->next;
  }
 }
 if(true == found)
 {
  if(prev)
   *prev = tmp;
  return ptr;
 }
 else
 {
  return NULL;
 }
}

//4. Deleting the particular IP address and alias from the linked list
int deleteAddress()
{
 char alias[20];

 printf("\tEnter alias: ");
 scanf("%s",alias);
 
 struct	address_t *prev	= NULL;
 struct	address_t *del = NULL;
 
 del = search_in_list(alias,&prev);
 
 if(del	== NULL)
 {
  printf("\terror:%s does not exist\n",alias);
  displayList();
  return -1;
 }
 else
 {
  printf("\tDelete %s %d.%d.%d.%d?(y/n) ",alias,del->octet[0],del->octet[1],del->octet[2],del->octet[3]);
  char ch[2];
  scanf("%s",ch);
  if(strcmp(ch,"y")==0){
   if(prev != NULL)
    prev->next =	del->next;
   if(del == curr)
   {
    curr	= prev;
   }
   else if(del==head)
   {
    head	= del->next;
   }
 } else{
  return 0;
 }

 }
 free(del);
 del = NULL;
 printf("\t%s deleted\n",alias);
 return	0;
}

//5. Displaying the linked list values
void displayList(){
 int count = 0;
 struct	address_t *ptr = head;
 while(ptr!=NULL)
 {
  ++count;
  printf("%d %d %d %d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);	 
  ptr=ptr->next;
 }
 printf("Total node count: %d\n",count);
 return;
}

//6. Displaying all the alias values for the given location address
void displayAliasForLocation(){
 int b[4];
 
 for(int i=0; i<2; i++){
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

 struct address_t *ptr = head;
 int flag = 0;
 while(ptr != NULL){
  if((ptr->octet[0]==b[0]) && (ptr->octet[1]==b[1])){
   flag = 1;
   printf("\t%d.%d.%d.%d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
  }  
  ptr = ptr->next;
 }
 if(flag ==0)
  printf("\terror: location doesnot exist\n");

}

//7. Saving the new linked list to the given file name 
void saveToFile(){
 char fileName[40];
 printf("\tEnter file name:");
 scanf("%s", fileName);
 
 FILE *fptr;
 fptr = fopen(fileName,"w");

 if(fptr == NULL){
  printf("\tError while creating a file\n");
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
 printf("\tFile saved. \n");
 fclose(fptr);
}

//8. To quit the application
void quit(){
 printf("\nGood bye!\n");
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
  add_to_list(line,true); 
 } 
 /*
  printf("1) Add address\n");
  printf("2) Look up address\n");
  printf("3) Update address\n");
  printf("4) Delete address\n");
  printf("5) Display list\n");
  printf("6) Display aliases for location\n");
  printf("7) Save to file\n");
  printf("8) Quit\n");*/

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
