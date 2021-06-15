#include "Key.h"

Key::Key(int code, int code_fn, int code_num, int code_num_fun) {
  this->code = code;
  this->code_fn = code_fn;
  this->code_num = code_num;
  this->code_num_fn = code_num_fun;
  this->col = 0;
  this->row = 0;
  this->state = false;
}

Key::Key(int code) {
  this->code = code;
  this->code_fn = code;
  this->code_num = code;
  this->code_num_fn = code;
  this->col = 0;
  this->row = 0;
  this->state = false;
}

Key::Key(int code, int code_fn, int code_num, int code_num_fun, int row, int col) {
  this->code = code;
  this->code_fn = code_fn;
  this->code_num = code_num;
  this->code_num_fn = code_num_fun;
  this->col = col;
  this->row = row;
  this->state = false;
}

Key::Key(int code, int row, int col) {
  this->code = code;
  this->code_fn = code;
  this->code_num = code;
  this->code_num_fn = code;
  this->col = col;
  this->row = row;
  this->state = false;
}

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

void Key::setup(int row, int col) {
  this->row = row;
  this->col = col;
}

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