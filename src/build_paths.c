#include "pathfinder.h"

void mx_build_paths(t_finder *path) {
    t_out *step = (t_out*) malloc (sizeof(t_out));
    step->route = (int *) malloc(sizeof(int) * (path->num + 1));

    for (int i = 0; i < path->num; i++) {
        for (int j = i + 1; j < path->num; j++) {
            step->length = 1;
            step->route[0] = j;
            step->route[1] = i;
            shortest_route(path, step);
        }
    }
    free(step->route);
    free(step);
}

void shortest_route(t_finder *path, t_out *step) {
    int i = step->route[step->length];
    int j = step->route[0];

    for (int k = 0; k < path->num; k++) {
        if (step->route[step->length] == step->route[0] && k > 0) break;
        else if (k != step->route[step->length] && 
        (path->primary[i][k] == path->cost[i][j] - path->cost[k][j])) {
            step->length++;
            step->route[step->length] = k;
            shortest_route(path, step);
            step->length--;
        }
    }

    if (step->route[step->length] != step->route[0]) return;

    mx_print_path(path, step);
}

void mx_print_path(t_finder *path, t_out *step) {
    int sum = 0, tmp = 0;
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(path->islands[step->route[1]]);
    mx_printstr(" -> ");
    mx_printstr(path->islands[step->route[0]]);
    mx_printstr("\nRoute: ");

    for (int i = 1; i < step->length + 1;) {
        mx_printstr(path->islands[step->route[i]]);
        if (++i < step->length +1)
            mx_printstr(" -> ");
    }

    mx_printstr("\nDistance: ");
    for (int i = 1; i < step->length; i++) {
        tmp = path->primary[step->route[i]][step->route[i+1]];
        mx_printint(tmp);
        sum += tmp;
        
        if (i < step->length - 1)
            mx_printstr(" + ");
        else if (i > 1) {
            mx_printstr(" = ");
            mx_printint(sum);
        }
    }
    mx_printstr("\n========================================\n");
}
