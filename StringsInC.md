# Introduction to Stings in C #

Data from various books including Denis Ritichie


# Strings in C #

How to deal with String char array and pointer:
  * `char amessage[] ` = "now is the time"    /**an array**/
  * `char *pmessage  ` = "now is the time"    /**a pointer**/

  * amessage : `*--->` `[now is the time\0]`
  * pmessage : `[now is the time\0]`

amessage is an array, just big enough to hold the sequence of characters
and '\0' that initializes it. Individual characters within the array may be
changed but amessage will always refer to the same storage. On the other hand, pmessage is a pointer, initialized to point to a string constant, the pointer may be subsequently be modified to point elsewhere, but the result is undefined if you try to modify the contents.

# Array of Pointers #

  * Name as an Array of 3 Pointers
```
char *Name[3] = {
    "Australia",
    "Afganistan",
    "India"
}

```

`  (*Name)[3] ` : Declares Name as a pointer to an array of 3 elements.

` *(name[i]+j) ` : To access j'th character in i'th name