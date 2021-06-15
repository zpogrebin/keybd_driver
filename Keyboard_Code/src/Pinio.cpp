#include "Pinio.h"
#include "Arduino.h"

// Class constructor. Sets up the pins, macros, and LED's
KeyboardHandler::KeyboardHandler() {
  setup();
  makeMacros();
  pinMode(led::r, OUTPUT);
  pinMode(led::g, OUTPUT);
  pinMode(led::b, OUTPUT);
}

// Setup helper function, defaults values, and sets up pin modes for keys
void KeyboardHandler::setup() {
  fnPressed = false;
  numPressed = false;
  recordMode = false;
  for(int row = 0; row <= NUMROWS; row++) pinMode(rowToPin(row), OUTPUT);
  for(int col = 0; col <= NUMCOLS; col++) {
    *portConfigRegister(col) = PORT_PCR_MUX(1) | PORT_PCR_PE;
  }
  for(int col = 0; col < NUMCOLS; col++) {
    for(int row = 0; row < NUMROWS; row++) {
      keyboard[col][row].setup(row, col);
    }
  }
}

// Scans all rows and columns and performs the apropriate action if a key is 
// pressed
void KeyboardHandler::scanKeys() {
  int newKey;
  for(int row = 0; row < NUMROWS; row++) {
    for(int i = 0; i < NUMROWS; i++) {
      if(i != row) digitalWrite(rowToPin(i), LOW);
      else digitalWrite(rowToPin(row), HIGH);
    }
    for(int col = 0; col < NUMCOLS; col++) {
      bool trueRecording = recordMode and recording >= 0;
      newKey = keyboard[col][row].update(fnPressed, numPressed, trueRecording);
      if(isMacro(newKey) and !recordMode) {
        macros[-newKey].doMacro();
      } else if(recordMode and recording <= 0 and isMacro(newKey)) {
        recording = -newKey;
        delay(100);
        macros[recording].clear();
      } else if(trueRecording and isKey(newKey)) {
        macros[recording].addKey(row, col, newKey < 0);
      }
    }
  }
}

// Updates Fn/Num/Shift and updates the LED controls 
void KeyboardHandler::updateModifiers() {
  if(!recordMode) {
    if(keyboard[1][0].turnedOn()) fnPressed = !fnPressed;
    if(keyboard[0][0].turnedOn()) numPressed = !numPressed;
  } else if(keyboard[2][0].turnedOn()) recordMode = false;
  shiftPressed = keyboard[3][3].isPressed() or keyboard[16][3].isPressed();
  if(keyboard[2][0].turnedOn() and fnPressed and numPressed) {
    if(shiftPressed) {
      recordMode = !recordMode;
      recording = -1;
    }
  }
}

// Constructs macro class instances
void KeyboardHandler::makeMacros() {
  int size = KEYSSTORED/NUMMACROS;
  for(int i = 0; i < NUMMACROS; i++) {
    macros[i] = Macro{i*size, size, this};
  }
}

// Update Wrapper Function
void KeyboardHandler::update() {
  updateLEDs();
  scanKeys();
  updateModifiers();
}

// Updates the values of status LED's
void KeyboardHandler::updateLEDs() {
  digitalWrite(led::r, recordMode);
  digitalWrite(led::g, fnPressed);
  digitalWrite(led::b, numPressed);
}

// Executes a keypress.
void KeyboardHandler::doKey(int code) {
    bool keyup;
    if(code > 127) {
        keyup = true;
        code = 255 - code + 1;
    } else keyup = false;
    int row = code / NUMCOLS;
    int col = code % NUMCOLS;
    keyboard[col][row].doKey(keyup);
}