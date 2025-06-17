#include "decoder.h"
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <frame_number> <output_file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    int frame_number = atoi(argv[2]);
    const char *output_file = argv[3];

    DecoderContext ctx = {0};
    int ret;

    // Инициализация декодера
    ret = decoder_init(&ctx, input_file);
    if (ret < 0) {
        char errbuf[AV_ERROR_MAX_STRING_SIZE];
        av_strerror(ret, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error initializing decoder: %s\n", errbuf);
        return 1;
    }

    // Получение кадра
    AVFrame *frame;
    ret = decoder_get_frame(&ctx, frame_number, &frame);
    if (ret < 0) {
        char errbuf[AV_ERROR_MAX_STRING_SIZE];
        av_strerror(ret, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error getting frame: %s\n", errbuf);
        decoder_free(&ctx);
        return 1;
    }

    // Сохранение в BMP
    ret = save_frame_as_bmp(frame, output_file);
    if (ret < 0) {
        fprintf(stderr, "Error saving frame to BMP\n");
        decoder_free(&ctx);
        return 1;
    }

    // Освобождение ресурсов
    decoder_free(&ctx);
    return 0;
} 