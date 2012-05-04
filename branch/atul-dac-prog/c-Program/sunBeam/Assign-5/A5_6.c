#include<stdio.h>
#include<conio.h>
void main()
{
	int dd, mm, yy, j,yr1=0,yr2=0;
	int msum=0,ysum,total,odd;
	char arr[7][20] = {"Sunday", "Monday", "Thuesday", "Wendsday", "Thursday", "Friday", "Saturday"};
	int l_mm1[12] = {30, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int l_mm2[12] = {30, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	printf("Enter date format(dd-mm-yy) :");
	scanf("%d%d%d",&dd, &mm, &yy);
	for(j=1;j<yy;j++)
	{
		if(j % 4 == 0)
			yr1++;	
		else 
			yr2++;
	}
	ysum = (yr1 * 2) + (yr2 * 1);
	for(j=0; j<mm-1; j++)
	{
		if(yy % 4 == 0)
			msum = msum + l_mm1[j];
		else
			msum = msum + l_mm2[j];
	}
	total = ysum + msum + dd;
	odd = total%7;
	printf("\nThe day is %s \n",arr[odd]);
}
