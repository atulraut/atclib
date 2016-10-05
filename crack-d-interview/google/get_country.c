/*
 * Q1: How would you select a country where the probability of being selected was
 * proportional to its population?
 * by Google
 * Author - https://www.careercup.com/question?id=14582824
 * Oct 3, 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *get_country (char *countries[], int *population, int size);

int main () {
  int i, size;
  char *ret;
  char *countries[] = {"Taiwan", "Koria", "Mexico", "india", "USA", "China"};
  int population[] = {2, 3, 4, 10, 11, 20};
  size = sizeof(countries)/sizeof (countries[0]);
  for (i=0; i<6; i++) {
    ret = get_country (countries, population, size);
    printf ("ret = %s\n", ret);
  }
  return 0;
}

char *get_country (char *countries[], int *population, int sz) {
  int i, fst, mid, key, end;
  int *count;
  count = (int *)malloc (sizeof(sz));
  count[0] = population[0];
  for(i=1; i<sz; i++)
    count[i] = count[i-1] + population[i];
  key = 1 + rand() % count[sz-1];
  printf ("key=%d, cnt=%d \n", key, count[sz-1]);
  fst = 0;
  end = sz-1;
  while (fst <= end) {
    mid = fst + (end-fst)/2;
    if (count[mid] < key)
      fst = mid + 1;
    else
      end = mid - 1;
  } // end while
  free(count);
  return countries[fst];
}
