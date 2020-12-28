#include <stdio.h>
#include <stdlib.h>

void foo () {
	char *str[] = {"Mercury", "Venus", "Earth", "Mars",
		"Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
	for (int i=0; i<9; i++)
		if (str[i][0] == 'M')
			printf ("%s begins with M \n", str[i]);
}

/*
	Modifying a string literal seems harmelss enough. Why
	does it cause undefined behaviour ?
	--> Some compilers try to reduce memory requirements by
	storing single copies of identical string liternals.
	Consider below example:
	char *p = "abc", *q = "abc";
	A compiler might choose to store "abc" just once,
	making both p and q point to it. If we were to change
	"abc" through the pointer p, the string that q points
	to would also be affected. Needless to say, this could
      lead to some annoying bugs. Another potential problem
	is thta string literals might be stored in a
	"READ-ONLY" area of memory; A program that attempts to
	modify such a literal will simply crash.
***/
void zoo() {
	char *p = "abc";
	char *q = "abc";
	printf ("[%s] p=%s q=%s \n", __func__, p, q);
	printf ("[%s] p=%p q=%p \n", __func__, p, q);
}
/*
	=> ./a.out
	[zoo] p=abc q=abc
	[zoo] p=0x4007a4 q=0x4007a4
***/

void coo() {
	char *p = "abc";
	char *q = "abc";
	printf ("[%s] p=%s q=%s \n", __func__, p, q);
	q[1] = 'B';
	printf ("[%s] p=%p q=%p \n", __func__, p, q);
}
/*
	=> ./a.out
	[zoo] p=abc q=abc
	[zoo] p=0x400814 q=0x400814
	[coo] p=abc q=abc
	Segmentation fault (core dumped)
***/

void koo() {
  int i, j;
  char s[10];
  scanf("%d%s%d", &i, s, &j);
  printf ("%d%s%d\n", i, s, j);
}

void joo() {
  char s[] = "Hsjodi", *p;
  for (p=s; *p; p++)
    --*p;
  puts(s);
}

int func(char *s, char *t) {
  char *p1, *p2;
  for (p1=s; *p1; p1++) {
    for (p2=t; *p2; p2++)
      if (*p1 == *p2)
	break;
    if (*p2 == '\0')
      break;
  }
  return p1 - s;
}
/*
  => ./a.out
  Grinch
  [main] --> 3
  [main] --> 0
***/

int main() {
  //foo();
  //	zoo();
  //	coo();

  //	koo();
  joo();

  printf ("[%s] --> %d \n", __func__, func("abcd", "babc"));
  printf ("[%s] --> %d \n", __func__, func("abcd", "bcd"));
  return 0;
}
