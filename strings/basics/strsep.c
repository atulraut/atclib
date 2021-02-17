/***
    https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/lib/string.c?h=v4.4.217
    http://c-faq.com/lib/strtok.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * strpbrk - Find the first occurrence of a set of characters
 * @cs: The string to be searched
 * @ct: The characters to search for
 */
char *strpbrk(const char *cs, const char *ct) {
	const char *sc1, *sc2;

	for (sc1 = cs; *sc1 != '\0'; ++sc1) {
		for (sc2 = ct; *sc2 != '\0'; ++sc2) {
			if (*sc1 == *sc2)
				return (char *)sc1;
		}
	}
	return NULL;
}

/**
 * strsep - Split a string into tokens
 * @s: The string to be searched
 * @ct: The characters to search for
 *
 * strsep() updates @s to point after the token, ready for the next call.
 *
 * It returns empty tokens, too, behaving exactly like the libc function
 * of that name. In fact, it was stolen from glibc2 and de-fancy-fied.
 * Same semantics, slimmer shape. ;)
 */
char *strsep(char **s, const char *ct) {
	char *sbegin = *s;
	char *end;

	if (sbegin == NULL)
		return NULL;

	end = strpbrk(sbegin, ct);
	if (end)
		*end++ = '\0';
	*s = end;
	return sbegin;
}

int main() {

  char str[] = "Marco:Q:2F7PKC";
  char *token1, *token2, *token3;
  char *r = malloc(30);

  strcpy(r, str);

  token1 = strsep(&r, ":");
  token2 = strsep(&r, ":");
  token3 = strsep(&r, ":");

  printf("tok1 = %s\n", token1);
  printf("tok2 = %s\n", token2);
  printf("tok3 = %s\n", token3);

  free(r);
  r = NULL;

  return 0;

}

/***
    => ./a.out
    tok1 = Marco
    tok2 = Q
    tok3 = 2F7PKC
*/
