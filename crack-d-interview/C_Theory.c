
Volatile : 
What is difference : 
const volatile int *ptr1;  
*const volatile int ptr2; 
Error volatile will tell the compiler not to optimise code related the variable const will tell the compiler that it is restrict for the 
program to modify the variable's value. it means that the program cannot modify the variable's value, but the value can be modified from
the outside, thus no optimisations will be performed on the variable.
