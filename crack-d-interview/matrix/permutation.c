#include <stdio.h>
#define SIZE 3
#define N 5

void permute(char list[],int k, int m);
	
int main(char *argv[],int argc)
{
	char list[3]={'a','b','c'};
	char list2[5]={'a','b','c','d','e'};

	int i,j,k;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			for(k=0;k<SIZE;k++)
				if(i!=j && j!=k && i!=k)
					printf("%c%c%c\n",list[i],list[j],list[k]);
	permute(list2,0,N);
	return(0);
}

void permute(char list[],int k, int m) {
	int i;
	char temp;
	if(k==m) {
                /* PRINT A FROM k to m! */
		for(i=0;i<N;i++) {
			printf("%c",list[i]);
		}
		printf("\n");
	} else {
		for(i=k;i<m;i++) {
			/* swap(a[i],a[m-1]); */
			temp=list[i];
			list[i]=list[m-1];
			list[m-1]=temp;
			permute(list,k,m-1);
			/* swap(a[m-1],a[i]); */
			temp=list[m-1];
			list[m-1]=list[i];
			list[i]=temp;
		}
	}
}


/*
Output :
  abc
  acb
  bac
  bca
  cab
 cba
*/
