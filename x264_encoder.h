#pragma once

#include <fstream>
#include <cstdint>
extern "C" {
#include <x264.h>
}

class X264Encoder {
public:
    X264Encoder(int width, int height);
    ~X264Encoder();
    int encode_frame(x264_picture_t *pic, bool is_key_frame, uint8_t** output);

private:
    x264_t* encoder_;
    x264_picture_t pic_out_;
};