# H.264 Decoder

Программа для извлечения кадров из видеофайлов формата H.264 и сохранения их в формате BMP.

## Требования

- CMake 3.10 или выше
- FFmpeg с поддержкой H.264
- pkg-config
- Компилятор C (gcc/clang)

## Сборка

```bash
mkdir build
cd build
cmake ..
make
```

## Использование

```bash
./h264_decoder <input_file> <frame_number> <output_file>
```

Где:
- input_file - путь к входному H.264 файлу
- frame_number - номер кадра для извлечения (начиная с 0)
- output_file - путь к выходному BMP файлу

## Пример

```bash
./h264_decoder video.mp4 10 frame.bmp
```

Это извлечет 10-й кадр из video.mp4 и сохранит его как frame.bmp. 