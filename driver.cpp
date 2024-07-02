#include "driver.h"

MatrixDriver::MatrixDriver(HUB75Connector &connector, int shiftDelay,
                           colour colourMode)
    : connector(connector),
      selectedRow(0),
      delay(shiftDelay),
      colourMode(colourMode) {}

void MatrixDriver::setBuffer(std::vector<uint8_t> buffer) {
  displayBuffer.setBuffer(buffer);
}

/**
 * Encode a new row number into the row address pins.
 *
 * @param row The row number to be set.
 */
void MatrixDriver::setRowAddress(int row) {
  connector.setPin(OE, LOW);
  connector.setPin(A, row & 0x01 ? HIGH : LOW);
  connector.setPin(B, row & 0x02 ? HIGH : LOW);
  connector.setPin(C, row & 0x04 ? HIGH : LOW);
  connector.setPin(D, row & 0x08 ? HIGH : LOW);
  connector.setPin(OE, HIGH);
  selectedRow = row;
}

/**
 * Pushes data for the specified row index pair into the connector by setting
 * the RBG pins and clocking.
 *
 * @param row The row number to be loaded.
 */
void MatrixDriver::loadRow(int row) {
  setRowAddress(row);
  const int start_idx_top = WIDTH * row * 3;
  const int start_idx_bottom = (row + HEIGHT / 2) * WIDTH * 3;
  std::bitset<WIDTH * N_SUBFRAMES> r_top_seq = buildSubframeSequence(start_idx_top);
  std::bitset<WIDTH * N_SUBFRAMES> r_bottom_seq = buildSubframeSequence(start_idx_bottom);
  std::bitset<WIDTH * N_SUBFRAMES> g_top_seq = buildSubframeSequence(start_idx_top + 1);
  std::bitset<WIDTH * N_SUBFRAMES> g_bottom_seq = buildSubframeSequence(start_idx_bottom + 1);
  std::bitset<WIDTH * N_SUBFRAMES> b_top_seq = buildSubframeSequence(start_idx_top + 2);
  std::bitset<WIDTH * N_SUBFRAMES> b_bottom_seq = buildSubframeSequence(start_idx_bottom + 2);
  for (int i = 0; i < WIDTH * N_SUBFRAMES; i++) {
    connector.setPin(R1, r_top_seq[i] ? HIGH : LOW);
    connector.setPin(G1, g_top_seq[i] ? HIGH : LOW);
    connector.setPin(B1, b_top_seq[i] ? HIGH : LOW);
    connector.setPin(R2, r_bottom_seq[i] ? HIGH : LOW);
    connector.setPin(G2, g_bottom_seq[i] ? HIGH : LOW);
    connector.setPin(B2, b_bottom_seq[i] ? HIGH : LOW);
    clock();
    if (i % WIDTH == 0) {
      latch();
    }
  }
}

void MatrixDriver::offDelay() { 
  std::this_thread::sleep_for((100 - brightness) * 0.01 * std::chrono::milliseconds(delay));
}
void MatrixDriver::onDelay() { 
  std::this_thread::sleep_for(brightness * 0.01 *std::chrono::milliseconds(delay));
}

/**
 * Load the currently selected row and select the next one.
 */
void MatrixDriver::loadNextRow() {
  loadRow(selectedRow);
  selectedRow = (selectedRow + 1) % (HEIGHT / 2);
}

void MatrixDriver::clock() {
  connector.setPin(CLK, HIGH);
  connector.setPin(CLK, LOW);
}
/*
 * Latching causes the current data to be displayed
 */
void MatrixDriver::latch() {
  connector.setPin(OE, LOW);
  connector.setPin(Latch, HIGH);
  connector.setPin(Latch, LOW);
  offDelay();
  connector.setPin(OE, HIGH);
  onDelay();
}

int MatrixDriver::getSubframeBit(int frameNo) { return frameNo + 4; }

/*
 * Build the bitset that comprises the pin states for all the subframes of a
 * given colour
 */
std::bitset<WIDTH * N_SUBFRAMES> MatrixDriver::buildSubframeSequence(
    int buffer_idx) {
  std::bitset<WIDTH * N_SUBFRAMES> sequence;
  for (int i = 0; i < WIDTH * N_SUBFRAMES; i++) {
    int frame = i / WIDTH;
    int pixel = i % WIDTH;
    int subframe = frameOrder[frame];
    sequence.set(i, displayBuffer.colSequence(buffer_idx, pixel) &
                        (1 << getSubframeBit(subframe)));
  }
  return sequence;
}

void MatrixDriver::setBrightness(int brightness) {
  if (brightness < 0 || brightness > 100) {
    throw std::invalid_argument("Brightness must be between 0 and 100");
  }
  this->brightness = brightness;
}