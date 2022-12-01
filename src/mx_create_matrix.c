#include "header.h"

void mx_fill(int ***matrix, char **put, char **arr, int size, int root) {
    int **temp_matrix = *matrix;
    int i = 0;

    if (mx_isdigit(arr[root + 1][0])) {
        for(; mx_strcmp(put[i], arr[root - 1]) != 0; i++) {}
        if (temp_matrix[size][i] > mx_atoi(arr[root + 1]) || !temp_matrix[size][i])
            temp_matrix[size][i] = mx_atoi(arr[root + 1]);
    }
    else {
        for(; mx_strcmp(put[i], arr[root + 1]) != 0; i++) {}
        if (temp_matrix[size][i] > mx_atoi(arr[root + 2]) || !temp_matrix[size][i])
            temp_matrix[size][i] = mx_atoi(arr[root + 2]);
    }
}

void mx_find(int ***matrix, char **put, char **arr) {
    int size = 0;
    int root = 0;

    while (put[size]) {
        root = 0;
        while (arr[root]) {
            if (mx_strcmp(put[size], arr[root]) == 0)
                mx_fill(&(*matrix), put, arr, size, root);
            root++;
        }
        size++;
    }
}

int **mx_create_matrix(char **put, char ***arr) {
    int i = 0;
    int j = 0;
    int **matrix = NULL;

    for (; put[i]; i++, j++) {}

    matrix = malloc(sizeof(int *) * i + 1);
    for (; j >= 0; j--)
        matrix[j] = malloc(sizeof(int) * i);
        
    mx_find(&matrix, put, *arr);

    return matrix;
}

