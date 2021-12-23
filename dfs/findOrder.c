/***
    Course Schedule II

    There are a total of numCourses courses you have to take, labeled
    from 0 to numCourses - 1. You are given an array prerequisites
    where prerequisites[i] = [ai, bi] indicates that you must take
    course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you
    have to first take course 1.
    Return the ordering of courses you should take to finish all courses.
    If there are many valid answers, return any of them. If it is impossible
    to finish all courses, return an empty array.

    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: [0,1]
    Explanation: There are a total of 2 courses to take. To take course 1
    you should have finished course 0. So the correct course order is [0,1].

    Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    Output: [0,2,1,3]
    Explanation: There are a total of 4 courses to take. To take course 3 you
    should have finished both courses 1 and 2. Both courses 1 and 2 should be
    taken after you finished course 0.
    So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

    Input: numCourses = 1, prerequisites = []
    Output: [0]

    Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= numCourses * (numCourses - 1)
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    ai != bi
    All the pairs [ai, bi] are distinct.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/22/21 Palindrom Date
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/
struct Node {
  int course;
  struct Node* next;
};

void InsertAdjList(struct Node **head, int course) {
  struct Node *NewNode = (struct Node *) malloc(sizeof(struct Node));
  NewNode->course = course;
  NewNode->next = *head;
  *head = NewNode;
}

void PushStack(struct Node **top, int course) {
  struct Node *NewNode = (struct Node *) malloc(sizeof(struct Node));
  NewNode->course = course;
  NewNode->next = *top;
  *top = NewNode;
}

void PopStack(struct Node **top) {
  if(*top == NULL)
    return;

  struct Node *temp = *top;
  *top = (*top)->next;
  free(temp);
}

#define TargetCourse 0
#define Prerequisite 1

#define White 0   // to be checked
#define Gray  1   // under checking
#define Black 2   // checked

void DFS(struct Node **AdjList, int course, struct Node **top, int *Color, bool *Cycle) {
  struct Node* List = AdjList[course];

  if(Color[course] == Black)  // already checked and pushed to the stack
    return;

  if(Color[course] == Gray) {  // found a cycle
    *Cycle = true;
    return;
  }

  Color[course] = Gray;   // mark as under checking

  while(List != NULL) {
    DFS(AdjList, List->course, top, Color, Cycle);
    List = List->next;
  }

  Color[course] = Black;   // mark as checked
  PushStack(top, course);
}

int* findOrder(int CourseCount, int** Array, int RowSize, int* ColumnSize, int* CourseOrderSize) {
  int *Color = NULL;
  bool Cycle = false;

  struct Node **AdjList = (struct Node **) malloc(sizeof(struct Node *) * CourseCount);

  for(int c = 0 ; c<CourseCount; c++) {
    AdjList[c] = NULL;
  }

  for(int r=0; r<RowSize; r++) {
    InsertAdjList(&AdjList[Array[r][Prerequisite]], Array[r][TargetCourse]);
  }

  Color = (int *) calloc(CourseCount, sizeof(int));
  struct Node *top = NULL;

  for(int c=0; c<CourseCount; c++)
    DFS(AdjList, c, &top, Color, &Cycle);

  free(AdjList[0]);
  free(AdjList);
  free(Color);

  int *CourseOrder = (int *) malloc(sizeof(int) * CourseCount);

  for(int c=0; c<CourseCount; c++) {
    CourseOrder[c] = top->course;
    PopStack(&top);
  }

  if(Cycle) {
    *CourseOrderSize = 0;
    free(CourseOrder);
    return NULL;
  }

  *CourseOrderSize = CourseCount;
  return CourseOrder;
}

int** create_matrix(int rows, int cols) {
  int** max = (int **)malloc(sizeof(int) * rows );
  for (int i=0; i<rows; ++i)
    max[i] = (int *) malloc(sizeof(int *) * cols);

  return max;
}
int main (int argc, char **argv) {
  int *ret;
  int RowSize = 4;
  int ColumnSize = 2;
  int CourseCount = 4;
  int CourseOrderSize;
  int **prerequisites = create_matrix(RowSize, ColumnSize);

  //[[1,0],[2,0],[3,1],[3,2]]

  *(*(prerequisites + 0) + 0) = 1;
  *(*(prerequisites + 0) + 1) = 0;

  *(*(prerequisites + 1) + 0) = 2;
  *(*(prerequisites + 1) + 1) = 0;

  *(*(prerequisites + 2) + 0) = 3;
  *(*(prerequisites + 2) + 1) = 1;

  *(*(prerequisites + 3) + 0) = 3;
  *(*(prerequisites + 3) + 1) = 2;

  ret=  findOrder(CourseCount, prerequisites, RowSize, &ColumnSize, &CourseOrderSize);
  for (int i=0; i<CourseOrderSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=199 :Output = 0
   [main] L=199 :Output = 1
   [main] L=199 :Output = 2
   [main] L=199 :Output = 3
**/
