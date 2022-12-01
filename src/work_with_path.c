#include "header.h"

t_path *mx_create_path(int isl, int d) {
	t_path *new = (t_path *)malloc(1 * sizeof(t_path));

    new->nextPath = NULL;
    new->next = NULL;
    new->id = isl;
    new->d = d;
    
	return new;
}

t_path *mx_add(t_path **old) {
    t_path *last = *old;
    t_path *res = mx_create_path(last->id, last->d);
    t_path *new = res;
    last = last->next;

    for (; last; last = last->next, new = new->next)
        new->next = mx_create_path(last->id, last->d);

    return res;
}

t_path *mx_add_single_path(t_path **old, int isl, int d) {
    t_path *res = NULL;
    t_path *last = *old;
    
    if (!last) return res = mx_create_path(isl, d);
    res = mx_create_path(last->id, last->d);
    t_path *new = res;
    last = last->next;

    for (; last; last = last->next, new = new->next)
        new->next = mx_create_path(last->id, last->d);

    new->next = mx_create_path(isl, d);

    return res;
}

void mx_add_link(t_path **fastest, t_path **new) {
    t_path *current = *fastest;

    for (; current->next; current->nextPath = *new, current = current->next) {}

    current->nextPath = *new;
}

void mx_path_push_back(t_path **path, t_path **old, int isl, int d) {
    t_path *new = NULL;
    t_path *last = *path;
    t_path *cur = *old;
    
    for (; last->nextPath; last = last ->nextPath) {}

    for (; cur; cur = cur->nextPath) {
        new = mx_add_single_path(&cur, isl, d);

        if (mx_unique(&new, &(*path)) > 0) {
            mx_add_link(&last, &new);
            last = last->nextPath;
        }
    }
}

t_path *mx_add_path(t_path **old, int isl, int d) {
    t_path *cur = NULL;
    if (*old)
        cur = *old;
    t_path *res = mx_add_single_path(&cur, isl, d);
    t_path *new = NULL;
    t_path *fastest = res;

    if (cur)
        cur = cur->nextPath;

    for (; cur; cur = cur->nextPath, fastest = fastest->nextPath) {
        new = mx_add_single_path(&cur, isl, d);
        mx_add_link(&fastest, &new);
    }

    return res;
}

t_path *mx_paste_path(t_path **info) {
    t_path *cur = NULL;
    t_path *new = NULL;
    if (*info) cur = *info;
    t_path *res = mx_add(&cur);
    t_path *fastest = res;
    cur = cur->nextPath;

    for (; cur; cur = cur->nextPath, fastest = fastest->nextPath) {
        new = mx_add(&cur);
        mx_add_link(&fastest, &new);
    }

    return res;
}

