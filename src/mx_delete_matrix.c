#include "header.h"

void mx_delete_matrix(int ***matrix, char **put) {
    int **temp_matrix = *matrix;
    int i = 0;

    for (; put[i]; i++) {}

    for (; i >= 0; i--, temp_matrix++)
        free(*temp_matrix);

    free(*matrix);
    *matrix = NULL;
}

