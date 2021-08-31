#include "pathfinder.h"

int main(int argc, char **argv) {
    t_finder *path = NULL;
    
    valid_argc(argc);
    path = parse_input(argv[1]);
    mx_build_paths(path);
    mx_clean(&path);
    return 0;
}
