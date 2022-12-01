#include "header.h"

int mx_counter(char **arr) {
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
            for (int k = n - 1; k >= 0; k--) {
                if (mx_strcmp(arr[n], arr[k]) == 0)
                    break;
                if (k == 0)
                    i++;
            }
            
            n++;
        }

        n = 1;
    }

    return i;
}

int mx_test(char *arr, char **put) {
    int i = 0;

    while (put[i]) {
        if (mx_strcmp(arr, put[i]) == 0)
            return 1;
        
        i++;
    }

    return 0;
}

void mx_put_check(char ***arr, char ***put) {
    char **temp_arr = *arr;
    char **temp_put = *put;

    for (int i = 0; *temp_arr;) {
        if (mx_isdigit(**temp_arr))
            temp_arr++;
        if (*temp_arr) {
            if (mx_test(*temp_arr, temp_put) == 0) {
                temp_put[i] = mx_strdup(*temp_arr);
                temp_put[i + 1] = NULL;
                i++;
            }

            temp_arr++;
        }
    }
}

void mx_put(char ***put, char ***arr) {
    int i = mx_counter(*arr);
    *put = (char **)malloc((i + 1) * sizeof(char *));
    **put = NULL;

    mx_put_check(&(*arr), &(*put));
}

