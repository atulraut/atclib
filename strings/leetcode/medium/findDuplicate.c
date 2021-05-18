/***
    Medium: 609. Find Duplicate File in System
    https://leetcode.com/problems/find-duplicate-file-in-system/

    Given a list paths of directory info, including the directory path, and all the files
    with contents in this directory, return all the duplicate files in the file system
    in terms of their paths. You may return the answer in any order.

    A group of duplicate files consists of at least two files that have the same content.

    A single directory info string in the input list has the following format:

    "root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

    It means there are n files (f1.txt, f2.txt ... fn.txt) with content (f1_content,
    f2_content ... fn_content) respectively in the directory "root/d1/d2/.../dm".
    Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the
    root directory.

    The output is a list of groups of duplicate file paths. For each group,
    it contains all the file paths of the files that have the same content.
    A file path is a string that has the following format:

    "directory_path/file_name.txt"

    Input: paths = ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)","root 4.txt(efgh)"]
    Output: [["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]

    Input: paths = ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)"]
    Output: [["root/a/2.txt","root/c/d/4.txt"],["root/a/1.txt","root/c/3.txt"]]

    Constraints:

    1 <= paths.length <= 2 * 104
    1 <= paths[i].length <= 3000
    1 <= sum(paths[i].length) <= 5 * 105
    paths[i] consist of English letters, digits, '/', '.', '(', ')', and ' '.
    You may assume no files or directories share the same name in the same directory.
    You may assume each given directory info represents a unique directory.
    A single blank space separates the directory path and file info.

    Follow up:
    Imagine you are given a real file system, how will you search files? DFS or BFS?
    If the file content is very large (GB level), how will you modify your solution?
    If you can only read the file by 1kb each time, how will you modify your solution?
    What is the time complexity of your modified solution? What is the most
    time-consuming part and memory-consuming part of it? How to optimize?
    How to make sure the duplicated files you find are not false positive?

    Date: 18 May 2021.
    San Diego, CA.
    Status: Pending
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

struct am {
  char *content;
  int n;
};

void insf(struct am *m, int *n, char ***dups, char *content, char *fpath) {
  int i;
  for (i = 0; i < *n && strcmp(m[i].content, content); i++)
    ;
  m[i].content = content;
  m[i].n++;
  i == *n ? ++*n : 0;
  dups[i] = realloc(dups[i], sizeof(char *[m[i].n]));
  dups[i][m[i].n - 1] = fpath;
  debug("AR");
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** findDuplicate(char **paths, int pathsSize, int* returnSize, int** returnColumnSizes) {
  int n = 0, k = 0, sz = 20000;
  char ***dups = calloc(1, sizeof(char **[sz])), fpath[128], *space, *dir, *fname, *oparen, *content;
  struct am *m = calloc(1, sizeof(struct am[sz]));
  debug("AR");

  for (int i = 0 ; i < pathsSize ; i++) {
    debug("AR=%s", paths[i]);
    (space = strchr(dir = paths[i], ' ')) ? *space = 0 : 0;
    debug("AR");
    debug("AR=%s", space);
    while (space) {
      (space = strchr(fname = space + 1, ' ')) ? *space = 0 : 0;
      *(oparen = strchr(fname, '(')) = 0;
      *strchr(content = oparen + 1, ')') = 0;
      snprintf(fpath, sizeof fpath, "%s/%s", dir, fname);
      insf(m, &n, dups, content, strdup(fpath));
    }
  }
  debug("AR");
  for (int i = 0, *c = *returnColumnSizes = malloc(sizeof(int [n])) ; i < n ; i++)
    m[i].n > 1 ? c[k] = m[i].n, dups[k++] = dups[i] : (free(dups[i][0]), free(dups[i]));

  return free(m), *returnSize = k, dups;
}

int main () {
  int ret = 0;
  char *paths[] = {"root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)","root 4.txt(efgh)"};
  int pathsSize = sizeof(paths)/sizeof(paths[0]);
  int returnSize;
  int* returnColumnSizes;

  char ***io = findDuplicate(paths, pathsSize, &returnSize, &returnColumnSizes);

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
