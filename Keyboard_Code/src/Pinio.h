#ifndef PINIO_H_
#define PINIO_H_

#define NUMCOLS 19
#define NUMROWS 5
#define NUMMACROS 64
#define KEYSSTORED 2048

#include "Arduino.h"
#include <usb_desc.h>
#include "Macro.h"
#include "Key.h"
#include "Keyboard.h"

namespace led {
  const int r = 27;
  const int g = 29;
  const int b = 26;
};

class Macro;

class KeyboardHandler {

  private:
    //Keyboard Descriptor
    Key keyboard[NUMCOLS][NUMROWS] = {
      { //COLUMN 1
        Key(-6), 
        Key(KEY_MEDIA_PREV_TRACK, KEY_F7, KEYPAD_7, -7),
        Key(KEY_MEDIA_MUTE, KEY_F4, KEYPAD_4, -8),
        Key(KEY_F14, KEY_F1, KEYPAD_1, -9),
        Key(KEYPAD_0)
      },
      { //COLUMN 2
        Key(KEY_NONE),
        Key(KEY_MEDIA_PLAY_PAUSE, KEY_F8, KEYPAD_8, -10),
        Key(KEY_MEDIA_VOLUME_DEC, KEY_F5, KEYPAD_5, -11),
        Key(KEY_F15, KEY_F2, KEYPAD_2, -12),
        Key(KEY_NONE),
      },
      { //COLUMN 3
        Key(KEY_ESC),
        Key(KEY_MEDIA_NEXT_TRACK, KEY_F9, KEYPAD_9, -13),
        Key(KEY_MEDIA_VOLUME_INC, KEY_F6, KEYPAD_6, -14),
        Key(KEY_NONE, KEY_F3, KEYPAD_3, -15),
        Key(KEYPAD_PERIOD),
      },
      { //COLUMN 4
        Key(KEY_TILDE),
        Key(KEY_TAB),
        Key(KEY_CAPS_LOCK),
        Key(KEY_LEFT_SHIFT),
        Key(KEY_LEFT_CTRL),
      },
      { //COLUMN 5
        Key(KEY_1), Key(KEY_Q), Key(KEY_A), Key(KEY_Z), Key(KEY_LEFT_ALT)
      },
      { //COLUMN 6
        Key(KEY_2), Key(KEY_W), Key(KEY_S), Key(KEY_X), Key(KEY_LEFT_GUI)
      },
      { //COLUMN 7
        Key(KEY_3), Key(KEY_E), Key(KEY_D), Key(KEY_C), Key(KEY_NONE)
      },
      { //COLUMN 8
        Key(KEY_4), Key(KEY_R), Key(KEY_F), Key(KEY_V), Key(KEY_NONE)
      },
      { //COLUMN 9
        Key(KEY_5), Key(KEY_T), Key(KEY_G), Key(KEY_B), Key(KEY_SPACE)
      },
      { //COLUMN 10
        Key(KEY_6), Key(KEY_Y), Key(KEY_H), Key(KEY_N), Key(KEY_NONE)
      },
      { //COLUMN 11
        Key(KEY_7), Key(KEY_U), Key(KEY_J), Key(KEY_M), Key(KEY_NONE)
      },
      { //COLUMN 12
        Key(KEY_8), Key(KEY_I), Key(KEY_K), Key(KEY_COMMA), Key(KEY_NONE)
      },
      { //COLUMN 13
        Key(KEY_9), Key(KEY_O), Key(KEY_L), Key(KEY_PERIOD), Key(KEY_RIGHT_GUI)
      },
      { //COLUMN 14
        Key(KEY_0), Key(KEY_P), Key(KEY_SEMICOLON), Key(KEY_SLASH), Key(KEY_RIGHT_ALT)
      },
      { //COLUMN 15
        Key(KEY_MINUS), 
        Key(KEY_LEFT_BRACE), 
        Key(KEY_QUOTE),
        Key(KEY_NONE),
        Key(KEY_NONE)
      },
      { //COLUMN 16
        Key(KEY_EQUAL), 
        Key(KEY_RIGHT_BRACE), 
        Key(KEY_NONE),
        Key(KEY_NONE),
        Key(KEY_RIGHT_CTRL)
      },
      { //COLUMN 17
        Key(KEY_BACKSPACE), 
        Key(KEY_BACKSLASH), 
        Key(KEY_ENTER),
        Key(KEY_RIGHT_SHIFT),
        Key(KEYPAD_ENTER)
      },
      { //COLUMN 18
        Key(-1), //1,3
        Key(-2), //1,2  
        Key(-3), //2,1
        Key(-4), //2,2
        Key(-5)  //2,1 
      },
      { //COLUMN 19
        Key(-6),
        Key(KEY_UP),
        Key(KEY_RIGHT),
        Key(KEY_DOWN),
        Key(KEY_LEFT)
      }
    };

    bool fnPressed;
    bool numPressed;
    bool shiftPressed;
    bool recordMode;
    int recording;

    Macro macros[NUMMACROS];

    inline int rowToPin(int row) {return row + NUMCOLS;}
    void makeMacros();
    inline int isMacro(int test) {return test < 0 and test != -1000;}
    inline int isKey(int test) {return test != 0 and test != 1000;}

  public:
    KeyboardHandler();
    void doKey(int code);
    void update();
    void switchRows(int row);
    void scanKeys();
    void updateModifiers();
    void setup();
    void updateLEDs();
};

#endif