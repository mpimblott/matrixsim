#ifndef IMGBUFFER_H
#define IMGBUFFER_H

#include <stdint.h>

#include <vector>

#include "util.h"

// should store the rgb bytes for the image, but want r,g,b to be separate for ease of use

class ImgBuffer {
 public:
  ImgBuffer() = default;
  ImgBuffer(std::vector<uint8_t> data);
  void setBuffer(std::vector<uint8_t> data);
  const std::vector<uint8_t>& getBuffer() const;
  uint8_t& operator[](int idx);
  int size() const;
  uint8_t& r(int idx);
  uint8_t& g(int idx);
  uint8_t& b(int idx);
  uint8_t& colSequence(int start_idx, int idx);

 private:
  std::vector<uint8_t> bufferData;
};

#endif