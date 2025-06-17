#ifndef DECODER_H
#define DECODER_H

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>

// Структура для хранения контекста декодера
typedef struct DecoderContext {
    AVFormatContext *format_ctx;
    AVCodecContext *codec_ctx;
    AVFrame *frame;
    AVPacket *packet;
    int video_stream_idx;
} DecoderContext;

// Инициализация декодера
int decoder_init(DecoderContext *ctx, const char *filename);

// Декодирование кадра по номеру
int decoder_get_frame(DecoderContext *ctx, int frame_number, AVFrame **frame);

// Освобождение ресурсов
void decoder_free(DecoderContext *ctx);

#endif 