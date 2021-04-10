/***
    535. Encode and Decode TinyURL
    https://leetcode.com/problems/encode-and-decode-tinyurl/
    https://leetcode.com/discuss/interview-question/124658/Design-a-URL-Shortener-(-TinyURL-)-System/

    TinyURL is a URL shortening service where you enter a URL such as
    https://leetcode.com/problems/design-tinyurl and it returns a short
    URL such as http://tinyurl.com/4e9iAk.

    Design the encode and decode methods for the TinyURL service. There
    is no restriction on how your encode/decode algorithm should work
    You just need to ensure that a URL can be encoded to a tiny URL
    and the tiny URL can be decoded to the original URL.

    Date: 25 March 2021.
    San Diego, CA.
*/

// Your functions will be called as such:
// char* s = encode(s);
// decode(s);#
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

void strcopy(char* src, char* dest){
  int i;
  for(i=0;src[i];i++){
    dest[i]=src[i];
  }
  dest[i]=src[i];
}

char lUrl[10000];
char base62[65]= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl) {
  int i;
  char* s = (char*)malloc(sizeof(char)*10);
  for(i=0;i<=7;i++){
    s[i]=base62[longUrl[i]%62];
  }
  s[i]='\0';
  strcopy(longUrl,lUrl);
  return s;
}

/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) {
  return lUrl;
}

int main () {
  char word1[] = "https://leetcode.com/problems/design-tinyurl";
  char *word2;

  word2 = encode(word1);

 debug("Short URL = %s", word2);

 debug("Long UR = %sL", decode(word2));

 return 0;
}

/***
    Algo :
    A URL character can be one of the following
    1) A lower case alphabet [‘a’ to ‘z’], total 26 characters
    2) An upper case alphabet [‘A’ to ‘Z’], total 26 characters
    3) A digit [‘0’ to ‘9’], total 10 characters

    There are total 26 + 26 + 10 = 62 possible characters.

    So the task is to convert a decimal number to base 62 number.

    To get the original long URL, we need to get URL id in the database
    The id can be obtained using base 62 to decimal conversion.
*/
=
/**
   Output :
   => ./a.out
   [main] L=69 :Short URL = Q22Y16VV
   [main] L=71 :Long UR = https://leetcode.com/problems/design-tinyurlL
**/
