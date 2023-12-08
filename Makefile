CXX := g++
CXXFLAGS := -Wall -Wextra -O2 -std=c++11
X264_DIR := libx264
X264_BUILD_DIR := $(X264_DIR)/build
X264_LIB := $(X264_BUILD_DIR)/lib/libx264.a
INCLUDES := -I$(X264_BUILD_DIR)/include
LIBDIRS := -L$(X264_BUILD_DIR)/lib
LIBS := -lx264 -lpthread -lm
SOURCES := main.cpp yuv_reader.cpp x264_encoder.cpp scene_change_detector.cpp
OBJ_DIR := build
OBJECTS := $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE := yuv_to_h264

.PHONY: all clean libx264

all: $(EXECUTABLE)

$(EXECUTABLE): $(X264_LIB) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBDIRS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(X264_LIB):
	cd $(X264_DIR) && ./configure --enable-static --prefix=$(PWD)/$(X264_BUILD_DIR) && $(MAKE) && $(MAKE) install

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)
	cd $(X264_DIR) && $(MAKE) clean