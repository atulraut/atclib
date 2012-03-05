#include <stdio.h>

int main() {
  char input_str[20];
  char *output_str;

  strncpy(input_str, "Hello", 20);
  printf("input_str: %s\n", input_str);

  /* Reset string */
  memset(input_str, '\0', sizeof( input_str ));

  strncpy(input_str, "Hello", 2);
  printf("input_str: %s\n", input_str);

  /* Reset string */
  memset(input_str, '\0', sizeof( input_str ));
  output_str = strncpy(input_str, "World", 3);

  printf("input_str: %s\n", input_str);
  printf("output_str: %s\n", output_str);

  return 0;
}
