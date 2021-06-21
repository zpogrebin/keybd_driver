#include "src/Pinio.h"

KeyboardHandler board{};

void setup() {
  Serial.begin(115200);
  board.setup();
}

void loop() {
  board.update();
  //delay(2);
}
Row 0_x_________________
Row 1___________________
Row 2___________________
Row 3___________________
Row 4___________________
