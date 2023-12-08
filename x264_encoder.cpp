#include "x264_encoder.h"

X264Encoder::X264Encoder(int width, int height)
    : encoder_(nullptr) {
    x264_param_t param;
    x264_param_default_preset(&param, "medium", "zerolatency");
    param.i_width = width;
    param.i_height = height;
    param.i_csp = X264_CSP_I420;
    param.i_bframe = 0;
    param.i_keyint_max = 99999;
    x264_param_apply_profile(&param, "high");

    encoder_ = x264_encoder_open(&param);
}

X264Encoder::~X264Encoder() {
    if (encoder_) {
        x264_encoder_close(encoder_);
        encoder_ = nullptr;
    }
}

int X264Encoder::encode_frame(x264_picture_t* pic, bool is_key_frame, uint8_t** output) {
    x264_nal_t* nals;
    int i_nals;
    int frame_size;

    pic->i_type = is_key_frame ? X264_TYPE_IDR : X264_TYPE_P;

    frame_size = x264_encoder_encode(encoder_, &nals, &i_nals, pic, &pic_out_);
    if (frame_size > 0) {
        *output = nals[0].p_payload;
    }
    return frame_size;
}