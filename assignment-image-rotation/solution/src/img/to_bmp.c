#include "../../include/files/file.h"
#include "../../include/img/bmp.h"

static struct bmp_header create_header(const struct image * const img) {
    const uint32_t width = img->width;
    const uint32_t height = img->height;
    const uint32_t i_size = (width * sizeof(struct pixel) + padding(width)) * height;
    const uint32_t f_size = i_size + sizeof(struct bmp_header);
    return bmp_header_construct(width, height, i_size, f_size);
}

static enum status write_header(FILE * file, const struct bmp_header* const header) {
    if (fseek(file, 0, SEEK_SET) != 0) return SEEK_ERR;
    if (fwrite(header, sizeof(struct bmp_header), 1, file) != 1) return WRITE_ERR;
    return OK;
}

static enum status write_image(FILE* const file, const struct image* const img) {
    if (fseek(file, sizeof(struct bmp_header), SEEK_SET) != 0) return SEEK_ERR;
    for (size_t i = 0; i < img->height; ++i) {
        if (fwrite(img->data + i * img->width, sizeof(struct pixel), img->width, file) != img->width) return WRITE_ERR;
        if (fseek(file, padding(img->width), SEEK_CUR) != 0) return SEEK_ERR;
    }
    return OK;
}

enum status bmp_close(const char * const name, struct image * const img) {
    FILE * file= NULL;
    enum status st;
    if ((st = open_file(&file, name, "wb")) != OK) return st;
    if ((st = to_bmp(file, img)) != OK) return st;
    return close_file(file);
}

enum status to_bmp(FILE * const file, const struct image* const img) {
    const struct bmp_header header = create_header(img);
    enum status st;
    if ((st = write_header(file, &header)) != OK) return st;
    return write_image(file, img);
}

