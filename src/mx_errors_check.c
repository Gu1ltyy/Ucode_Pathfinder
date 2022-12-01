#include "header.h"

void mx_line_check(char **line, int n) {
    int i = 0;
    int temp_i = 0;

    for (int temp_n = 1; temp_n <= n; temp_n++, i = 0, temp_i = 0) {
        while (mx_isalpha(line[temp_n][i]))
            i++;
        if (i == 0 || line[temp_n][i] != '-') {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(temp_n + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
        temp_i = i = i + 1;

        while (mx_isalpha(line[temp_n][temp_i]))
            temp_i++;
        if (temp_i - i == 0 || line[temp_n][temp_i] != ',') {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(temp_n + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
        i = temp_i = temp_i + 1;

        while (mx_isdigit(line[temp_n][temp_i]))
            temp_i++;
        if (temp_i - i == 0 || line[temp_n][temp_i] != '\0') {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(temp_n + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
    }
}

void mx_space_check(char **line, char *file) {
    char **temp_line = line;
    char *temp_file = file;
    int i = 0;

    if (*temp_file == '\n') {
        mx_printerr("error: line 1 is not valid\n");
        exit(1);
    }

    for (; *temp_file; temp_file++) {
        if (*(temp_file + 1) == '\n' && *temp_file == '\n') {
            for (; temp_line[i]; i++) {
                
                if (mx_strncmp(temp_file - mx_strlen(temp_line[i]),
                    temp_line[i], mx_strlen(temp_line[i])) == 0) {
                        mx_printerr("error: line ");
                        mx_printerr(mx_itoa(i + 2));
                        mx_printerr(" is not valid\n");
                        exit(1);
                }
            }
        }
    }
}

void mx_line_parsing(char *file) {
    char **line = mx_strsplit(file, '\n');
    int n = 0;

    if (line[0][0] == '0') {
        mx_printerr("error: invalid number of islands\n");
        exit(1);
    }

    while (line[n])
        n++;

    for (int i = 0; line[0][i]; i++) {
        if (!mx_isdigit(line[0][i])) {
            mx_printerr("error: line 1 is not valid\n");
            exit(1);
        }
    }

    mx_line_check(line, n - 1);
    mx_space_check(line, file);
    mx_del_strarr(&line);
}

void mx_errors_check(char *filestr, char **argv) {
    if (!filestr) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(1);
    }
    if (mx_strlen(filestr) == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(1);
    }

    mx_line_parsing(filestr);
}

