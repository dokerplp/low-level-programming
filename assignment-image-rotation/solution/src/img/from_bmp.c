#include "../../include/files/file.h"
#include "../../include/img/bmp.h"

static enum status read_header(FILE * const file, struct bmp_header * const header) {
    if (fread(header, sizeof(struct bmp_header), 1, file) != 1) return READ_ERR;
    return OK;
}

static enum status read_pixels(FILE * const file, struct image * const img) {
    const uint32_t width = img->width;
    const uint32_t height = img->height;
    for (size_t i = 0; i < height; i++) {
        if (fread(img->data + i * width, sizeof(struct pixel), width, file) != width)return READ_ERR;
        if (fseek(file, padding(width), SEEK_CUR) != 0) return SEEK_ERR;
    }
    return OK;
}

static enum status read_image(FILE * const file, const struct bmp_header * const header, struct image * const img) {
    *img = image_construct(header->width, header->height);
    if (!img->data) return ALLOCATION_ERR;
    if (fseek(file, header->offset, SEEK_SET) != 0) return SEEK_ERR;
    return read_pixels(file, img);
}

enum status bmp_open(const char* const name, struct image * const img) {
    FILE * file = NULL;
    enum status st;
    if ((st = open_file(&file, name, "rb")) != OK) return st;
    if ((st = from_bmp(file, img)) != OK) return st;
    return close_file(file);
}

enum status from_bmp(FILE * const file, struct image * const img) {
    struct bmp_header header = {0};
    enum status st;
    if ((st = read_header(file, &header)) != OK) return st;
    return read_image(file, &header, img);
}
