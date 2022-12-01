#include "header.h"

void mx_step_one(t_island **first, t_island **second, t_island **curr, int root, int size) {
    *first = NULL;
    *second = NULL;

    for (int i = 0; i < size; i++)
        mx_new_path(&(*first), NULL, i, 0);

    *curr = *first;
    while ((*curr)->island_index != root)
        *curr = (*curr)->next;

    (*curr)->path = mx_create_path(root, 0);
    mx_new_path(&(*second), &(*curr)->path, (*curr)->island_index, (*curr)->island_d);
    mx_isl_mid(&(*first), root);
    *curr = *second;
}

void mx_step_two(t_island **first, t_island **cur, t_islandsinf **isl, int **matrix) {
    int dist_sum = 0;
    t_island *temp = *first;

    while (temp != NULL) {
        (*isl)->island_2 = temp->island_index;
        (*isl)->island_1 = (*cur)->island_index;
        (*isl)->matrix = matrix[(*isl)->island_1][(*isl)->island_2];

        if (temp->island_d == 0 && (*isl)->matrix != 0) {
            temp->island_d = (*isl)->matrix + (*cur)->island_d;
            dist_sum += temp->island_d;

            if (dist_sum < 0) { 
                mx_printerr("error: sum of bridges lengths is too big\n");
                exit(1);
            } 

            temp->path = mx_add_path(&(*cur)->path, (*isl)->island_2, (*isl)->matrix);
        }
        else if ((*isl)->matrix != 0) {
            if ((*cur)->island_d + (*isl)->matrix == temp->island_d)
                mx_path_push_back(&temp->path, &(*cur)->path, (*isl)->island_2, (*isl)->matrix);

            if ((*cur)->island_d + (*isl)->matrix < temp->island_d) {
                mx_delete_path(&temp->path);
                temp->island_d = (*cur)->island_d + (*isl)->matrix;
                temp->path = mx_add_path(&(*cur)->path, (*isl)->island_2, (*isl)->matrix);
            }
        }
        
        temp = temp->next;
    }
}

void mx_step_three(t_pathslist **list, int **matrix, char **put) {
    (*list)->fourth = mx_distance_count(&(*list)->first);

    mx_new_path(&(*list)->second, &(*list)->fourth->path, (*list)->fourth->island_index, (*list)->fourth->island_d);
    mx_isl_mid(&(*list)->first, (*list)->fourth->island_index);
    (*list)->third = (*list)->third->next;

    if ((*list)->third->path == NULL) {
        mx_printerr("error: invalid number of islands\n");
        mx_delete_matrix(&matrix, put);
        exit(1);
    }
}

void mx_finder(int **matrix, char **put, int root, int size) {
    t_pathslist *list = malloc(1 * sizeof(t_pathslist)); // 1 *
    t_islandsinf *isl = NULL;
    list->first = NULL;
    list->second = NULL;
    list->third = NULL;
    list->fourth = NULL;

    mx_step_one(&list->first, &list->second, &list->third, root, size);

    while (list->first && list->first != NULL) {
        isl = malloc(1 * sizeof(t_islandsinf)); // 1 * 
        mx_step_two(&list->first, &list->third, &isl, matrix);
        free(isl);
        isl = NULL;

        mx_step_three(&list, matrix, put);
    }

    mx_print_path(&list->second, put, root + 1, size);

    while (list->second != NULL) {
        mx_delete_path(&list->second->path);
        mx_isl_front(&list->second);
    }

    free(list);
    list = NULL;
}

void mx_path_finder(int **matrix, char **put) {
    int size = 0;
    int root = 0;

    while (put[size]) 
        size++;

    while (root < size - 1) {
        mx_finder(matrix, put, root, size);
        root++;
    }
}

