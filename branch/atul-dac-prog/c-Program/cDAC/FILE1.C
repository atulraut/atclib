/*IN THIS PROGRAM WE COUNT THE NO. OF CHARACTORS, SPACES AND LINES PRESENT
  IN FILE  */

#include<stdio.h>
#include<conio.h>
void main()
{
	FILE *fp,*ft,*ft1;
	int noc=0,nos=0,nol=1,i=0,j;
	char m,n,buff[80][80],buff1[80],a[80];
	clrscr();
	fp=fopen("d:\\vishal\\mugdha.txt","r");
	if(fp==NULL)
	{
		puts("cannot open the source file");
		getch();
		exit();
	}
	ft=fopen("d:\\vishal\\kasturi.txt","w");
	if(ft==NULL)
	{
		puts("cannot open the target file");
		fclose(fp);
		exit();
	}
	ft1=fopen("d:\\vishal\\vish.txt","w");
	printf("\n");
	while((m=fgetc(fp))!=EOF)
	{

	if(m==' ')
		nos++;

	if(m=='\n')
		nol++;
	noc++;

	fputc(m,ft);
	/*a[i]=m;*/

	}
	/*for(i=noc-1;i>=0;i--)
	   fputc(a[i],ft);*/
	fclose(fp);
	fp=fopen("d:\\vishal\\v1.txt","r");
       while(fscanf(fp,"%s",buff1)!=EOF)
       {
		/*strrev(buff1);*/
		strcpy(buff[i],buff1);
		i++;

       }
       /*for(j=0;j<i;j++)*/
       for(j=i-1;j>=0;j--)
       {
		fputs(buff[j],ft1);

       }

	fclose(fp);
	fclose(ft);
	fclose(ft1);
	printf("\n no. of charactor= %d",noc);
	printf("\n no. of space= %d",nos);
	printf("\n no. of lines= %d\n",nol);
	fp=fopen("d:\\vishal\\kasturi.txt","r");
	ft=fopen("d:\\vishal\\vish.txt","r");
	while((m=fgetc(fp))!=EOF)
	{
		putchar(m);
	}
	fclose(fp);
	while((n=fgetc(ft))!=EOF)
	{

		putchar(n);
	}
	fclose(ft);
	getch();

}

