#include "Macro.h"
#include "Pinio.h"
#include "Keyboard.h"

Macro::Macro(int starting_key, int max_keys, KeyboardHandler *keyboard) {
    this->keyboard = keyboard;
    this->starting_key = starting_key;
    this->max_keys = max_keys;
}

Macro::Macro() {
    this->starting_key = 0;
    this->max_keys = 0;
}

void Macro::doMacro() {
    int offset = 0;
    while(offset < max_keys) {
        if(doKey(offset)) return;
        delay(5);
        offset++;
    }
}

bool Macro::doKey(int offset) {
    int value = EEPROM.read(starting_key + offset);
    if(!value) return true;
    keyboard->doKey(value);
    return false;
}

void Macro::clear() {
    for(int i = 0; i < max_keys * 2; i++) EEPROM.write(starting_key + i, 0);
}

void Macro::addKey(int row, int col, bool press) {
    int value = col + NUMCOLS * row;
    if(press) value = -value;
    int offset = 0;
    while(offset < max_keys) {
        if(!getKey(offset)) {
            if(value == 0 or value == -63 or value == -2) return;
            EEPROM.write(offset + starting_key, (uint8_t)value);
            doKey(offset);
            return;
        }
        offset++;
    }
}

int Macro::getKey(int offset) {
    if(offset >= max_keys) return 0;
    return EEPROM.read(starting_key+offset);
}