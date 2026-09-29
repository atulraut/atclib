/**
   11. Parse command-line/configuration strings safely

   Tue Sep 29 07:19:22 PDT 2026
   Folsom, CA, USA
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
  int port;
  int timeout;
  int debug;
} config_t;

static int parse_int(const char *str, int *value) {
  char *end;
  long v;

  if (str == NULL || *str == '\0')
    return -1;

  errno = 0;
  v = strtol(str, &end, 10);

  /* No digits */
  if (end == str)
    return -1;

  /* Extra garbage: "123abc" */
  if (*end != '\0')
    return -1;

  /* strtol overflow */
  if (errno == ERANGE)
    return -1;

  /* Doesn't fit into int */
  if (v < INT_MIN || v > INT_MAX)
    return -1;

  *value = (int)v;
  return 0;
}

int parse_config(const char *input, config_t *cfg) {
  char buf[256];

  if (input == NULL || cfg == NULL)
    return -1;

  /* Prevent buffer overflow */
  if (strlen(input) >= sizeof(buf))
    return -1;

  memcpy(buf, input, strlen(input) + 1);

  char *saveptr = NULL;
  char *token = strtok_r(buf, ",", &saveptr);

  while (token != NULL) {

    char *equal = strchr(token, '=');

    if (equal == NULL)
      return -1;

    *equal = '\0';

    char *key   = token;
    char *value = equal + 1;

    if (*key == '\0' || *value == '\0')
      return -1;

    int v;

    if (parse_int(value, &v) != 0)
      return -1;

    if (strcmp(key, "port") == 0) {
      if (v < 1 || v > 65535)
	return -1;
      cfg->port = v;

    } else if (strcmp(key, "timeout") == 0) {
      if (v < 0)
	return -1;

      cfg->timeout = v;

    } else if (strcmp(key, "debug") == 0) {
      if (v != 0 && v != 1)
	return -1;

      cfg->debug = v;

    } else {
      /* Unknown option */
      return -1;
    }
    token = strtok_r(NULL, ",", &saveptr);
  }
  return 0;
}


int main(void) {
  config_t cfg = {
    .port = 80,
    .timeout = 10,
    .debug = 0
  };

  const char *input =
    "port=8080,timeout=30,debug=1";

  if (parse_config(input, &cfg) != 0) {
    fprintf(stderr, "Invalid configuration\n");
    return 1;
  }

  printf("port    = %d\n", cfg.port);
  printf("timeout = %d\n", cfg.timeout);
  printf("debug   = %d\n", cfg.debug);

  return 0;
}

/**
   port    = 8080
   timeout = 30
   debug   = 1
**/
