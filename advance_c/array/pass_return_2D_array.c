#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(int (*a)[2]) {
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d\n", a[i][j]);
    }
}

int (*generate())[2] {
    static int arr[][2] = { 11, 22, 33, 44 };
    return arr;
}

int (*fun())[2][3] {
    static int arr[][2][3] = { 11, 22, 33, 44 };
    int(*ptr)[2][3] = arr;
    return arr;
}

int** create_matrix(int rows, int cols) {
    int** mat = (int**) malloc(rows * sizeof(int*));
    int i;
    for (i = 0; i < rows; i++)
        mat[i] = (int*)malloc(cols * sizeof(int));
    return mat;
}

int (*create_sparse_matrix(int rows))[3] {
    int (*mat)[3];
    mat = (int(*)[3]) malloc(rows * 3 * sizeof(int));
    return mat;
}


// sparse matrix: int mat[R][3]; --> row, col, value


int main() {
    int arr[][2] = { 19, 29, 39, 49 };
    // ptr;
    display(arr);
    int (*ptr)[2] = generate();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d\n", ptr[i][j]);
    }
    return 0;
}
