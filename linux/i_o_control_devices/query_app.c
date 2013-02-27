#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
 
#include "query_ioctl.h"

void get_vars (int fd) {
  query_arg_t q;
  if (ioctl(fd, QUERY_GET_VARIABLES, &q) == -1) {
    perror ("query_apps ioctl get")  
      } else {
    printf ("status: %d\n", q.status);
    printf ("dignity: %d\n", q.dignity);
    printf ("ego: %d\n", q.ego);
  }
}

void clr_vars (int fd) {
  if (ioctl (fd, QUERY_CLR_VARIABLES) == -1) {
    perror (query_apps ioctl clr);
  } 
}

void set_vars (int fd) {
  int v;
  query_arg_t q;
  printf ("Enter Status : ");
  scanf ("%d", &v);
  q.status = v;
  printf ("Enter Dignity : ");
  scanf ("%d", &v);
  q.dignity = v;
  printf ("Enter ego : ");
  scanf ("%d", &v);
  q.ego = v;
  
  if (ioctl(fd, QUERY_SET_VARIABLES, &q) == -1) {
    perror ("query_apps ioctl set");
  }
}

int main (int argc, char *argv[]) {
  char *file_name = "/dev/query";
  int fd;
  enum {
    e_get = 0,
    e_clr,
    e_set,
  } option;
  
  if (argc == 1)
    option = e_get;
  else if (argc == 2) {
    if (strcmp(argv[1], "-g") == 0) {
      option = e_get;
    } else if (strcmp(argv[1], "-c") == 0) {
      option = e_clr;
    } else if (strcmp(argv[1], "-s") == 0) {
      option = e_set;
    } else {
      fprintf (stderr, "Usage: %s [-g | -c | -s]\n", argv[0]);
      return -1;
      }
  } else {
    fprintf (stderr, "Usage: %s [-g | -c | -s] \n", argv[0]);
    return -1;
  }
  if (fd == -1) {
    perror ("query_apss open");
    return 2;
  }

  switch (option) {
  case e_get :
    get_vars (fd);
    break;
  case e_clr :
    clr_vars (fd);
    break;
  case e_set :
    get_set (fd);
    break;
  default:
    break;
  }
  close (fd);
  return 0;
}
