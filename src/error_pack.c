#include "pathfinder.h"

void valid_file(char *file) {
    char *str = NULL, fd = open(file, O_RDONLY);

    if (fd == -1) {
        mx_printerr("error: file ");
        mx_printerr(file);
        mx_printerr(" does not exist\n");
        close(fd);
        exit(errno);
    }

    else if (mx_read_line(&str, 1,'\n', fd) == -1) {
        mx_strdel(&str);
        mx_printerr("error: file ");
        mx_printerr(file);
        mx_printerr(" is empty\n");
        close(fd);
        exit(errno);
    }
}

void valid_argc(int argc) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(errno);
    }
}

void invalid_num() {
    mx_printerr("error: invalid number of islands\n");
    exit(errno);
}

void check_num(char *str, int line) {
    for (int i = 0; str[i]; i++) {
        if (!mx_isdigit(str[i])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(line));
            mx_printerr(" is not valid\n");
            exit(errno);
        }
    }
}

void valid_line(int line, char *num, char *first_isle, char *second_isle) {
    bool invalid = false;

    check_num(num, line);

    for (int i = 0; first_isle[i]; i++) {
        if (!mx_isalpha(first_isle[i])) {
            invalid = true;
            break;
        }
    }

    for (int i = 0; second_isle[i]; i++) {
        if (!mx_isalpha(second_isle[i])) {
            invalid = true;
            break;
        }
    }

    if (invalid || mx_strcmp(first_isle, second_isle) == 0) {
        mx_printerr("error: line ");
        mx_printerr(mx_itoa(line));
        mx_printerr(" is not valid\n");
        exit(errno);
    }
}

void valid_duplicates(int cost) {
    if (cost != INF) {
        mx_printerr("error: duplicate bridges\n");
        exit(errno);
    }
}

void valid_bridges_len(int sign, int sum) {
    if (sign > 0 && sum < 0) {
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(errno);
    }
}
