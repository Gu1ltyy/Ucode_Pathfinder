#include "header.h"

void mx_inv_num_check(char **arr, char *line) {
    int i = 0;
    int n = 1;

    if (arr && *arr) {
        if (arr[0])
            i++;
        while (arr[i] != NULL) {
            if (mx_isdigit(arr[n][0]))
                n++;
            if (arr[n] == NULL)
                break;

            int k = n - 1;
            while (k >= 0) {
                if (mx_strcmp(arr[n], arr[k]) == 0)
                    break;
                if (k == 0)
                    i++;
                k--;
            }
            n++;
        }
        n = 1;
    }

    if (i == 0 || i == 1 || i != mx_atoi(line)) {
        mx_printerr("error: invalid number of islands\n");
        exit(1);
    }
}

void mx_dup_briges_check(char **temp_arr, int i) {
    int j = 0;

    while (j < i - 3) {
        if ((mx_strcmp(temp_arr[i - 2], temp_arr[j]) == 0 && mx_strcmp(temp_arr[i - 3], temp_arr[j + 1]) == 0) ||
            (mx_strcmp(temp_arr[i - 3], temp_arr[j]) == 0 && mx_strcmp(temp_arr[i - 2], temp_arr[j + 1]) == 0)) {
            mx_printerr("error: duplicate bridges\n");
            exit(1);
        }

        j += 3;
    }
}

void mx_island_reader(char *line, char **island_1, char **island_2, char **d) {
    char *temp_line = line;
    int i = 0;

    while (temp_line[i] != '-')
        i++;
    
    *island_1 = mx_strndup(temp_line, i);
    i++;
    temp_line += i;
    i = 0;

    while (temp_line[i] != ',')
        i++;

    *island_2 = mx_strndup(temp_line, i);
    i++;
    temp_line += i;
    i = 0;

    while (temp_line[i] != '\0')
        i++;

    *d = mx_strndup(temp_line, i);
}

void mx_fill_arr(char ***arr, char **line) {
    char *island_1 = NULL;
    char *island_2 = NULL;
    char *d = NULL;
    char **temp_arr = *arr;
    int n = 1;
    int i = 0;

    for (; line[n]; n++) {
        mx_island_reader(line[n], &island_1, &island_2, &d);
        
        if (mx_strcmp(island_1, island_2) == 0 && mx_atoi(d) != 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(n + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        temp_arr[i++] = mx_strdup(island_1);
        temp_arr[i++] = mx_strdup(island_2);
        temp_arr[i++] = mx_strdup(d);

        mx_strdel(&island_1);
        mx_strdel(&island_2);
        mx_strdel(&d);
    }

    mx_inv_num_check(*arr, *line);
    mx_dup_briges_check(temp_arr, i);
}

void mx_create_arr(char **line, char ***arr) {
    int i = 1;

    for (; line[i]; i++) {}

    *arr = (char **)malloc((i * 3 + 1) * sizeof(char *));

    mx_fill_arr(&(*arr), line);
}

