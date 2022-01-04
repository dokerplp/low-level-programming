#include "../../include/img/bmp.h"

static const struct bmp_header template = {
        .signature = 0x4D42,
        .reserved = 0,
        .offset = sizeof(struct bmp_header),
        .header_size = 40,
        .planes = 1,
        .bit_count = 24,
        .compression = 0,
        .ppmx = 2834,
        .ppmy = 2834,
        .clr_used = 0,
        .clr_imoprtant = 0
};

struct bmp_header bmp_header_construct(uint32_t const width, uint32_t const height, uint32_t const image_size, uint32_t const file_size) {
    struct bmp_header templ = template;
    templ.width = width;
    templ.height = height;
    templ.image_size = image_size;
    templ.file_size = file_size;
    return templ;
}

uint8_t padding(const uint32_t width) {
    const uint8_t padding = (width * sizeof(struct pixel)) % 4;
    return padding ? 4 - padding : 0;
}


