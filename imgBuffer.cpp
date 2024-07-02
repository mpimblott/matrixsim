#include "imgBuffer.h"

ImgBuffer::ImgBuffer(std::vector<uint8_t> data) {
  bufferData = data;
}

void ImgBuffer::setBuffer(std::vector<uint8_t> data) {
  bufferData = data;
}

const std::vector<uint8_t>& ImgBuffer::getBuffer() const {
  return bufferData;
}

uint8_t& ImgBuffer::operator[](int idx) {
  return bufferData[idx];
}

int ImgBuffer::size() const {
  return bufferData.size();
}

uint8_t& ImgBuffer::r(int idx) {
  return bufferData[idx * 3];
}

uint8_t& ImgBuffer::g(int idx) {
  return bufferData[idx * 3 + 1];
}

uint8_t& ImgBuffer::b(int idx) {
  return bufferData[idx * 3 + 2];
}

uint8_t& ImgBuffer::colSequence(int start_idx, int idx) {
  return bufferData[start_idx + idx * 3];
}