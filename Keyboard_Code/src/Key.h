#ifndef KEY_H_
#define KEY_H_

#include <usb_desc.h>
#include <Arduino.h>
#include "Keyboard.h"

const int KEY_NONE = -1000;

class Key {
  public:
    Key(int code);
    Key(int code, int code_fn, int code_num, int code_num_fun);
    Key(int code, int row, int col);
    Key(int code, int code_fn, int code_num, int code_num_fun, int row, int col);
    int update(bool fn_pressed, bool num_pressed, bool recordMode);
    inline bool isPressed() {return this->state;}
    inline bool turnedOn() {return (state and !prev_state);}
    inline bool turnedOff() {return (!state and prev_state);}
    void setup(int row, int col);
    void writeInfo();
    inline int doKey(bool keyup) {return doKey(false, false, keyup);}
    int doKey(bool fn_pressed, bool num_pressed, bool keyup);

  private:
    int code;
    int code_fn;
    int code_num;
    int code_num_fn;
    int col;
    int row;
    bool state;
    bool prev_state;
};

#endif