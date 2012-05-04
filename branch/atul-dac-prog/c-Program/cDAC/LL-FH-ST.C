#include<stdio.h>
#include<conio.h>
#include<string.h>

typedef struct node
{
   char *word;
   struct node *next;
} NODE;

NODE *head=NULL;
void addfirst(char *);
NODE * createnode(char*);
void display();

FILE *fp,*fs;

void main()
{

	char buff[200];
	clrscr();
	fp=fopen("d:\\veeresh\\lotus5.txt","r+");
	if(fp==NULL)
	{
	  printf("\n file couldn't be opened");
	  getch();
	  exit();
	}
	while(fgets(buff,sizeof(buff),fp)!=NULL)
	{
	  addfirst(buff);
	}
	display();
fclose(fp);
getch();
}

NODE *createnode(char *word)
{
  NODE *nn;
  nn=malloc(sizeof(NODE));
  strcpy(nn->word,word);
  nn->next=NULL;
  return nn;
}

void addfirst(char *word)
{
   NODE *newnode=createnode(word);
   newnode->next=head;
   head=newnode;

}
void display()
{
  NODE *trav;
  trav=head;
  if(head==NULL)
    printf("\n there is no data to display");
  else
  {
     while(trav!=NULL)
	{
	    printf("\n%s",trav->word);
	   trav=trav->next;

	}
  }
}