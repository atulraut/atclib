/*
   Program for Naive Pattern Searching algorithm
*/

#include <stdio.h>
#include <string.h>
#include "../../at_lib.h"

void search_pattern(char* pat, char* txt) {
  int M = strlen(pat);
  int N = strlen(txt);

  /* A loop to slide pat[] one by one */
  for (int i = 0; i <= (N - M); i++) {
    int j;

    /* For current index i, check for pattern match */
    for (j = 0; j < M; j++)
      if (txt[i + j] != pat[j])
	break;

    if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
      debug("Pattern found at index %d", i);
  }
}

int main() {
  char txt[] = "AABAACAADAABAAABAA";
  char pat[] = "AABA";
  search_pattern(pat, txt);
  return 0;
}

/***
    => ./a.out
    [pattern_matching.c] [search_pattern()] L=23 :Pattern found at index 0
    [pattern_matching.c] [search_pattern()] L=23 :Pattern found at index 9
    [pattern_matching.c] [search_pattern()] L=23 :Pattern found at index 13
*/
