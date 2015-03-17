# Introduction to C #

By Denis Richie

# C #

Start :
  * `int main (argc, argv) () {} ` : Where argc, (for argument count) is the number of command-line arguments the program was invoked with;
the second (argv, for argument vector) is a pointer to an array of character strings that contain the arguments, one per string.

  * Error message : Lvalue required in function main.
> > Anything which can change is called lvalue in compiler's language.


# All about Arrays #

  * Array of pointer          : `int *array [ 30 ] ;`

  * Pointers to Array         : `int *array [10];`

  * Array of Function Pointer : `int (*fp[4]) (int, int);`

# How to initialize a struct in ANSI C #

typedef struct MY\_TYPE {

> boolean flag;

> short int value;

> double stuff;

} MY\_TYPE;

void function(void) {
> MY\_TYPE a;

> a = { true, 15, 0.123 }
}