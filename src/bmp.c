#include "bmp.h"
#include <stdio.h>
#include <stdint.h>

// Структура заголовка BMP
#pragma pack(push, 1)
typedef struct {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} BMPHeader;
#pragma pack(pop)

int save_frame_as_bmp(AVFrame *frame, const char *filename) {
    FILE *f;
    BMPHeader header;
    int i, ret;

    f = fopen(filename, "wb");
    if (!f) {
        return -1;
    }

    // Заполняем заголовок BMP
    header.signature = 0x4D42; // 'BM'
    header.file_size = sizeof(BMPHeader) + frame->width * frame->height * 3;
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.data_offset = sizeof(BMPHeader);
    header.header_size = 40;
    header.width = frame->width;
    header.height = frame->height;
    header.planes = 1;
    header.bits_per_pixel = 24;
    header.compression = 0;
    header.image_size = frame->width * frame->height * 3;
    header.x_pixels_per_meter = 0;
    header.y_pixels_per_meter = 0;
    header.colors_used = 0;
    header.colors_important = 0;

    // Записываем заголовок
    fwrite(&header, sizeof(header), 1, f);

    // Записываем данные изображения
    for (i = frame->height - 1; i >= 0; i--) {
        fwrite(frame->data[0] + i * frame->linesize[0], 1, frame->width * 3, f);
    }

    fclose(f);
    return 0;
} 