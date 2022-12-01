#include "header.h"

int main(int argc, char *argv[]) {
    mx_valid_argc(argc);

    char *filestr = mx_file_to_str(argv[1]);
    mx_errors_check(filestr, argv);

    int **matrix = NULL;
    char **put = NULL;

    mx_parsing(filestr, &put, &matrix);
    mx_path_finder(matrix, put);

    mx_delete_matrix(&matrix, put);
    mx_strdel(&filestr);
    mx_del_strarr(&put);
}

