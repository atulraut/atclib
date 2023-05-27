/***
    Hard: https://leetcode.com/problems/word-search-ii/
    Word Search II
    Given an m x n board of characters and a list of
    strings words, return all words on the board.

    Each word must be constructed from letters of
    sequentially adjacent cells, where adjacent cells
    are horizontally or vertically neighboring. The
    same letter cell may not be used more than once
    in a word.

    Input: board = [["o","a","a","n"],["e","t","a","e"],
    ["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
    Output: ["eat","oath"]

    Input: board = [["a","b"],["c","d"]], words = ["abcb"]
    Output: []

    Constraints:

    m == board.length
    n == board[i].length
    1 <= m, n <= 12
    board[i][j] is a lowercase English letter.
    1 <= words.length <= 3 * 104
    1 <= words[i].length <= 10
    words[i] consists of lowercase English letters.
    All the strings of words are unique.

    Date: 10/8/21 - Note 108 - Hindu Magic Number
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

struct TrieNode {
	int c;
	int isWord;
	struct TrieNode* children[26];
};

typedef struct TrieNode TrieNode;

/** Initialize your data structure here. */
struct TrieNode* trieCreate() {
	TrieNode* root = (TrieNode*)malloc(sizeof(TrieNode));
	root->c = -1;
	for (int i = 0; i < 26; i++)
		root->children[i] = 0;
	root->isWord = 0;
	return root;
}

/** Inserts a word into the trie. */
void insert(struct TrieNode* root, char* word, int idx) {
	TrieNode*node, *targetNode = root;
	for (int i = 0; i < strlen(word); i++) {
		if (targetNode->children[word[i] - 'a']) {
			targetNode = targetNode->children[word[i] - 'a'];
		}
		else {
			targetNode->children[word[i] - 'a'] = (TrieNode*)malloc(sizeof(struct TrieNode));
			targetNode = targetNode->children[word[i] - 'a'];
			targetNode->isWord = 0;
			for (int i = 0; i < 26; i++)
				targetNode->children[i] = 0;
		}
	}
	targetNode->c = idx;
	targetNode->isWord = 1;
}

/** Returns if the word is in the trie. */
bool search(struct TrieNode* root, char* word) {
	TrieNode* targetNode = root;
	for (int i = 0; i < strlen(word); i++) {
		targetNode = targetNode->children[word[i] - 'a'];
		if (!targetNode)
			return false;
	}

	return (targetNode->isWord ? true : false);
}


/** Returns if there is any word in the trie
that starts with the given prefix. */
int startsWith(struct TrieNode* root, char* word, int* idx) {
	TrieNode* targetNode = root;
	for (int i = 0; i < strlen(word); i++) {
		targetNode = targetNode->children[word[i] - 'a'];
		if (!targetNode)
			return 0;
	}
	if (targetNode->isWord) {
		*idx = targetNode->c;
		return 2;
	}
	else {
		*idx = -1;
		return 1;
	}
}

/** Deallocates memory previously allocated for the TrieNode. */
void trieFree(struct TrieNode* root) {
	if (!root)
		return;

	for (int i = 0; i < 26; i++) {
		trieFree(root->children[i]);
	}
	free(root);
}

void searchWords(struct TrieNode* dict, char** board, int boardRowSize, int boardColSize,
	int row, int col, char* str, int strSize, char** result, int* returnSize) {
	int res = 0;
	int idx = 0;
	if (row >= boardRowSize || row < 0 || col < 0 || col >= boardColSize)
		return;

	if (board[row][col] < 0) {
		return;
	}

	str[strSize] = board[row][col];
	str[strSize + 1] = '\0';

	board[row][col] *= -1;

	res = startsWith(dict, str, &idx);
	if (!res) {
		board[row][col] *= -1;
		return;
	}
	else if (res == 1) {

	}
	else {
		if (!result[idx]) {
			char* t = (char*)malloc(sizeof(char)*(strlen(str) + 1));
			strcpy(t, str);
			result[idx] = t;
			(*returnSize)++;
		}
		//printf("\n%s", str);
	}

	searchWords(dict, board, boardRowSize, boardColSize, row + 1, col, str, strSize + 1, result, returnSize);
	searchWords(dict, board, boardRowSize, boardColSize, row - 1, col, str, strSize + 1, result, returnSize);
	searchWords(dict, board, boardRowSize, boardColSize, row, col - 1, str, strSize + 1, result, returnSize);
	searchWords(dict, board, boardRowSize, boardColSize, row, col + 1, str, strSize + 1, result, returnSize);

	board[row][col] *= -1;
}

void backTracking(struct TrieNode* dict, char** board, int boardRowSize, int boardColSize,
	char** result, int* returnSize) {
	char* str = (char*)malloc(sizeof(char)*boardRowSize*boardRowSize);
	str[0] = '\0';
	*returnSize = 0;
	for (int i = 0; i < boardRowSize; i++) {
		for (int j = 0; j < boardColSize; j++) {
			searchWords(dict, board, boardRowSize, boardColSize, i, j, str, 0, result, returnSize);
		}
	}
}

char** findWords(char** board, int boardRowSize, int boardColSize, char** words, int wordsSize, int* returnSize) {
    if (!boardRowSize || !boardColSize || !wordsSize) {
		*returnSize = 0;
		return 0;
	}

	struct TrieNode* dict = trieCreate();
	char** result = (char**)malloc(wordsSize*sizeof(char*));
	for (int i = 0; i < wordsSize; i++) {
		char* word = words[i];
		insert(dict, word, i);
		result[i] = 0;
	}
	backTracking(dict, board, boardRowSize, boardColSize, result, returnSize);
	trieFree(dict);
	if (*returnSize == 0) {
		free(result);
	}
	else {
		int idx = 0;
		for (int i = 0; i < wordsSize; i++) {
			if (result[i]) {
				result[idx] = result[i];
				idx++;
			}
		}
	}
	return result;
}

int main (int argc, char **argv) {
  char** ret = 0;

   char* board[] = {
     "oaan",
     "etae",
     "ihkr",
     "iflv"
  };
   char* words[] = {
     "oath",
     "pea",
     "eat",
     "rain"
   };

  int boardRowSize = 4;
  int boardColSize = 4;
  int wordsSize = 4;
  int returnSize;

  ret = findWords(board, boardRowSize, boardColSize, words, wordsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", ret[i]);
  return 0;
}

/**

 **/
