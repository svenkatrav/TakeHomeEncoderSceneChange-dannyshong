#pragma once

#include <fstream>
#include <cstdint>
extern "C" {
#include <x264.h>
}

class SceneChangeDetector {
public:
    bool detect_scene_change(x264_picture_t* current, x264_picture_t* previous);
    bool detect_scene_change_post_encoding(const unsigned char* encoded_data, int size);
};