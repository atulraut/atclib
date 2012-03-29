#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

int main()  {  
    char *source;  
    char *target;  
    char *ret;  
    int no_of_char;  
  
    /*function prototype it takes string and returns address*/  
    char *my_strncpy(char *target1,const char *source1,int no);  
    source=(char*)malloc(20);  
    target=(char*)malloc(20);  
  
    printf(" Enter the string to be copied:\n");  
    fgets(source,20,stdin);   //taking input from user  
      
    printf("\n Enter the number of characters to be copied:");  
    scanf("%d",&no_of_char);  
    ret=my_strncpy(target,source,no_of_char);     
      
    printf("\n The address of copy of string is %d ",ret );  //print the address of copt of string  
    printf("\n The copied string is %s \n", ret);  //print the copy of string  
      
    free(source);  
    free(target);  
    return EXIT_SUCCESS;  
}  
char * my_strncpy(char *target1,const char *source1,int no)  {  
    char *tempt=target1;  
    int n=0;  
    while(n<no)  
    {  
        *target1=*source1;  
        target1++;  
        source1++;  
        n++;  
    }  
  
    *target1='\0';  
    return tempt;  
}  
