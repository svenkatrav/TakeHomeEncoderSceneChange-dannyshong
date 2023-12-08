#pragma once

#include <fstream>
#include <cstdint>
extern "C" {
#include <x264.h>
}

class YuvReader {
public:
    YuvReader(const char* filename, int width, int height);
    ~YuvReader();
    bool has_next_frame() const;
    void get_next_frame(x264_picture_t* pic);

private:
    std::ifstream file_;
    int width_;
    int height_;
};