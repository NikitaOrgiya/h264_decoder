#include "decoder.h"
#include <libavutil/error.h>

int decoder_init(DecoderContext *ctx, const char *filename) {
    int ret;
    
    // Открываем входной файл
    ret = avformat_open_input(&ctx->format_ctx, filename, NULL, NULL);
    if (ret < 0) {
        return ret;
    }

    // Получаем информацию о потоках
    ret = avformat_find_stream_info(ctx->format_ctx, NULL);
    if (ret < 0) {
        return ret;
    }

    // Находим видеопоток
    ret = av_find_best_stream(ctx->format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (ret < 0) {
        return ret;
    }
    ctx->video_stream_idx = ret;

    // Находим декодер
    const AVCodec *codec = avcodec_find_decoder(
        ctx->format_ctx->streams[ctx->video_stream_idx]->codecpar->codec_id);
    if (!codec) {
        return AVERROR_DECODER_NOT_FOUND;
    }

    // Создаем контекст декодера
    ctx->codec_ctx = avcodec_alloc_context3(codec);
    if (!ctx->codec_ctx) {
        return AVERROR(ENOMEM);
    }

    // Копируем параметры
    ret = avcodec_parameters_to_context(ctx->codec_ctx, 
        ctx->format_ctx->streams[ctx->video_stream_idx]->codecpar);
    if (ret < 0) {
        return ret;
    }

    // Открываем декодер
    ret = avcodec_open2(ctx->codec_ctx, codec, NULL);
    if (ret < 0) {
        return ret;
    }

    // Выделяем память для кадра и пакета
    ctx->frame = av_frame_alloc();
    ctx->packet = av_packet_alloc();
    if (!ctx->frame || !ctx->packet) {
        return AVERROR(ENOMEM);
    }

    return 0;
}

int decoder_get_frame(DecoderContext *ctx, int frame_number, AVFrame **frame) {
    int ret;
    int current_frame = 0;

    while (current_frame <= frame_number) {
        ret = av_read_frame(ctx->format_ctx, ctx->packet);
        if (ret < 0) {
            return ret;
        }

        if (ctx->packet->stream_index == ctx->video_stream_idx) {
            ret = avcodec_send_packet(ctx->codec_ctx, ctx->packet);
            if (ret < 0) {
                return ret;
            }

            while (ret >= 0) {
                ret = avcodec_receive_frame(ctx->codec_ctx, ctx->frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    return ret;
                }

                if (current_frame == frame_number) {
                    *frame = ctx->frame;
                    return 0;
                }
                current_frame++;
            }
        }
        av_packet_unref(ctx->packet);
    }

    return AVERROR(ENOENT);
}

void decoder_free(DecoderContext *ctx) {
    if (ctx->codec_ctx) {
        avcodec_free_context(&ctx->codec_ctx);
    }
    if (ctx->format_ctx) {
        avformat_close_input(&ctx->format_ctx);
    }
    if (ctx->frame) {
        av_frame_free(&ctx->frame);
    }
    if (ctx->packet) {
        av_packet_free(&ctx->packet);
    }
} 