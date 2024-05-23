/*
 *HW1-G01413212.c -- Design and implement a C program based on the given specifications.
 *Firstname: John Stephen
 *Lastname: Gutam
 */

#include<stdio.h>
#include<string.h>

void display(char str[][100]);
void bubbleSort_ASC(char str[][100], int n);
void bubbleSort_DSC(char str[][100], int n);

int main(){
 char str[10][100]; //Contains the character strings
 char sort[5]; //Accepts the A or D characters to sort the array
 int i;
 int n = 10; //number of strings

 printf("Enter 10 charater strings:\n");
 
 for(int  i=0; i < 10; i++){
  printf("Enter string %d:",i+1); 
  scanf("%s",&str[i][0]);

  int len = strlen(&str[i][0]);

  //Checking for the existence of illegal charaters
  char s2[ ] = "+*#$%^()";
  char *p;
  p = strpbrk(str[i], s2);
  if(p != NULL){
   printf("Error: %c  Is a illegal character - Please re-enter",*p);
   i = i-1;
  }

  //Checking for the length of the strings entered
  if(len < 1 || len >25){
   printf("Please enter the values of size between 1 and 25");
   i = i-1;
  }
 // if(str[i][0] == '\0'|| str[i][0] == '\n'){
  char empty[2] = ""; 
  if(!strcmp(str[i],empty)){
   printf("Please enter the non empty string");
   i = i-1;
  }

  //Checking for the duplicate string
  int j =0;
  for(j =0; j < i; j++){
   if(strcmp(str[i],str[j]) == 0){
    printf("Error: duplicate string – please re-enter");
    i=i-1;
    break;
   }
  }
   printf("\n");
 }
 
 //Sorting based on the user unput
 printf("\nPrint character strings in \e[1mA\e[mscending or \e[1mD\e[mescending order:");

 do{
  scanf("%s",&sort);

  if(!strcmp(sort, "A")){
         printf("\nAscending order\n");
         bubbleSort_ASC(str, n);
	 break;
  }else if(!strcmp(sort,"D")){
         printf("\nDescending order:\n");
         bubbleSort_DSC(str, n);
	 break;
  }else{
        printf("Please enter either A or D\n");
  }

}while(sort != "A" ||sort != "D");
 
 return 0;
}

/*
 *Function bubblesort_ASC will sort the character array in ascending order
 *Input: Takes Character array str[][100] and number of strings
 *Output: Sorted  Ascending order character array.
 */
void bubbleSort_ASC(char str[][100],int n){
 long c, d;
 char t[30];
 for (c = 0 ; c < ( n - 1 ); c++)
 {
  for (d = 0 ; d < n - c - 1; d++)
  {
   int ret = strcmp(str[d],str[d+1]);
   if (ret > 0)
   {
   /*  Swapping */

    strcpy(t,str[d]);
    strcpy(str[d],str[d+1]);
    strcpy(str[d+1],t);
   }
  }
 }

 display(str);
 printf("\nlowest Ascii value string:%s",str[0]);
 printf("\nhighest Ascii value string:%s",str[9]);
}

/*
 *Function bubblesort_DSC will sort the character array in descending order
 *Input: Takes Character array str[][100] and number of strings 
 *Output: Sorted Character array in descending order.
 */
void bubbleSort_DSC(char str[][100],int n){
 long c, d;
 char t[30];
 for (c = 0 ; c < ( n - 1 ); c++)
 {
  for (d = 0 ; d < n - c - 1; d++)
  {
   int ret = strcmp(str[d],str[d+1]);
   if (ret < 0)
   {
   /*  Swapping */
   /* t = str[d];
    str[d] = str[d+1];
    str[d+1] = t;*/

    strcpy(t,str[d]);
    strcpy(str[d],str[d+1]);
    strcpy(str[d+1],t);
   }
  }
 }

 display(str);
 printf("\nString with lowest ascii value:%s",str[9]);
 printf("\nString with highest ascii value:%s",str[0]);

}

/*
 *Function display will print the strings 
 *Input: takes the 2 dimentional character string
 *Output: Display the charater strings
 */
void display(char  str[][100]){
 printf("\nAfter sorting:\n");
 for(int j=0; j < 10; j++){
  printf(" %s \n ",str[j]);
 }
}
