cmake_minimum_required(VERSION 3.10)
project(h264_decoder)

# Поиск FFmpeg
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED
    libavcodec
    libavformat
    libavutil
    libswscale
)

# Добавление исходных файлов
set(SOURCES
    src/main.c
    src/decoder.c
    src/bmp.c
)

# Создание исполняемого файла
add_executable(h264_decoder ${SOURCES})

# Подключение заголовочных файлов
target_include_directories(h264_decoder PRIVATE
    ${FFMPEG_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

# Линковка с библиотеками FFmpeg
target_link_libraries(h264_decoder
    ${FFMPEG_LIBRARIES}
) 