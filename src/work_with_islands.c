#include "header.h"

t_island *mx_distance_count(t_island **first) {
    if (!first || !*first)
        return NULL;

    t_island *shortest = *first;
    t_island *temp = *first;

    for (; temp; temp = temp->next) {
        if (temp->island_d != 0 && (shortest->island_d > temp->island_d || !shortest->island_d))
            shortest = temp;
    }
    
    return shortest;
}

void mx_isl_front(t_island **isl) {
    t_island *temp = NULL;
    
    if (isl && (*isl)) {
        if ((*isl)->next != NULL) {
            temp = (*isl)->next;
            free(*isl);
            *isl = temp;
        }
        else {
            free(*isl);
            *isl = NULL;
            return;
        }
    }
    else
        return;
}

void mx_isl_mid(t_island **unv, int index) {
    if (!unv || !(*unv)) 
        return;

    if ((*unv)->island_index != index) {
        t_island *temp = *unv;
        t_island *left = temp;

        for (; temp && temp->island_index != index; left = temp, temp = temp->next) {}
        if (temp && temp->island_index == index) {
            if (!temp->next)
                left->next = NULL;
            else
                left->next = temp->next;

            mx_delete_path(&temp->path);
            free(temp);
            temp = NULL;
        }
    }
    else {
        mx_delete_path(&((*unv)->path));
        mx_isl_front(&(*unv));
    }
}

void mx_new_path(t_island **island, t_path **path, int i, int d) {
    t_island *new = (t_island *)malloc(1 * sizeof(t_island));
    t_island *last = *island;
    new->island_index = i;
    new->island_d = d;
    new->path = NULL;
    new->next = NULL;

    if (path && *path)
        new->path = mx_paste_path(&(*path));

    if (*island == NULL) {
        *island = new;
        return;
    }

    for (; last->next != NULL; last = last->next) {}

    last->next = new;
    return;
}

