/*
* Aim : Server-Client communication !
* Author : Atul R. Raut
* Date   : Mon 06-04-2012 01:10PM
* Source : http://www.cs.cf.ac.uk/Dave/C/node28.html#SECTION002800000000000000000
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define NSTRS 3               /* No. of strings */
#define ADDRESS "AtulSocket"  /*addr to connect */

/*
* Strings we send to the clinet
*/
char *strs[NSTRS] = {"Rahul\n", "Ramesh\n", "Raut\n"};

int main () {
	char c; 
	FILE *fp;
	int fromlen;
	register int i, s, ns, len;
	struct sockaddr_un saun, fsaun;

	/*
       * Get a socket to work with. This socket will
       * be in the UNIX domain, and will be a stream socket.
       */
	if ((s = socket (AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror ("server : socket");
		exit (1);
	} 
	/*
	* Create the address  we will be binding to.
	*/
	saun.sun_family = AF_UNIX;
	strcpy (saun.sun_path, ADDRESS);

	/*
       * Try to bind the address to the socket. We unlink
       * the name first so that the bind won't fall.
       * The third argument indicates the "lengh" of the 
       * structure, not just the lengh of the socket name.
       */
	unlink (ADDRESS);
	len = sizeof (saun.sun_family) + strlen (saun.sun_path);
	
	if (bind(s, &saun, len) < 0) {
		perror ("server : bind");
		exit (1);
	}
	/* Listen on the socket */
	if (listen (s, 5) < 5) {
		perror ("server : listen");
		exit (1);
	}
	/*
        * Accept connections. When we accept one, ns will be
	* connected to the client. fasun wil contain the address
	* of the client. 
	*/
	if (ns = accept (s, &fsaun, &fromlen) < 0) {
		perror ("server : accept ");
		exit (1);
	}
	/* We'll use stdio for reading the socket. */
	fp = fopen (ns, "r");
	/* First we send some strings to the client. */
	for (i=0; i <NSTRS; i++) {
		while ((c = fgetc(fp)) != EOF) {
			putchar(c);
			if (c == '\n')
				break;
		}
	}

	close (s);
	exit (0 );
}
