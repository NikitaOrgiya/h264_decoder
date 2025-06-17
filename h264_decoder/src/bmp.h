#ifndef BMP_H
#define BMP_H

#include <libavutil/frame.h>

// Сохранение кадра в BMP
int save_frame_as_bmp(AVFrame *frame, const char *filename);

#endif 