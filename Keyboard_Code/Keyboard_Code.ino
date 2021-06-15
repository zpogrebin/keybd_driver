#include "src/Pinio.h"

KeyboardHandler board{};

void setup() {
  Serial.begin(115200);
  board.setup();
}

void loop() {
  board.update();
  delay(1);
}
