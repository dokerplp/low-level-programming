#ifndef LAB3_IMG_H
#define LAB3_IMG_H
#include "../util/status.h"
#include <inttypes.h>
#include <mm_malloc.h>

#pragma pack(push, 1)
struct pixel { uint8_t b, g, r; };
#pragma pack(pop)

struct image {
    uint64_t width, height;
    struct pixel * data;
};

struct image image_construct(const uint32_t width, const uint32_t height);
void image_free(struct image img);

struct pixel get_pixel(const struct image* const img, const size_t row, const size_t col);

void set_pixel(struct image* const img, const size_t row, const size_t col, const struct pixel pixel);


#endif //LAB3_IMG_H
