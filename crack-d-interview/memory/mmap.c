/*
Ref : https://en.wikipedia.org/wiki/Mmap (copy paste from wiki)
https://en.wikipedia.org/wiki/Demand_paging
https://www.quora.com/How-are-mmap-ioremap-and-kmap-different
https://stackoverflow.com/questions/1739296/malloc-vs-mmap-in-c
*/
#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Does not work on OS X, as you can't mmap over /dev/zero */
int main(void) {
  const char str1[] = "ATUL 1";
  const char str2[] = "RAUT 2";
  int parpid = getpid(), childpid;
  int fd = -1;
  char *anon, *zero;

  if ((fd = open("/dev/zero", O_RDWR, 0)) == -1)
    err(1, "open");

  /*
  user space processes can't access device memory directly for security purpose. 
  So, user space processes use the mmap system call to ask kernel to map the 
  device into virtual address space of the calling process. 
  */
  anon = (char*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
  zero = (char*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  if (anon == MAP_FAILED || zero == MAP_FAILED)
    errx(1, "either mmap");
  /*
  After the mapping the user space process can write directly into the device memory
  via the returned address.
  */
  strcpy(anon, str1);
  strcpy(zero, str1);

  printf("PID %d:\t [A]anonymous %s, zero-backed %s\n", parpid, anon, zero);
  switch ((childpid = fork())) {
  case -1:
    err(1, "fork");
    /* NOTREACHED */
  case 0:
    childpid = getpid();
    printf("PID %d:\t [T]anonymous %s, zero-backed %s\n", childpid, anon, zero);
    sleep(3);

    printf("PID %d:\t [U]anonymous %s, zero-backed %s\n", childpid, anon, zero);
    munmap(anon, 4096);
    munmap(zero, 4096);
    close(fd);
    return EXIT_SUCCESS;
  }

  sleep(2);
  strcpy(anon, str2);
  strcpy(zero, str2);

  printf("PID %d:\t [L]anonymous %s, zero-backed %s\n", parpid, anon, zero);
  munmap(anon, 4096);
  munmap(zero, 4096);
  close(fd);
  return EXIT_SUCCESS;
}
