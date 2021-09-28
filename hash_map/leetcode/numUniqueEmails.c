/***
    929. Unique Email Addresses

    Every valid email consists of a local name and a domain name,
    separated by the '@' sign. Besides lowercase letters,
    the email may contain one or more '.' or '+'.

    For example, in "alice@leetcode.com", "alice" is the
    local name, and "leetcode.com" is the domain name.
    If you add periods '.' between some characters in the
    local name part of an email address, mail sent there
    will be forwarded to the same address without dots in
    the local name. Note that this rule does not apply to
    domain names.

    For example, "alice.z@leetcode.com" and "alicez@leetcode.com"
    forward to the same email address.
    If you add a plus '+' in the local name, everything after the
    first plus sign will be ignored. This allows certain emails
    to be filtered. Note that this rule does not apply to domain names.

    For example, "m.y+name@email.com" will be forwarded to "my@email.com".
    It is possible to use both of these rules at the same time.

    Given an array of strings emails where we send one email to each
    email[i], return the number of different addresses that
    actually receive mails.

    Input: emails = ["test.email+alex@leetcode.com",
    "test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
    Output: 2
    Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com"
    actually receive mails.

    Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
    Output: 3

    Constraints:
    1 <= emails.length <= 100
    1 <= emails[i].length <= 100
    email[i] consist of lowercase English letters, '+', '.' and '@'.
    Each emails[i] contains exactly one '@' character.
    All local and domain names are non-empty.
    Local names do not start with a '+' character.

    https://leetcode.com/problems/unique-email-addresses/

    Date: 27 Sept 2021
    Fair Oaks, CA.
*/

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

#define TABLE_SIZE 100
#define MAX_EMAIL_LEN 100

struct Node {
  char email[MAX_EMAIL_LEN];
  struct Node *next;
} Node;

struct Node *hashTable[TABLE_SIZE];

int hashCal(char *str) {
  int myhash = 5831;
  char c;
  while(c==*str++) {
    myhash = (((myhash<<5)+myhash)+c) % TABLE_SIZE;
  }
  return myhash % TABLE_SIZE;
}

void mystrcpy(char *dst, char *src) {
  int i=0;
  while(src[i])
    {
      dst[i]=src[i];
      i++;
    }
  dst[i]='\0';
}

int count;
int mystrcmp(char *str1, char *str2) {
  int i=0;
  while(str1[i] && str2[i]) {
    if(str1[i]!=str2[i])
      break;
    i++;
  }
  //printf("string compare : str1=%s and str2=%s and comp value = %d\n",str1,str2,str1[i]-str2[i]);
  return str1[i]-str2[i];
}

struct Node *getNode(char *email) {
  struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
  mystrcpy(temp->email,email);
  temp->next = NULL;
  return temp;
}

void init() {
  count = 0;
  for(int i=0; i<TABLE_SIZE; i++) {
    hashTable[i] = NULL;
  }
}

struct Node *searchInHash(char *email) {
  int hash_key = hashCal(email);
  //printf("hash_key in search is =%d\n",hash_key);
  struct Node *res = hashTable[hash_key];
  while(res !=NULL) {
    if(0==mystrcmp(res->email,email))
      return res;
    res = res->next;
  }
  return NULL;
}

void insertHash(char *email) {
  struct Node *res = searchInHash(email);
  int key = hashCal(email);
  printf("key and email are %d %s\n",key,email);
  if(res!=NULL)
    printf("search is %s\n",res->email);
  if(res==NULL) {
    if(hashTable[key] == NULL) {
      hashTable[key] = getNode(email);
    } else {
      struct Node *newnode = getNode(email);
      newnode->next = hashTable[key];
      hashTable[key] = newnode;
    }
    printf("inserted email in hash = %s\n",email);
    count++;
  }
}

char *preprocess(char *email) {
  char *tmp = (char*)malloc(sizeof(char) * 100);
  memset(tmp, '\0', sizeof(tmp));
  int i= 0;
  int j = 0;
  int k = 0;

  while(email[i]) {
    if(email[i]=='+')
      k=1;
    if(email[i]=='@') {
      tmp[j]=email[i];
      j++;
      i++;
      break;
    }
    if(email[i]!='.' && k==0) {
      tmp[j]=email[i];
      j++;
    }
    i++;
  }
  while(email[i]) {
    tmp[j]=email[i];
    j++;
    i++;
  }
  tmp[j]='\0';
  return tmp;
}

int numUniqueEmails(char ** emails, int emailsSize) {
  char *temp;
  init();
  for(int i=0; i<emailsSize; i++) {
    temp = NULL;
    // printf("string before preprocess = %s\n",emails[i]);
    temp = preprocess(emails[i]);
    //printf("inserting keystring in hash = %s\n",temp);
    insertHash(temp);
  }
  return count;
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
