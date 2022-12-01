#include "header.h"

static void mx_print_base(t_names **prd) {
    char *flat = mx_strdup("========================================\n");

    mx_printstr(flat);
    mx_printstr((*prd)->name1);
    mx_printstr((*prd)->name2);
    mx_printstr((*prd)->name3);
    mx_printstr(flat);

    mx_strdel(&flat);
    mx_strdel(&(*prd)->name3);
    mx_strdel(&(*prd)->name2);
    mx_strdel(&(*prd)->name1);
    free(*prd);
    *prd = NULL;
}

void mx_join(char **res, char *s2) {
    int i = 0;
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    char *s1 = *res;

    for (int sl = -1; s1[++sl]; i++) 
        newstr[i] = s1[sl];

    for (int sl = -1; s2[++sl]; i++)
        newstr[i] = s2[sl];

    mx_strdel(&(*res));
    *res = newstr;
}

t_names *mx_print_head(t_path *temp, char **put) {
    t_names *head = malloc(1 * sizeof(t_names));
    int i = 0;

    head->name1 = mx_strdup("Path: ");
    head->name2 = mx_strdup("Route: ");
    head->name3 = mx_strdup("Distance: ");

    mx_join(&(*head).name1, put[temp->id]);
    mx_join(&(*head).name2, put[temp->id]);

    while (temp != NULL) {
        temp = temp->next;
        i++;
    }

    head->num = i;

    return head;
}

void mx_add_next_bond(t_path *temp, t_names **prd, char *dTo, char **put) {
    char *d = NULL;
    
    mx_join(&(*prd)->name2, " -> ");
    mx_join(&(*prd)->name2, put[temp->id]);
    
    if (mx_strlen((*prd)->name3) != 10)
        mx_join(&(*prd)->name3, " + ");
    d = mx_itoa(temp->d);
    mx_join(&(*prd)->name3, d);

    if (temp->next == NULL) {
        mx_join(&(*prd)->name2, "\n");

        mx_join(&(*prd)->name1, " -> ");
        mx_join(&(*prd)->name1, put[temp->id]);
        mx_join(&(*prd)->name1, "\n");

        if ((*prd)->num != 2) {
            mx_join(&(*prd)->name3, " = ");
            mx_join(&(*prd)->name3, dTo);
        }

        mx_join(&(*prd)->name3, "\n");
    }

    mx_strdel(&d);
}

void mx_display_path(t_path **disp, char **put, int d) {
    t_names *isl_n = NULL;
    t_path *temp = *disp;
    char *dist = mx_itoa(d);

    for (; temp; temp = temp->nextPath) {
        isl_n = mx_print_head(temp, put);
        temp = temp->next;
        for (; temp->next; temp = temp->next)
            mx_add_next_bond(temp, &isl_n, dist, put);

        mx_add_next_bond(temp, &isl_n, dist, put);
        mx_print_base(&isl_n);
    }

    mx_strdel(&dist);
}

void mx_print_path(t_island **second, char **put, int root, int size) {
    t_island *cur = NULL;

    for (int i = 0; root < size; root++, i = 0) {
        t_path *temp = NULL;
        cur = *second;

        while (cur->island_index != root)
            cur = cur->next;
        
        t_path *indexed = cur->path;

        for (; indexed; indexed = indexed->nextPath, i++) {
            temp = indexed;
            while (temp) {
                temp->index = i;
                temp = temp->next;
            }
        }

        mx_sort_path(&cur->path, i);
        mx_display_path(&cur->path, put, cur->island_d);
    }
}
