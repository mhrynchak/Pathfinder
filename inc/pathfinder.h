#pragma once
#include "libmx.h"

#define INF INT_MAX

typedef struct s_finder {
    int num;
    int **primary;
    int **cost;
    char **islands;
    t_list *route;
    t_list *distances;
}              t_finder;

typedef struct s_out {
    int length;
    int *route;
}              t_out;

//Tools pack
t_finder *parse_input(char *file);
void mx_build_paths(t_finder *path);
void shortest_route(t_finder *path, t_out *step);
void mx_print_path(t_finder *path, t_out *step);
void mx_clean(t_finder **path);

//Error pack
void valid_argc(int argc);
void invalid_num();
void valid_file(char *file);
void check_num(char *str, int line);
void valid_duplicates(int cost);
void valid_bridges_len(int sign, int sum);
void valid_line(int line, char *str, char *first_isle, char *second_isle);
