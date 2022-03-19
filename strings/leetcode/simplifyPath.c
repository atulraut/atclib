/***
    https://leetcode.com/problems/simplify-path/
    Simplify Path

    Given a string path, which is an absolute path (starting
    with a slash '/') to a file or directory in a Unix-style
    file system, convert it to the simplified canonical path.

    In a Unix-style file system, a period '.' refers to the
    current directory, a double period '..' refers to the
    directory up a level, and any multiple consecutive
    slashes (i.e. '//') are treated as a single slash '/'.
    For this problem, any other format of periods such
    as '...' are treated as file/directory names.

    The canonical path should have the following format:

    The path starts with a single slash '/'.
    Any two directories are separated by a single slash '/'.
    The path does not end with a trailing '/'.
    The path only contains the directories on the path from
    the root directory to the target file or directory (i.e.,
    no period '.' or double period '..')
    Return the simplified canonical path.

    Input: path = "/home/"
    Output: "/home"
    Explanation: Note that there is no trailing slash after the
    last directory name.

    Input: path = "/../"
    Output: "/"
    Explanation: Going one level up from the root directory is
    a no-op, as the root level is the highest level you can go.

    Input: path = "/home//foo/"
    Output: "/home/foo"
    Explanation: In the canonical path, multiple consecutive slashes
    are replaced by a single one.

    Constraints:
    1 <= path.length <= 3000
    path consists of English letters, digits, period '.', slash '/' or '_'.
    path is a valid absolute Unix path.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Mar 14 22:06:40 PDT 2022
    Folsom, CA.
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct node {
  char *path;
  struct node *prev;
  struct node *next;
};

char* simplifyPath(char* path) {
  char *newpath = malloc(sizeof(char) * 3001);
  int len = strlen(path);
  struct node *stack = NULL;
  struct node *curr = NULL;
  struct node *tail = NULL;
  char c;
  int n = 0;
  int i = 0;
  int totLen = 0;

  for (i = 0; i < len + 1; i++) {
    c = path[i];
    if (c == '/' || c == '\0') {
      path[i] = '\0';
      if (curr) {
	if (!strcmp("..", curr->path)) {
	  /* pop */
	  struct node *tmp = stack;
	  if (tmp) {
	    stack = tmp->next;
	    if (stack) {
	      stack->prev = NULL;
	    } else {
	      tail = NULL;
	    }
	    free(tmp);
	  }
	} else if (strcmp(".", curr->path)) {
	  /* push */
	  if (stack) {
	    stack->prev = curr;
	  } else {
	    tail = curr;
	  }
	  curr->next = stack;
	  stack = curr;
	}
	curr = NULL;
	n = 0;
      }
    } else {
      if (curr == NULL) {
	curr = malloc(sizeof(*curr));
	curr->path = &path[i];
	curr->prev = NULL;
	curr->next = NULL;
      }
      n++;
    }
  } // For Loop Ends
  curr = tail;

  if (!curr) {
    strcpy(newpath, "/");
  }
  char *pos = newpath;
  while (curr) {
    pos += sprintf(pos, "/%s", curr->path);
    curr = curr->prev;
  }

  return newpath;
}

char* simplifyPath_1(char* path) {
  int top = -1;
  int i;
  int j;

  for(i = 0; path[i] != '\0'; ++i) {
    path[++top] = path[i];
    if(top >= 1 && path[top - 1] == '/' && path[top] == '.' && (path[i + 1] == '/' || path[i + 1] == '\0')) {
      top -= 2;
    } else if(top >= 2 && path[top - 2] == '/' && path[top - 1] == '.' && path[top] == '.' && (path[i + 1] == '/' || path[i + 1] == '\0')) {
      for(j = top - 3; j >= 0; --j) {
	if(path[j] == '/') break;
      } if(j < 0) {
	top = -1;
      } else {
	top = j - 1;
      }
    } else if(path[top] == '/' && path[i + 1] == '/')
      --top;
  }
  if(top > 0)  {
    if(path[top] == '/')
      path[top] = '\0';
    else
      path[top + 1] = '\0';
  } else if(top == 0)
    path[top + 1] = '\0';
  else {
    path[0] = '/';
    path[1] = '\0';
  }
  return path;
}

void test() {
  char*  ret = 0;
  char path[] = "/home/";
  ret = simplifyPath(path);
  debug("Output = %s", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
=> ./a.out
[test] L=189 :Output = /home
 **/
