/*
Every email consists of a local name and a domain name, separated by the @ sign.
For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.
Besides lowercase letters, these emails may contain '.'s or '+'s.
If you add periods ('.') between some characters in the local name part of an email address,
mail sent there will be forwarded to the same address without dots in the local name.
For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.
(Note that this rule does not apply for domain names.)
If you add a plus ('+') in the local name, everything after the first plus sign will be ignored.
This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded
to my@email.com.  (Again, this rule does not apply for domain names.)
It is possible to use both of these rules at the same time
Given a list of emails, we send one email to each address in the list.  How many different
addresses actually receive mails?
Example 1:
Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* unique_email_address(char *str) {
  int i=0, j=0, len=0, cnt=0, flag=0, k=0;
  char *domain = "gmail.com";
  len = strlen(str);
  for(i=0; i<len; i++) {
    if(str[i] == '.')
      continue;
    if(str[i] == '@')
      break;
    if(str[i] == '+')
      continue;

    if(str[i] < 97)
      str[i] = str[i] + 97;

    str[j] = str[i];
    j++;
  }

  if(str[i] == '@') {
    k = i;
    while(str[i] != '\0') {
      cnt++; i++;
    }
  }

  len = strlen(domain);
  printf("cnt=%d len=%d \n", (cnt-1), len);
  if((cnt-1) == len) {
	flag = 0;
  } else {
	flag = 1;
	printf("Cant send email to this address\n");
	return NULL; 
  }

  i = k;
  if(!flag) {
   while(str[i] != '\0') {
     str[j] = str[i];
     j++; i++;
   }
   str[j] = '\0';
  }
  return str;
}

int main() {
//  char str[] = "atul.r@gmail.com";
//  char str[] = "atul+r@gmail.com";
//  char str[] = "test.e.mail+bob.cathy@gmail.com";
//  char str[] = "testemail+david@gmai.tcode.com";
  char *str1[] = {"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"};
  char *ret;
  printf (" ip --> %s \n", str);
  ret = unique_email_address(str);
  printf (" op --> %s \n", ret);
  return 0;
}
