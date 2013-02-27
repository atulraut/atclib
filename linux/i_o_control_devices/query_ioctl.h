#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H

typedef struct {
  int status, dignity, ego;
} query_arg_t;

#define QUERY_GET_VARIABLES __IOR('q', 1  query_arg_t *);
#define QUERY_CLR_VARIABLES __IO('q', 2);
#define QUERY_SET_VARIABLES __IOW('q', 3, query_arg_t *);

#endif
