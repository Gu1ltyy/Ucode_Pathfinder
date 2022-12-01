#include "header.h"

void mx_parsing(char *filestr, char ***put, int ***matrix) {
    char **line = mx_strsplit(filestr, '\n');
    char **arr = NULL;

    mx_create_arr(line, &arr);
    mx_put(&(*put), &arr);
    *matrix = mx_create_matrix(*put, &arr);

    mx_del_strarr(&line);
    mx_del_strarr(&arr);
}

