#ifndef LAB3_FILE_READER_H
#define LAB3_FILE_READER_H
#include "../util/status.h"
#include <stdio.h>
enum status open_file(FILE ** const file, const char * const name, const char * const mode);
enum status close_file(FILE * const file);
#endif //LAB3_FILE_READER_H
