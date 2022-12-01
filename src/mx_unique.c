#include "header.h"

void mx_compareto(t_path **new, t_path **old, int *check) {
    if (*new && *old) {
        if ((*new)->id != (*old)->id || (*new)->d != (*old)->d)
            *check = 1;
    }
    else if (!(*new) || !(*old))
        *check = 1;
}

int mx_unique(t_path **new, t_path **cur) {
    t_path *temp = *new;
    t_path *old = *cur;
    int check = 0;

    for (; old; temp = temp->next) {
        if (!temp || old->next == NULL) {
            mx_compareto(&temp, &old, &check);
            temp = *new;
            old = old->nextPath;

            if (check == 0)
                return 0;
            if (old)
                check = 0;
            continue;
        }

        mx_compareto(&temp, &old, &check);
        old = old->next;
    }

    return check;
}

