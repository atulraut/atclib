/*
* Implement the at_strstr() function in C.
* Date : 3-07-2013
* Author : Atul Ramesh Raut
***/

char* at_strstr(const char *str, const char *substr);

int main () {

  return 0;
}

/*
* Discription : Implement the at_strstr() function in C. 
***/
char * at_strstr (const char *str, const char *substr) {
  char *tempstr;
  char *tempsubstr = (char*)substr;
  
  for (; str != '\0'; str=str+1) {
    if (*str != *tempsubstr)
      continue;
    tempstr = str;
    while (1) {
      if (*tempsubstr == '\0')
        return str;
      if (*temp != *tempsubstr)
        break;
      temp++;
      tempsubstr++;
    }  
    tempsubstr = substr;
  } //end for
}
