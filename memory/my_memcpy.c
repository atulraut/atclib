/* memcpy example
   Credit/Ref: http://www.danielvik.com/2010/02/fast-memcpy-in-c.html
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // 'uint8_t
#include <inttypes.h>

// void * memcpy ( void * destination, const void * source, size_t num );
void* mymemcpy(void* dest, const void* src, size_t count);
void *mymemmove(void *dest, void const *src, size_t n);

struct {
  char name[3];
  int age;
} person, person_copy;

/*
 * Ref: http://www.danielvik.com/2010/02/fast-memcpy-in-c.html
***/
void* mymemcpy(void* dest, const void* src, size_t count) {
        char* dst8 = (char*)dest;
        char* src8 = (char*)src;
        //printf ("InSide mymemcpy:: src = %s, cnt = %d \n", src, count);
        while (count--) {
            *dst8++ = *src8++;
        }
        //printf ("InSide mymemcpy:: dest = %s \n", dest);
        return dest;
}

/*
 * Ref: http://c-faq.com/ansi/memmove.html
 ***/
void *mymemmove(void *dest, void const *src, size_t n) {
    register char *dp = dest;
	register char const *sp = src;
	if(dp < sp) {
		while(n-- > 0)
			*dp++ = *sp++;
	} else {
		dp += n;
		sp += n;
		while(n-- > 0)
			*--dp = *--sp;
	}

	return dest;
}

int main () {
  char myname[] = "Atul R Raut";

  printf("Size of char : %d\n",sizeof(char));
  printf("Size of char : %d\n",sizeof(person.name));
  printf("Size of int  : %d\n",sizeof(int));
  printf("Size of stuct: %d\n",sizeof(person));

  /* using memcpy to copy string: */
  mymemcpy ( person.name, myname, strlen(myname)+1 );
  person.age = 24;
  /* using memcpy to copy structure: */
  mymemcpy ( &person_copy, &person, sizeof(person) );
  printf ("main::memcpy  : person.name: %s \n", person.name);
  printf ("main::memcpy  : person_copy: %s, %d \n", person_copy.name, person_copy.age );

  mymemcpy ( person.name, myname, strlen(myname)+1 );
  person.age = 24;
  mymemcpy( &person_copy, &person, sizeof(person));
  printf ("main::memcpy  : person_copy: %s, %d \n", person_copy.name, person_copy.age );
  mymemmove ( &person_copy, &person, sizeof(person) );
  printf ("main mymemmove: person_copy: %s, %d \n", person_copy.name, person_copy.age );

  mymemcpy ( &person_copy, &person, sizeof(person) );
  printf ("main::imemcpy : person_copy: %s, %d \n", person_copy.name, person_copy.age );

  return 0;
}

/*Output :
Size of char : 1
Size of char : 3
Size of int  : 4
Size of stuct: 8
memcpy  : person.name: Atul
main::memcpy  : person_copy: Atul, 24
main::memcpy  : person_copy: Atul, 24
main mymemmove: person_copy: Atul, 24
main::imemcpy : person_copy: Atul, 24
*/
