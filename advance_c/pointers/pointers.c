#include <stdio.h>
#include <string.h>

//Example for the 'Function pointers' section.
static char *(*get_strcpy_ptr(void))(char *dst, const char *src);

//Examples for the 'Strings' section.
static size_t strlen1(const char *str);
static size_t strlen2(const char *str);

int main(void) {
	//I use these blocks ({}) for scoping. In particular, there are two 'foo_ptr' variables here, of different types. They must be in separate scopes.
	{
		//----------------------------------------------------------------------
		/*Starting off*/

		int foo = 3;
		int *foo_ptr = &foo; //foo_ptr is a pointer to foo; its type is int * (pointer to int)
		printf("Value of foo: %d\n", foo);
		printf("Address of foo: %p\n", &foo);
		printf("Value of foo_ptr (= &foo): %p\n", foo_ptr);
		puts("---");

		//----------------------------------------------------------------------
		/*Declaration syntax*/

		//This way is evil:
		int* ptr_a, ptr_b;
		//Type of ptr_b is int - NOT int *!
		//Only ptr_a is actually a pointer.

		//Better way:
		int *ptr_c, ptr_d; //ptr_d is more clearly not a pointer
		int ptr_e, *ptr_f; //Even clearer here

		//Ultimate clarity
		int  ptr_g;
		int *ptr_h;

		//Gratuitous parentheses are allowed around the asterisk and variable name in a declaration.
		int ((not_a_pointer)), (*ptr_i), (((*ptr_j)));

		//----------------------------------------------------------------------
		/*Assignment and pointers*/

		//This line elicits a warning in gcc:
		foo_ptr = 42;
		//Remember that foo_ptr is (was) a pointer to foo.
		//You might have expected that this line would set foo to 42 through the pointer, but it doesn't.
		//Instead, we changed the pointer that's in foo_ptr; foo is unchanged. What changed is that foo_ptr no longer points to foo; it points into random wilderness.
		printf("foo (after  foo_ptr = 42): %i (note that foo is unchanged)\n", foo); //Prints 3 (see?)

		//----------------------------------------------------------------------
		/*Dereferencing*/

		foo_ptr = &foo;
		*foo_ptr = 42; //This is what we meant to do (note dereference operator, prefix *)
		printf("foo (after *foo_ptr = 42): %i\n", foo); //Prints 42

		int bar = *foo_ptr; //Dereference as read; bar now == 42

		puts("---");

		//----------------------------------------------------------------------
		/*Interlude: Arrays*/

		//Here's an array:
		int array[] = { 45, 67, 89 };

		//Now, we try to refer to this array:
		printf("array: %p\n", array); //Prints some hexadecimal string like 0x12307734
		//But %p means 'pointer'. We used a pointer to the array's first element (&array[0]) here. The array, you see, decayed to a pointer.

		int *array_ptr = array;
		//Equivalently:
		array_ptr = &array; //This & is implicit in the first method
		array_ptr = &array[0];

		//This equivalence doesn't hold for pointer variables, only array variables. See what happens when we try it with a pointer variable:
		int **array_ptr_ptr;
		array_ptr_ptr = array_ptr; //This will warn, because we are assigning a pointer of a different type: An int * value (array_ptr) to an int ** variable (array_ptr).
		array_ptr_ptr = array; //Same here: array decays to int *, but this variable holds int **.
		array_ptr_ptr = &array_ptr; //Valid: &array_ptr is a pointer to a variable holding a pointer to an int.
		array_ptr_ptr = &array_ptr[0]; //This will warn, because &array_ptr[0], like array_ptr itself, is an int *.

		//----------------------------------------------------------------------
		/*Pointer arithmetic (or: why 1 == 4)*/

		printf(" first element: %i\n", *(array_ptr++));
		printf("second element: %i\n", *(array_ptr++));
		printf(" third element: %i\n", *array_ptr);
		/*output:
		 * first element: 45
		 *second element: 67
		 * third element: 89
		 */
		//Each ++ expression adds 1 to the variable. But in fact, the pointer moves more than 1 byte, because it is an int pointer (it moves sizeof(int) bytes). The amount added (1) is multiplied by the size (sizeof(int)) of the type of the pointer (int).

		//If it was a void pointer (void *), the multiplier would be 1.

		putchar('\n'); //blank line

		//----------------------------------------------------------------------
		/*Indexing*/

		printf("array[0]: %i (first element)\n", array[0]); //Prints 45
		//Believe it or not, the subscript operator has nothing to do with arrays.
		//Remembering that the type of the pointer is int, array[0] == array + (0 * sizeof(int)).

		//A better example:
		/*int array[] = { 45, 67, 89 };
		 *int *array_ptr;
		 */
		array_ptr = &array[1];
		puts("array_ptr = &array[1]");
		printf("array_ptr[1]: %i (last element)\n", array_ptr[1]); //Prints 89

		putchar('\n'); //blank line

		//Stated diagrammatically:
		puts(" 0  1  2 <- indices into array");
		puts("    0  1 <- indices into array_ptr");
		puts("-- -- --");
		puts("45 67 89 <- values in the actual array");

		puts("---");
	}

	{
		//----------------------------------------------------------------------
		/*Interlude: Structures and unions*/

		struct foo {
			size_t size;
			char name[64];
			int answer_to_ultimate_question;
			unsigned shoe_size;
		} my_foo;
		//Direct structure access.
		my_foo.size = sizeof(struct foo);

		struct foo *foo_ptr = &my_foo;
		printf("Address of my_foo: %p\n", &my_foo);
		printf("Value of foo_ptr (= &my_foo): %p\n", foo_ptr);
		putchar('\n'); //blank line

		//This is the way we already know about:
		(*foo_ptr).size = sizeof(struct foo);
		//But there's a better way:
		foo_ptr->size = sizeof(struct foo);
		//Same thing, but shorter.

		//More levels of indirection make it uglier:
		struct foo **foo_ptr_ptr = &foo_ptr;
		(**foo_ptr_ptr).size = sizeof(struct foo);
		(*foo_ptr_ptr)->size = sizeof(struct foo);

		//The Pascal way (sigh):
		//foo_ptr_ptr^^.size := new_size;

		printf("my_foo.size: %zu\n", my_foo.size);
		putchar('\n'); //blank line
		printf("(*foo_ptr).size: %zu\n", (*foo_ptr).size);
		printf("foo_ptr->size: %zu\n", foo_ptr->size);
		putchar('\n'); //blank line

		printf("Address of foo_ptr: %p\n", &foo_ptr);
		printf("Value of foo_ptr_ptr (= &foo_ptr): %p\n", foo_ptr_ptr);
		putchar('\n'); //blank line

		printf("(**foo_ptr_ptr).size: %zu\n", (**foo_ptr_ptr).size);
		printf("(*foo_ptr_ptr)->size: %zu\n", (*foo_ptr_ptr)->size);

		puts("---");
	}

	//--------------------------------------------------------------------------
	/*Multiple indirection*/

	int    a =  3;
	int   *b = &a;
	int  **c = &b;
	int ***d = &c;

	  *d ==   c; //Dereferencing an (int ***) once gets you an (int **) (3 - 1 = 2)

	//Note: C does not support chaining comparisons (e.g., a == b == c); each relational operator only compares two operands at a time. So, for one example, (a == b == c) is actually ((a == b) == c).
	//In the examples below, this is a comparison of an integer (the result of the first comparison) to a pointer (the other term of the second comparison). This is not what I'd intended, and both GCC and Clang rightly warn about it.
	//I've maintained the chained-comparison style below for clarity, but commented the lines out to show that such expressions are to be disfavored.

	//Dereferencing an (int ***) twice, or an (int **) once, gets you an (int *) (3 - 2 = 1; 2 - 1 = 1):
	// **d ==  *c ==  b;

	//Dereferencing an (int ***) thrice, or an (int **) twice, or an (int *) once, gets you an int (3 - 3 = 0; 2 - 2 = 0; 1 - 1 = 0):
	//***d == **c == *b == a == 3;

	//Thus, the & operator can be thought of as adding asterisks (or 'increasing pointer level'), and the * and [] operators as removing asterisks ('decreasing pointer level').

	printf("Address of a: %p\n", &a);
	printf("Value of b (= &a): %p\n", b);
	putchar('\n'); //blank line
	printf("Address of b: %p\n", &b);
	printf("Value of  c (= &b): %p\n",  c);
	printf("Value of *c (= &a): %p\n", *c);
	putchar('\n'); //blank line
	printf("Address of c: %p\n", &c);
	printf("Value of   d (= &c): %p\n",  d);
	printf("Value of  *d (= &b): %p\n",  *d);
	printf("Value of **d (= &a): %p\n", **d);
	putchar('\n'); //blank line
	printf("Value of a = *b = **c = ***d: %i\n", a);

	puts("---");

	//--------------------------------------------------------------------------
	/*Pointers and const*/

	//The placement of the const keyword matters:
	const int *ptr_a; //Here, the int (*ptr_a) is const. '*ptr_a = 42' is illegal.
	int const *ptr_b; //Same as ptr_a.
	int *const ptr_c; //Here, the pointer (ptr_b) is const. '*ptr_c = 42' is legal, but '++ptr_c' is not.
	//Note the similarity of ptr_b and ptr_c. The first is equivalent to ptr_a; only the last is a different type where the pointer, not the int, is constant. Be sure which one you mean.

	//--------------------------------------------------------------------------
	/*Function pointers*/
	{
		enum { str_length = 18U }; //Remember the NUL terminator!
		char src[str_length] = "This is a string.", dst[str_length];

		//Functions decay to pointers, the same as arrays do.
		//When you call a function, you really call an address.
		strcpy(dst, src); //The function call operator in action. Notice the function pointer on the left side.

		//Function pointers are declared similarly to variables, but with parentheses in order to separate the * indicating a pointer from the zero or more * in the return type.

		//char *strcpy(char *dst, const char *src); //An ordinary function declaration, for reference
		char *(*strcpy_ptr)(char *dst, const char *src); //Pointer (indicated by inner *) to strcpy-like function

		strcpy_ptr =  strcpy; //Decay: implicit &
		strcpy_ptr = &strcpy; //This works the same
		//strcpy_ptr = &strcpy[0]; //But not this

		//Even with the parameter names removed, this is still the same type as strcpy_ptr.
		char *(*strcpy_ptr_noparams)(char *, const char *) = strcpy_ptr;

		//Type of strcpy_ptr: char *(*)(char *dst, const char *src)
		//You use this in a cast:
		void *my_strcpy = strcpy; //Imagine that you got this somewhere else (e.g. that my_strcpy was a function parameter)
		strcpy_ptr = (char *(*)(char *dst, const char *src))my_strcpy;

		//As you might expect, a pointer to a pointer to a function has two asterisks inside of the parentheses:
		char *(**strcpy_ptr_ptr)(char *, const char *) = &strcpy_ptr;

		//And we can have an array of function-pointers:
		char *(*strcpies[3])(char *, const char *) = { strcpy, strcpy, strcpy };
		char *(*strcpies2[])(char *, const char *) = { strcpy, strcpy, strcpy }; //Array size is optional, same as ever

		strcpies[0](dst, src);

		//Here's a pathological declaration, taken from the C99 standard.
		/*'[This declaration] declares a function f with no parameters returning an int,
		 * a function fip with no parameter specification returning a pointer to an int,
		 * and a pointer pfi to a function with no parameter specification returning an int.'
		 *(6.7.5.3[16])
		 */
		int f(void), *fip(), (*pfi)();
		/*Equivalent to:
		int f(void);
		int *fip();   //Function returning int pointer
		int (*pfi)(); //Pointer to function returning int
		 */

		//A function pointer can even be the return value of a function.
		//char *(*get_strcpy_ptr(void))(char *dst, const char *src);
		strcpy_ptr = get_strcpy_ptr();

		//Because function pointer syntax is so mind-bending, most developers use typedefs to abstract them:
		typedef char *(*strcpy_funcptr)(char *, const char *);

		strcpy_funcptr strcpy_ptr2 = strcpy;
		//strcpy_funcptr get_strcpy_ptr(void);
	}

	//--------------------------------------------------------------------------
	/*Strings (and why there is no such thing)*/

	char str[] = "I am the Walrus";
	/*This array (str) is 16 bytes (16 chars) long.
	 *The 'string' is 15 characters.
	 *The last element of the array (str[15]) is 0, called 'NUL' in ASCII.
	 *Thus it is called the 'NUL terminator', because it signals the end of the string.
	 *But, aside from string literal syntax ("foo"), this is just an idiom.
	 *The idiom is also supported by C's 'string library' (the contents of string.h).
	 */
	size_t len = strlen(str); //len = 15
	printf("str: %s\n", str);
	printf("Your library's strlen: %zu\n", len);
	printf("Demonstration strlen (strlen1) using pointer arithmetic: %zu\n", strlen1(str));
	printf("Demonstration strlen (strlen2) using indexing: %zu\n", strlen2(str));

	return 0;
}

static char *(*get_strcpy_ptr(void))(char *dst, const char *src) {
	return strcpy;
}

static size_t strlen1(const char *str) { //Note the pointer syntax here
	//Remember, there is no 'string' here. There is only an array of characters, of which the last one is 0.
	size_t len = 0U;
	while(*(str++)) ++len; //When *str is 0, the loop exits.
	return len;
}
static size_t strlen2(const char *str) {
	size_t i;
	for(i = 0U; str[i]; ++i);
	//When the loop exits, i is the length of the string.
	return i;
}
