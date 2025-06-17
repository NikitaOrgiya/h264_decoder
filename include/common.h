#ifndef COMMON_H
#define COMMON_H

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
#include <libavutil/error.h>

// Максимальная длина сообщения об ошибке
#define ERROR_BUFFER_SIZE 1024

// Коды ошибок
#define ERROR_SUCCESS 0
#define ERROR_INVALID_ARGUMENTS -1
#define ERROR_FILE_NOT_FOUND -2
#define ERROR_DECODER_INIT -3
#define ERROR_FRAME_DECODE -4
#define ERROR_BMP_SAVE -5

// Функция для получения текстового описания ошибки
const char* get_error_message(int error_code);

#endif // COMMON_H 