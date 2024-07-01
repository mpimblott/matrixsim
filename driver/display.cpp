#include "display.h"

#include <iostream>
#include <chrono>
#include <thread>

MatrixDisplay::MatrixDisplay(sf::RenderWindow& window) : window(window) {
  matrixTexture.create(WIDTH, HEIGHT);
  matrixSprite.setTexture(matrixTexture);
  matrixSprite.setScale(60, 60);
}

void MatrixDisplay::setBufferRow(int row, std::bitset<WIDTH> rBuffer,
                                 std::bitset<WIDTH> gBuffer,
                                 std::bitset<WIDTH> bBuffer) {
  for (int i = 0; i < WIDTH; i++) {
    const int idx = (row * WIDTH + i) * 4;
    displayBuffer[idx] = rBuffer[i] ? 0xFF : 0x00;
    displayBuffer[idx + 1] = gBuffer[i] ? 0xFF : 0x00;
    displayBuffer[idx + 2] = bBuffer[i] ? 0xFF : 0x00;
    displayBuffer[idx + 3] = 0xFF;
  }
  printBufferRow(row);
}

void MatrixDisplay::updateTexture() {
  matrixTexture.update(displayBuffer.data());
  matrixSprite.setTexture(matrixTexture);
}

void MatrixDisplay::setBufferRGB(std::vector<uint8_t> buffer) {
  for (int i = 0; i < WIDTH*HEIGHT; i += 1) {
    int src_idx = i * 3;
    int dst_idx = i * 4;
    displayBuffer[dst_idx] = buffer[src_idx];
    displayBuffer[dst_idx + 1] = buffer[src_idx + 1];
    displayBuffer[dst_idx + 2] = buffer[src_idx + 2];
    displayBuffer[dst_idx + 3] = 0xFF;
  }
}

void MatrixDisplay::printBuffer() {
  for (int i = 0; i < WIDTH * HEIGHT * 4; i += 4) {
    if (i % (WIDTH * 4) == 0) std::cout << std::endl;
    std::cout << "(" << unsigned(displayBuffer[i]) << ", "
              << unsigned(displayBuffer[i + 1]) << ", "
              << unsigned(displayBuffer[i + 2]) << ", "
              << unsigned(displayBuffer[i + 3]) << ")";
  }
  std::cout << std::endl;
}

void MatrixDisplay::printBufferRow(int row) {
  for (int i = 0; i < WIDTH * 4; i += 4) {
    std::cout << "(" << unsigned(displayBuffer[row * WIDTH * 4 + i]) << ", "
              << unsigned(displayBuffer[row * WIDTH * 4 + i + 1]) << ", "
              << unsigned(displayBuffer[row * WIDTH * 4 + i + 2]) << ", "
              << unsigned(displayBuffer[row * WIDTH * 4 + i + 3]) << ")";
  }
  std::cout << std::endl;
}

bool MatrixDisplay::isOpen() { return window.isOpen(); }

void MatrixDisplay::update() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }
  window.clear();
  updateTexture();
  window.draw(matrixSprite);
  window.display();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}