#ifndef MACRO_H_
#define MACRO_H_

#include "Arduino.h"
#include "EEPROM.h"

class KeyboardHandler;

class Macro {

    public:
        Macro(int starting_key, int max_keys, KeyboardHandler *keyboard);
        Macro(); //Invalid constructor
        void doMacro();
        bool doKey(int value);
        void clear();
        void addKey(int row, int col, bool press);
        
    private:        
        int starting_key;
        int max_keys;
        KeyboardHandler *keyboard;
        int getKey(int offset);
};

#endif