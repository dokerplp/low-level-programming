#include "../../include/files/file.h"

enum status open_file(FILE** file, const char* const name, const char* const mode) {
    *file = fopen(name, mode);
    if (!*file) return FILE_OPEN_ERR;
    return OK;
}

enum status close_file(FILE* file) {
    const int res = fclose(file);
    if (res != 0) return FILE_CLOSE_ERR;
    return OK;
}

