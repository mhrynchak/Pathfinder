#include "pathfinder.h"

void mx_clean(t_finder **path) {
    mx_del_strarr(&((*path)->islands));
    mx_del_intarr((*path)->cost, (*path)->num);
    mx_del_intarr((*path)->primary, (*path)->num);
    free(*path);
}
