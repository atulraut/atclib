/*
* Aim : Server-Client communication !
* Author : Atul R. Raut
* Date   : Maon 02-04-2012 11:45PM
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int main () {
  int sd, ns;
  char but[256];;
  struct sockaddr sockaddr;
  int fromlen;

  sd = socket (AF_UNIX, SOCK_STREAM, 0);

  /* bind name = dont include null char in the system*/
  bind (sd, "sockname", sizeof ("sockname") - 1);
  
  listen (sd, 1);

  for (;;) {
    ns = accept (sd, &sockadd, &fromlen);
  
    if (fork () == 0) {
      /* child */
      close (fd);
      read (ns, buf, sizeof (buf));
      printf ("\nAT:: server read :: %s\n", buf);
      exit ();
    }
    close (ns);
  }
    
}
