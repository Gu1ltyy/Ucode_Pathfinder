#include "header.h"

void mx_del(t_path **path) {
    t_path *temp = NULL;

    if (path && (*path)) {
        for (; (*path)->next; *path = temp) {
            temp = (*path)->next;
            free(*path);
        }
        if (!(*path)->next && !(*path)->nextPath) {
            free(*path);
            *path = NULL;
            return;
        }
    }
    else
        return;
}

void mx_del_next(t_path **path) {
    t_path *temp = NULL;

    if (path && (*path)) {
        if ((*path)->nextPath != NULL) {
            temp = (*path)->nextPath;
            free(*path);
            *path = temp;
        }
        else {
            free(*path);
            *path = NULL;
            return;
        }
    }
    else
        return;
}

void mx_delete_path(t_path **path) {
    if (path && (*path)) {
        while(*path) {
            mx_del(&(*path));
            mx_del_next(&(*path));
        }
    }
    else
        return;
}

