#include "../include/files/file.h"
#include "../include/img/bmp.h"
#include "../include/transformation/rotate.h"
#include "../include/util/status.h"

void handle_err(enum status st);

int main( int argc, char** argv ) {
    enum status st;
    if (argc != 3) {
        handle_err(WRONG_ARGS);
        return WRONG_ARGS;
    }

    struct image img = {0};
    if ((st = bmp_open(argv[1], &img)) != OK) {
        handle_err(st);
        return st;
    }
    if ((st = rotate(&img)) != OK) {
        handle_err(st);
        return st;
    }
    if ((st = bmp_close(argv[2], &img)) != OK) {
        handle_err(st);
        return st;
    }

    image_free(img);

    return OK;
}

void handle_err(enum status st) {
    char * err;
    switch (st) {
        case WRONG_ARGS:
            err = "Wrong amount of arguments";
            break;
        case FILE_OPEN_ERR:
            err = "Can't open file";
            break;
        case FILE_CLOSE_ERR:
            err = "Error while closing file";
            break;
        case READ_ERR:
            err = "Can't read file";
            break;
        case WRITE_ERR:
            err = "Can't write in file";
            break;
        case SEEK_ERR:
            err = "Seek error";
            break;
        case ALLOCATION_ERR:
            err = "Allocation error";
            break;
        default:
            err = "Unknown error";
            break;
    }
    fprintf(stderr, "%s", err);
}


