#include "yuv_reader.h"

YuvReader::YuvReader(const char* filename, int width, int height)
    : file_(filename, std::ios::binary),
      width_(width),
      height_(height) {}

YuvReader::~YuvReader() {
    if (file_.is_open()) {
        file_.close();
    }
}

bool YuvReader::has_next_frame() const {
    return !file_.eof();
}

void YuvReader::get_next_frame(x264_picture_t* pic) {
    file_.read(reinterpret_cast<char*>(pic->img.plane[0]), width_ * height_);
    file_.read(reinterpret_cast<char*>(pic->img.plane[1]), width_ * height_ / 4);
    file_.read(reinterpret_cast<char*>(pic->img.plane[2]), width_ * height_ / 4);
}