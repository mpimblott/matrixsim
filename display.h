#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <array>
#include <bitset>
#include <vector>

#include "util.h"

class MatrixDisplay {
 public:
  MatrixDisplay(sf::RenderWindow& window);
  void setBufferRow(int row, std::bitset<WIDTH> rBuffer,
                    std::bitset<WIDTH> gBuffer, std::bitset<WIDTH> bBuffer);
  bool isOpen();
  void update();
  void setBufferRGB(std::vector<uint8_t> buffer);
  void printBuffer();
  void printBufferRow(int row);

 private:
  sf::RenderWindow& window;
  sf::Texture matrixTexture;
  sf::Sprite matrixSprite;
  std::array<uint8_t, WIDTH * HEIGHT * 4> displayBuffer = {}; // Initialize to 0
  void updateTexture();
};;

#endif