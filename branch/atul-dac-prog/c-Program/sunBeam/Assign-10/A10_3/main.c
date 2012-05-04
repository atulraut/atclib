#include<stdio.h>
#include<stdlib.h>
int main()
{
	 char source[10],target[10],buff[20];		
	 FILE *fs, *ft;
	 printf("Enter the sorce file name :");
	 scanf("%s", source); 	 
	 printf("enter target file name :");
	 scanf("%s", target);
	 
	 fs = fopen(source,"rb");
	 if(fs == NULL)
	 {
		printf("\nSource File not found....\n");
		return 1;
	 }

	 ft = fopen(target,"wb");
	 if(ft == NULL)
	 {
		printf("\nTarget File not found...\n");
		return 1;
	 }
	 while(fread(&buff,sizeof(buff),1,fs))
	 {
		fwrite(&buff,sizeof(buff),1,ft);
	 }
	 printf("\nFile copied successfully \n");
	 return 1;
}