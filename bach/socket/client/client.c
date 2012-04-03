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
  char buf[256];
  
  struct sockaddr sockaddr;
  int formlen;
  
  sd = socket (AF_UNIX, SOCK_STREAM, 0);

  /* connect to name - null char is not part of name */
  if (connect (sd, "sockname", sizeof ("sockname") - 1) == -1)
    exit (0);

  write (sd, "Hi Atul this is Client Code !", 27);
}
