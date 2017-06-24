/*
* WAP for Insertion Sort
*/
#include <stdio.h>

void insertionSort(int list[], int n);
int main() {
    printf("Insertion Sort!\n");
    int i, sz;
    
    int list[] = {57, 48, 79, 65, 15, 33, 53};
    sz = sizeof(list)/sizeof(list[0]);
    printf("Original Array \n");
    for(i=0; i<sz; i++)
        printf ("->[%d]", list[i]);
    printf("\n");
    insertionSort(list, sz);
    printf("Sorted Array \n");
    for(i=0; i<sz; i++)
        printf ("->[%d]", list[i]);
    printf("\n");
    return 0;
}


void insertionSort(int list[], int n) {
	// sort list[0] to list[n-1] in ascedning order
	for(int h=1; h<n; h++) {
		int key = list[h];
		int k=h-1; // start comparing with previous item
		while(k>=0 && key < list[k]) {
			list[k+1] = list[k];
			--k;
		}
		list[k+1] = key;
	}//end for 
}//end insertionSort

/*
Insertion Sort!
Original Array 
->[57]->[48]->[79]->[65]->[15]->[33]->[53]
Sorted Array 
->[15]->[33]->[48]->[53]->[57]->[65]->[79]
*/
