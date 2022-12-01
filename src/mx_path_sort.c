#include "header.h"

void mx_swap_p(t_path **cur, t_path **temp, t_path **fast) {
    t_path *cur_temp = *cur;
    t_path *temp_2 = (*fast)->nextPath;

    for (; cur_temp->nextPath != *fast; cur_temp = cur_temp->nextPath) {}

    mx_add_link(&cur_temp, &(*temp));
    cur_temp = *cur;
    
    if (*cur != *temp) {
        while (cur_temp && cur_temp->nextPath != *temp)
            cur_temp = cur_temp->nextPath;
        mx_add_link(&cur_temp, &(*fast));
    }
    else
        *cur = *fast;

    mx_add_link(&(*fast), &(*temp)->nextPath);
    mx_add_link(&(*temp), &temp_2);
}

void mx_swap(t_path **cur, t_path **temp, t_path **fast) {
    t_path *cur_temp = *cur;
    t_path *temp_2 = (*fast)->nextPath;

    if ((*temp)->nextPath != *fast) {
        mx_swap_p(&(*cur), &(*temp), &(*fast));
        return;
    }
    else {
        mx_add_link(&(*fast), &(*temp));
        mx_add_link(&(*temp), &temp_2);

        if (*cur != *temp) {
            while (cur_temp && cur_temp->nextPath != *temp)
                cur_temp = cur_temp->nextPath;
            mx_add_link(&cur_temp, &(*fast));
        }
        else
            *cur = *fast;
    }
}

int mx_compare(t_path *temp, t_path *fast) {
    for (; temp && fast; temp = temp->next, fast = fast->next){
        if (temp->id != fast->id)
            return temp->id > fast->id ? 1 : 0;
    }

    if (temp && !fast)
        return 1;

    return 0;
}

void mx_sort_path(t_path **cur, int sizeI) {
    t_path *fast = (*cur)->nextPath;
    t_path *temp = *cur;

    for (int i = 0; i < sizeI; i++) {
        temp = *cur;
        fast = temp->nextPath;

        while (temp->index != i) {
            fast = temp->nextPath;
            temp = temp->nextPath;
        }

        while (fast) {
            if (mx_compare(temp, fast) != 1)
                fast = fast->nextPath;
            else {
                mx_swap(&(*cur), &temp, &fast);
                for (temp = *cur; temp->index != i; temp = temp->nextPath)
                    fast = temp->nextPath;
            }
        }
    }
}
