#include "../../include/transformation/rotate.h"

enum status rotate(struct image* const img) {
    const uint32_t width = img->width;
    const uint32_t height = img->height;

    struct image _img = image_construct(height, width);

    if (!_img.data) return ALLOCATION_ERR;

    for (size_t i = 0; i < height; ++i) {
        for(size_t j = 0; j < width; ++j) {
            const struct pixel pixel = get_pixel(img, i, j);
            set_pixel(&_img, j, height - i - 1, pixel);
        }
    }

    image_free(*img);
    *img = _img;

    return OK;

}
