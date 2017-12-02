/*
I/P: Write a program to merge two arrays in sorted order, so that if an 
integer is in both the arrays, it gets added into the final array only once.
O/P:
Merge Array !
->[1]->[3]->[4]->[5]->[0]->[6]->[8]->[2]
Sorting Started !
->[0]->[1]->[2]->[3]->[4]->[5]->[6]->[8]
Removed Duplicate Elements! 
->[0]->[1]->[2]->[3]->[4]->[5]->[6]->[8]
*/
#include <stdio.h>
#include <stdlib.h>

void merge_2_array_and_sort(int a[], int b[], int asz, int bsz) {
  int cnt = 0; 
  int temp = 0, flag = 0;
  int ia = 0, ib = 0;
  int total = asz+bsz;
  int final[total];

  printf ("\nMerge Array !\n");
  /* by Thareja */
  while (ia < asz || ib < bsz) {
    if (a[ia] < b[ib]) {
      final[cnt] = a[ia++];
    } else {
      final[cnt] = b[ib++];
    }
    cnt++;
  }
  /*
  while (ia<asz) {
    final[cnt] = a[ia++];
    cnt++;
  }
  while (ib<bsz) {
    final[cnt] = b[ib++];
    cnt++;
  } */
  for (ia=0; ia<total; ia++)
  printf ("->[%d]", final[ia]);
  printf ("\nSorting Started !\n");

  /* BUBBLE sort the array */
  for (ia=0; ia<total-1; ia++) {
    flag = 0;
    for (ib=0; ib<total-1; ib++) {
      if (final[ib] > final[ib+1]) { /* swap 2 next2next element */
	flag = 1;
	temp = final[ib];
	final[ib] = final[ib+1];
	final[ib+1] = temp;
      } // if ends
    }
    if (flag==0)
      break;
  } // for ends

  for (ia=0; ia<total; ia++)
  printf ("->[%d]", final[ia]);
  printf ("\n");
  cnt = 0;
  /* remove duplicates of element */
  for (ia=0; ia<total; ia++) {
    for (ib=ia+1; ib<total;) {
      if (final[ib] == final[ia]) {
	for(cnt=ib; cnt<total-1; cnt++) {
	  if((total-1) == cnt)
	    final[cnt+1] = 0;
	  final[cnt] = final[cnt+1];
	}
        total--;
      } else
	  ib++;
    }
  }
  printf ("Removed Duplicate Elements! \n");
  for (ia=0; ia<total; ia++)
    printf ("->[%d]", final[ia]);
  printf ("\n");
}

int main () {
  int a1sz = 0, b2sz = 0;
  int a1[3] = {1,3,5};
  int b2[5] = {4,6,8,2,1};
  a1sz = sizeof(a1)/sizeof(a1[0]);
  b2sz = sizeof(b2)/sizeof(b2[0]);
  printf ("\nasz=%d, bsz=%d\n", a1sz, b2sz);
  merge_2_array_and_sort(a1,  b2, a1sz, b2sz);
  return 0;
}
