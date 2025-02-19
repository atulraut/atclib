/***
    Parser for Compiler Using Stack

    Ref : https://www.cquestions.com/2010/10/c-interview-questions-and-answers.html

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun 15 Sep 2024 11:47:44 AM PDT
    Folsom, CA.

    To run Program -
    a.out
    char *(*c[10]) (int **p);

    Credit - Expert C Programming: Deep C Secrets by Peter van der Linden (Author)
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

#define MAXTOKENS 100
#define MAXTOEKNLEN 64

enum type_tag {IDENTIFIER, QUALIFIER, TYPE};

struct token {
  char type;
  char string[MAXTOEKNLEN];
};

int top=-1;
struct token stack[MAXTOKENS];
struct token this;

#define atclib_pop stack[top--]
#define atclib_push(s) stack[++top]=s

/* figure out hte identifier type */
enum type_tag atclib_classify_string(void) {
  char* s = this.string;

  if(!strcmp(s, "const")) {
    strcpy (s, "read-only");
    return QUALIFIER;
  }

  if (!strcmp(s, "volatile") )
    return QUALIFIER;
  if (!strcmp(s, "void") )
    return TYPE;
  if (!strcmp(s, "char") )
    return TYPE;
  if (!strcmp(s, "signed") )
    return TYPE;
  if (!strcmp(s, "unsigned") )
    return TYPE;
  if (!strcmp(s, "short") )
    return TYPE;
  if (!strcmp(s, "int") )
    return TYPE;
  if (!strcmp(s, "long") )
    return TYPE;
  if (!strcmp(s, "float") )
    return TYPE;
  if (!strcmp(s, "double") )
    return TYPE;
  if (!strcmp(s, "struct") )
    return TYPE;
  if (!strcmp(s, "union") )
    return TYPE;
  if (!strcmp(s, "enum") )
    return TYPE;

  return IDENTIFIER;
}

/* rad next token into "this" */
void  atclib_gettoken (void) {

  char* p = this.string;

  /* read past any spaces */
  while ( (*p = getchar() ) == ' ' )
    ;

  if (isalnum(*p)) {
    /* it start with A-Z, 0-9 read in identifier */
    while ( isalnum(*++p = getchar() ) )
      ;

    ungetc(*p, stdin);
    *p = '\0';
    this.type =  atclib_classify_string();

    return;
  }

  if (*p == '*') {
    strcpy (this.string, "pointer to");
    this.type = '*';
    return;
  }
  this.string[1] = '\0';
  this.type = *p;

  return;
}

/* The piece of code taht understandeth all parsing .. */
void  atclib_read_to_first_identifier () {

  atclib_gettoken ();

  while (this.type != IDENTIFIER) {
    atclib_push(this);
    atclib_gettoken();
  }
  printf ("%s is ", this.string);
  atclib_gettoken();
}

void  atclib_deal_with_arrays () {
  while (this.type == '[') {
    printf ("Array ");
    atclib_gettoken (); /* a number or ']' */
  }
  if (isdigit(this.string[0])) {
    printf ("0..%d ", atoi(this.string)-1);
    atclib_gettoken(); /* read ths ']' */
  }
  atclib_gettoken(); /* read next past the ']' */
  printf ("of ");
}

void  atclib_deal_with_function_args() {
  while (this.type != ')' ) {
    atclib_gettoken();
  }
  atclib_gettoken();
  printf ("function returning ");
}

void atclib_deal_with_pointers () {
  while (stack[top].type == '*') {
    printf ("%s ", atclib_pop.string);
  }
}

void atclib_deal_with_declarator () {
  /* deal with possible array/function following the idetifier */
  switch (this.type) {
  case '[':
    atclib_deal_with_arrays();
    break;
  case '(':
    atclib_deal_with_function_args();
    //  break;//doubt
  }
  atclib_deal_with_pointers ();

  /* Process toekn that we stacked while reading to identifier */
  while (top >= 0) {
    if (stack[top].type == '(') {
      atclib_pop;
      atclib_gettoken (); /* read past ')' */
      atclib_deal_with_declarator();
    } else {
      printf ("%s ", atclib_pop.string);
    }
  }
}

void test() {
  debug("Enter !");
  /* put token s on stack until we reach identifier */
  atclib_read_to_first_identifier ();

  atclib_deal_with_declarator ();
  printf ("\n");
  return;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[182] [test] :| Enter !
   char *(*c[10]) (int **p);
   c is Array 0..9 of pointer to function returning pointer to char
**/
