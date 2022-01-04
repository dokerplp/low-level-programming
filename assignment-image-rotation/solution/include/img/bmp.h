#ifndef LAB3_BMP_H
#define LAB3_BMP_H
#include "../img/img.h"
#include "../util/status.h"
#include <inttypes.h>
#include <stdio.h>

#pragma pack(push, 1)
struct bmp_header
{
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    uint32_t ppmx;
    uint32_t ppmy;
    uint32_t clr_used;
    uint32_t clr_imoprtant;
};
#pragma pack(pop)

struct bmp_header bmp_header_construct(uint32_t const width, uint32_t const height, uint32_t const image_size, uint32_t const file_size);

enum status from_bmp(FILE* const f, struct image* const img);
enum status to_bmp(FILE* const f, const struct image* const img);

enum status bmp_open(const char* const name, struct image * const img);
enum status bmp_close(const char * const name, struct image * const img);

uint8_t padding(const uint32_t width);


#endif //LAB3_BMP_H
