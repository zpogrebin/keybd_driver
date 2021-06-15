#include "Key.h"

// Class constructor. Takes the ascii codes for pressing under the four cases.
// Nothing, Fn pressed, Num pressed, Num+Fn pressed.
Key::Key(int code, int code_fn, int code_num, int code_num_fun) {
  this->code = code;
  this->code_fn = code_fn;
  this->code_num = code_num;
  this->code_num_fn = code_num_fun;
  this->col = 0;
  this->row = 0;
  this->state = false;
}

// Class Constructor. Takes the ascii code for pressing.
Key::Key(int code) {
  this->code = code;
  this->code_fn = code;
  this->code_num = code;
  this->code_num_fn = code;
  this->col = 0;
  this->row = 0;
  this->state = false;
}

// Class Constructor. Same as the #1 but also accepts row and column
Key::Key(int code, int code_fn, int code_num, int code_num_fun, int row, int col) {
  this->code = code;
  this->code_fn = code_fn;
  this->code_num = code_num;
  this->code_num_fn = code_num_fun;
  this->col = col;
  this->row = row;
  this->state = false;
}

// Class Constructor. Same as the #2 but also accepts row and column
Key::Key(int code, int row, int col) {
  this->code = code;
  this->code_fn = code;
  this->code_num = code;
  this->code_num_fn = code;
  this->col = col;
  this->row = row;
  this->state = false;
}

// Update function. Checks the state of the key and updates it. Accepts the 
// State of the modifier keys and whether the system is recording a macro.
// Returns the key code (and also does the key press if necessary)
int Key::update(bool fn_pressed, bool num_pressed, bool recording) {
  prev_state = state;
  state = digitalRead(col);
  if(state == prev_state) return 0;
  if(!recording) return doKey(fn_pressed, num_pressed, !state);
  else {
    if(state) return row * 20 + col; //Return for macro recorder
    else return -(row * 20 + col);
  }
}

// Executes the key press by sending the appropriate HID Code. Accepts the 
// State of the modifier keys and whether the system is recording a macro.
// Returns the key code.
int Key::doKey(bool fn_pressed, bool num_pressed, bool keyup) {
  int key;
  if(!fn_pressed and !num_pressed) key = code;
  else if(fn_pressed and num_pressed) key = code_num_fn;
  else if(fn_pressed) key = code_fn;
  else key = code_num;
  if(key > 0) { //Actually press
    if(!keyup) Keyboard.press(key);
    else Keyboard.release(key);
    return 0;
  } else if((key != KEY_NONE) and !keyup) return key; //Access macros
  return 0;
}

// Setup function for use with #1 and #2 constructor. Sets the "location" of the
// key.
void Key::setup(int row, int col) {
  this->row = row;
  this->col = col;
}

// Debugging print function. Does not work when in HID mode.
void Key::writeInfo() {
  //Serial.print(code);
  Serial.print("COL | ROW: ");
  Serial.print(col);
  Serial.print("|");
  Serial.print(row);
  if(state) {
    Serial.println(" ON");
  } else Serial.println(" OFF");
}