#include<stdio.h>
#include<string.h>

void display(char str[][30]);
void bubblesort_ASC(char str[][30], int n);
void bubblesort_DSC(char str[][30], int n);

int main(){
 char str[10][30], sort[5];
 int i;
 int n = 10;
 printf("Enter 10 unique charater strings\n");
 /*scanf("%s",&str);
 printf("%s",str[0]);*/
 for(int  i=0; i < 10; i++){
  printf("Enter your string %d:",i+1); 
  scanf("%s",&str[i][0]);
  
  int len = strlen(&str[i][0]);
  char s2[ ] = "+*#$%^()";
  char *p;
  p = strpbrk(str[i], s2);
  if(p != NULL)
   printf("\nError: Is a illegal character - Please re-enter\n");

  if(len < 1 || len >25)
   printf("Please enter the values of size between 1 and 25");
  if(str[i][0] == '\0')
   printf("Please enter the non empty string");
  printf("\n");
 }
 printf("Enter which sorting you need ASC or DSC:");
 scanf("%s",&sort);
 if(!strcmp(sort, "ASC")){
	 printf("\nSorting based on ASC order:\n");
	 bubblesort_ASC(str, n);
 }else{
	 printf("\nSorting based on DSC order:\n");
	 bubblesort_DSC(str, n);
 }
// printf(*str);
 //printf(str[0]);
 //printf(str[1]);
 display(str);
 return 0;
}

void bubblesort_ASC(char str[][30],int n){
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
 printf("\nlowest Ascii value string:%s",str[0]);
 printf("\nhighest Ascii value string:%s",str[9]);
}

void bubblesort_DSC(char str[][30],int n){
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
 printf("\nlowest Ascii value string:%s",str[9]);
 printf("\nhighest Ascii value string:%s",str[0]);

}

void display(char  str[][30]){
 printf("\nAfter sorting:\n");
 for(int j=0; j < 10; j++){
  printf(" %s \n ",str[j]);
 }
}
