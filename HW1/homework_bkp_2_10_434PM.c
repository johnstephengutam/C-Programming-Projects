#include<stdio.h>
#include<string.h>

void display(char str[][100]);
void bubblesort_ASC(char str[][100], int n);
void bubblesort_DSC(char str[][100], int n);

int main(){
 char str[10][100], sort[5];
 int i;
 int n = 10;
 printf("Enter 10 charater strings:\n");
 /*scanf("%s",&str);
 printf("%s",str[0]);*/
 for(int  i=0; i < 10; i++){
  printf("Enter string %d:",i+1); 
  scanf("%s",&str[i][0]);

  int len = strlen(&str[i][0]);
  //printf("delete length %d",len);

  char s2[ ] = "+*#$%^()";
  char *p;
  p = strpbrk(str[i], s2);
  if(p != NULL){
   printf("\nError: %c  Is a illegal character - Please re-enter\n",*p);
   i = i-1;
  }
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
 printf("Print character strings in \e[1mA\e[mscending or \e[1mD\e[mescending order:");
// scanf("%s",&sort);
 /*for(i=1; i< 2;i++ )
 if(strcmp(sort,"A")!= 0||strcmp(sort,"D")!=0){
	 printf("Please enter either A or D");
	 i = i-1;
 }*/

 do{
  scanf("%s",&sort);

  if(!strcmp(sort, "A")){
         printf("\nAscending order\n");
         bubblesort_ASC(str, n);
	 break;
  }else if(!strcmp(sort,"D")){
         printf("\nDescending order:\n");
         bubblesort_DSC(str, n);
	 break;
  }else{
        printf("Please enter either A or D\n");
  }

}while(sort != "A" ||sort != "D");
 
/*
 if(!strcmp(sort, "A")){
	 printf("\nAscending order\n");
	 bubblesort_ASC(str, n);
 }else if(!strcmp(sort,"D")){
	 printf("\nDescending order:\n");
	 bubblesort_DSC(str, n);
 }else{
 	printf("Please enter either A or D\n");
 }
// printf(*str);
 //printf(str[0]);
 //printf(str[1]);
// display(str);
*/
 
 return 0;
}

void bubblesort_ASC(char str[][100],int n){
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
 printf("\nlowest Ascii value string:%s",str[0]);
 printf("\nhighest Ascii value string:%s",str[9]);
}

void bubblesort_DSC(char str[][100],int n){
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

void display(char  str[][100]){
 printf("\nAfter sorting:\n");
 for(int j=0; j < 10; j++){
  printf(" %s \n ",str[j]);
 }
}
