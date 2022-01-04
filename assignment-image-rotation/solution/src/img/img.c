#include "../../include/img/img.h"

struct image image_construct(const uint32_t width, const uint32_t height) {
    return (struct image) {
            .width = width,
            .height = height,
            .data = malloc(width * height * sizeof(struct pixel))
    };
}

void image_free(struct image img) {
    free(img.data);
}

struct pixel get_pixel(const struct image* const img, const size_t row, const size_t col) {
    return img->data[row * img->width + col];
}

void set_pixel(struct image* const img, const size_t row, const size_t col, const struct pixel pixel) {
    img->data[row * img->width + col] = pixel;
}
