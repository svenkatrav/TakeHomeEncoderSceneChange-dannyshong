#include "yuv_reader.h"
#include "x264_encoder.h"
#include "scene_change_detector.h"
#include <fstream>
#include <iostream>

int main() {
    const int width = 1280;
    const int height = 720;
    std::ofstream file_("test/big_buck_bunny_720p30.264", std::ios::binary);
    SceneChangeDetector sceneChangeDetector;

    YuvReader reader("test/big_buck_bunny_720p30.yuv", width, height);
    X264Encoder encoder(width, height);

    x264_picture_t pic_in[2];
    x264_picture_alloc(&pic_in[0], X264_CSP_I420, width, height);
    x264_picture_alloc(&pic_in[1], X264_CSP_I420, width, height);

    int current_index = 0;
    bool is_key_frame = true; // Start with a key frame for the first frame
    int frame_count = 0;
    while (reader.has_next_frame()) {

        x264_picture_t* current_pic = &pic_in[current_index];
        x264_picture_t* previous_pic = &pic_in[current_index ^ 1]; // XOR to switch between 0 and 1

        reader.get_next_frame(current_pic);

        // Pre-encoding scene change detection (based on raw pixel data)
        if (!is_key_frame) { // Skip detection on the first frame
            is_key_frame = sceneChangeDetector.detect_scene_change(current_pic, previous_pic);
        }

        uint8_t* output_frame = nullptr;
        int frame_size = encoder.encode_frame(current_pic, is_key_frame, &output_frame);

        // Post-encoding scene change detection (based on encoded data)
        if (frame_size > 0) {
            bool scene_change_post_encode = sceneChangeDetector.detect_scene_change_post_encoding(output_frame, frame_size);

            bool needs_reencode = !is_key_frame && scene_change_post_encode;
            if (!needs_reencode) {
                // If already encoded as key frame or post-encoding indicates it is nnot a keyframe, write to file
                file_.write(reinterpret_cast<const char*>(output_frame), frame_size);
                std::cout <<frame_count++ << ": Encoded frame size: " << frame_size << std::endl;
            } else {
             // Scene change detected after encoding as P-frame, re-encode as IDR
                frame_size = encoder.encode_frame(current_pic, true, &output_frame);
                std::cout <<frame_count++ << ": Re-encoded frame size: " << frame_size << std::endl;
                file_.write(reinterpret_cast<const char*>(output_frame), frame_size);
            }
        }

        // Switch to the other picture for the next frame
        current_index ^= 1; // XOR to switch between 0 and 1
        is_key_frame = false; // Reset key frame flag for the next iteration
    }

    x264_picture_clean(&pic_in[0]);
    x264_picture_clean(&pic_in[1]);
    file_.close();

    return 0;
}