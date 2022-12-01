#pragma once

#include "libmx.h"

typedef struct s_path t_path;
typedef struct s_island t_island;
typedef struct s_pathslist t_pathslist;
typedef struct s_names t_names;
typedef struct s_islandsinf t_islandsinf;

struct s_path {
    int index;
    int id;
    int d;
    struct s_path *next;
    struct s_path *nextPath;
};

struct s_island {
    int island_index;
    int island_d;
    struct s_path *path;
    struct s_island *next;
};

struct s_pathslist {
    t_island *first;
    t_island *second;
    t_island *third;
    t_island *fourth;
};

struct s_names {
    int num;
    char *name1;
    char *name2;
    char *name3;
};

struct s_islandsinf {
    int matrix;
    int island_1;
    int island_2;
};

void mx_valid_argc(int argc);
void mx_errors_check(char *filearr, char **argv);
void mx_parsing(char *filestr, char ***put, int ***matrix);

void mx_create_arr(char **line, char ***arr);
void mx_put(char ***put, char ***arr);
int **mx_create_matrix(char **put, char ***arr);

t_island *mx_distance_count(t_island **first);
int mx_unique(t_path **new, t_path **cur);
void mx_path_push_back(t_path **path, t_path **old, int isl, int d);
void mx_add_link(t_path **fastest, t_path **new);
t_path *mx_add_path(t_path **old, int isl, int d);
void mx_delete_matrix(int ***matrix, char **put);
void mx_delete_path(t_path **path);
void mx_isl_mid(t_island **unv, int index);
void mx_isl_front(t_island **isl);
t_path *mx_create_path(int isl, int d);
t_path *mx_paste_path(t_path **data);
void mx_new_path(t_island **island, t_path **path, int i, int dist);
void mx_sort_path(t_path **cur, int sizeP);
void mx_print_path(t_island **second, char **put, int root, int size);
void mx_path_finder(int **matrix, char **set);
