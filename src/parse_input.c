#include "pathfinder.h"

bool mx_valid_num(int total, int curr_num) {
    return total >= curr_num;
}

int get_num(char *file) {
    char *str = NULL;
    int num = 0, fd = 0;

    fd = open(file, O_RDONLY);
    valid_file(file);

    mx_read_line(&str, 10, '\n', fd);
    check_num(str, 1);
    
    num = mx_atoi(str);

    mx_strdel(&str);
    close(fd);
    return num;
}

int found_at(char *island, char **arr) {
    for (int i = 0; arr[i] != NULL; i++) {
        if (mx_strcmp(island, arr[i]) == 0)
            return i;
    }
    return -1;
}

void add_island(char ***arr, char *island, int *i) {
    mx_strdel(&((*arr)[*i]));
    (*arr)[*i] = mx_strdup(island);
    (*i)++;
}

t_finder *parse_input(char *file) {
    t_finder *path = (t_finder *)malloc(sizeof(t_finder));
    char *str = mx_file_to_str(file), *first_isle = NULL, *second_isle = NULL;
    int index = 0, len = 0, sum = 0, sign = 1, x = 0, y = 0, fd = open(file, O_RDONLY);
    int count = mx_count_words(str, '\n');      //counting lines in the file
    mx_strdel(&str);

    //getting the number of islands
    path->num = get_num(file);

    //initialising matrices
    path->islands = (char **) malloc (sizeof(char *) * (path->num + 1));
    path->islands[path->num] = NULL;
    path->cost = malloc(sizeof(int*) * path->num);
    path->primary = malloc(sizeof(int*) * path->num);

    for (int i = 0; i < path->num; i++) {
        path->cost[i] = malloc(sizeof(int) * path->num);
        path->primary[i] = malloc(sizeof(int) * path->num);
        path->islands[i] = mx_strnew(10);
        for (int j = 0; j < path->num; j++) {
            path->cost[i][j] = i == j ? 0 : INF;
        }
    }

    //Get islands
    for (int i = 0; i < count - 1; i++) {
        mx_read_line(&str, 9, '\n', fd);

        mx_read_line(&first_isle, 15, '-', fd);        //reading island in the first column
        if (mx_valid_num(path->num, index) && found_at(first_isle, path->islands) == -1) {           //checking for duplicate in the array
            add_island(&(path->islands), first_isle, &index);
        }

        mx_read_line(&second_isle, 15, ',', fd);        //reading island in the second column 
        if (mx_valid_num(path->num, index) && found_at(second_isle, path->islands) == -1) {      //checking for duplicate in the array
            add_island(&(path->islands), second_isle, &index);
        }

        valid_line(i + 2, str, first_isle, second_isle);

        mx_strdel(&str);
        mx_strdel(&first_isle);
        mx_strdel(&second_isle);
    }
    close(fd);

    if (index != path->num) {
        invalid_num();
    }

    //Get distances and parse them into graph matrix
    fd = open(file, O_RDONLY);
    mx_read_line(&str, 10, '\n', fd);
    mx_strdel(&str);

    for (int i = 0; i < count - 1; i++) {
        mx_read_line(&str, 15, '-', fd);
        x = found_at(str, path->islands);
        mx_strdel(&str);

        mx_read_line(&str, 15, ',', fd);
        y = found_at(str, path->islands);
        mx_strdel(&str);

        mx_read_line(&str, 9, '\n', fd);
        len = mx_atoi(str);
        mx_strdel(&str);

        valid_duplicates(path->cost[x][y]);

        path->cost[x][y] = len;
        path->cost[y][x] = len;

        sign *= (len/len);
        sum += len;
    }

    valid_bridges_len(sign, sum);
    close(fd);

    //saving primary state
    for (int i = 0; i < path->num; i++){
        for (int j = i; j < path->num; j++) {
            path->primary[i][j] = path->cost[i][j];
            path->primary[j][i] = path->cost[j][i];
        }
    }

    //Floyd Warshall algorithm
    for (int k = 0; k < path->num; k++) {
        for (int i = 0; i < path->num; i++) {
            for (int j = 0; j < path->num; j++) {
                if (path->cost[i][k] == INF || path->cost[k][j] == INF)
                    continue;
                if (path->cost[i][j] > path->cost[i][k] + path->cost[k][j]) {
                    path->cost[i][j] = path->cost[i][k] + path->cost[k][j];
                }
            }
        }
    }

    return path;
}
