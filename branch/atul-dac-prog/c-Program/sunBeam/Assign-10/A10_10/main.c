#include<stdio.h>
#include<stdlib.h>
int main()
{
	 char source[100],target[100],buff[20], temp[20];		
	 FILE *fs, *ft;
	 printf("Enter the sorce file name :");
	 scanf("%s", source); 
	 fs = fopen(source,"rb");
	 if(fs == NULL)
	 {
		printf("\nSource File not found....\n");
		return 1;
	 }
	 ft = fopen("target", "wb");
		{
			printf("\nSource File not found....\n");
			return 1;
		}
		while((fread(&buff, sizeof(buff), 1, fs) != NULL)
		{
			if(fs == '\' || fs == '\n')
				continue;
			else
				fwrite(&buff, sizeof(buff), 1, fs);

		}
}
