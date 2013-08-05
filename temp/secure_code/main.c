#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

int main (int argc, char **argv) {
  /*  int i;
  char *buf;
  printf ("argv[1]= %s\n", argv[1]);
  int size = atol (argv[1]);
  printf ("size = %d", size);
  buf = (char*) malloc (size);
  printf ("buf = %d\n", size);
  for (i=0; i < size; i++) {
    buf[i] = getchar();
    printf ("buf[%d] = %c\n",i, buf[i]);
  }
  buf[size] = '\0';
*/

  // prog 2.
  register char *sp;
  char line[512];
  struct sockaddr _in sin;
  int i, p[2], pid, status;
  FILE *fp;
  char *av[4];
  
  i = sizeof (sin);
  printf ("i=%d\n", i);
  if (getpeername(0, &sin, &i) < 0)
    fatal (argv[0], "getpeername");
  line[0] = '\0';
  gets(line);
  sp = line;
}
