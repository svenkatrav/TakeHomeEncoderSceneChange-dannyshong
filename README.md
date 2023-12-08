# Scene Change Detection Take-Home Exercise

## Overview

This take-home exercise is designed to assess your ability to implement scene change detection algorithms in video encoding workflows. You are provided with a simple video encoder simulation that processes YUV frames and encodes them using the x264 library. Your task is to implement the scene change detection logic that determines whether a frame should be encoded as a keyframe (I-frame) or not.

## Directory Structure

- `main.cpp`: The main application entry point that sets up the encoding loop.
- `yuv_reader.h/cpp`: Defines the `YuvReader` class responsible for reading raw YUV frames from a file.
- `x264_encoder.h/cpp`: Defines the `X264Encoder` class that wraps the x264 encoding functionality.
- `scene_change_detector.h/cpp`: Defines the `SceneChangeDetector` class where you will implement the scene change detection algorithms.
- `Makefile`: Used to build the application using the `make` command.
- `README.md`: This file, which provides an overview and instructions.

## Building the Application

To build the application, you will need to have a C++ compiler installed on your system. Follow these steps to compile the application:

1. Clone the repository and navigate to the root directory of the project in your terminal.
2. Initialize and update the Git submodules to retrieve `libx264`:
git submodule update --init --recursive
3. Run the `make` command to build the executable:
make
4. The build process will generate an executable named `yuv_to_h264`.

## Running the Application

After building the application, you can run it by following these steps:

1. For initial verification, a short YUV file named `big_buck_bunny_720p30_short.yuv` has been included in the `test` directory. This file is a truncated version of the full video and is suitable for quick tests.
2. To run the application with the full video, download the YUV file from this [Google Drive link](https://drive.google.com/file/d/13Zjc8h9i0IHkdXTxBlLofaJTN6oZNsi4/view?usp=sharing), and copy it to the `test` directory, replacing the short version.
3. Run the executable from the terminal:
./yuv_to_h264
4. The encoded output will be written to a file named `big_buck_bunny_720p30.264` in the test directory.

## Implementing Scene Change Detection

Your task is to implement the scene change detection logic within the `scene_change_detector.cpp` file. The `SceneChangeDetector` class has two methods:

- `detect_scene_change`: This method should analyze the raw YUV data of the current and previous frames to detect scene changes before encoding.
- `detect_scene_change_post_encoding`: This method should analyze the encoded data to detect scene changes after encoding.

You are expected to implement the algorithms for these methods to accurately detect scene changes and ensure keyframes are inserted correctly.

Good luck with your implementation!