#include "Macro.h"
#include "Pinio.h"
#include "Keyboard.h"

////////// Key Encoding method: ////////// 
// Macro codes: (uint8) = col + (number of columns * row)
// If the key is a release, take the two's complement of macrovalue (negative)
// Note: Macros cannot contain the escape key (yeah yeah it's a limitation)
//////////////////////////////////////////

// Constructor function -- sets memory location and parameters
Macro::Macro(int starting_key, int max_keys, KeyboardHandler *keyboard) {
    this->keyboard = keyboard;
    this->starting_key = starting_key;
    this->max_keys = max_keys;
}

// Default Constructor
Macro::Macro() {
    this->starting_key = 0;
    this->max_keys = 0;
}

// Executes the macro
void Macro::doMacro() {
    int offset = 0;
    while(offset < max_keys) {
        if(doKey(offset)) return;
        delay(5);
        offset++;
    }
}

// Execute a key in the macro
// Returns true if the key is a '\0' character
bool Macro::doKey(int offset) {
    int value = EEPROM.read(starting_key + offset);
    if(!value) return true;
    keyboard->doKey(value);
    return false;
}

// Resets the macro
void Macro::clear() {
    for(int i = 0; i < max_keys * 2; i++) EEPROM.write(starting_key + i, 0);
}

// Adds a key to the end of the macro, encodign it 
void Macro::addKey(int row, int col, bool press) {
    int value = col + NUMCOLS * row;
    if(press) value = -value;
    int offset = 0;
    while(offset < max_keys) {
        if(!getKey(offset)) {
            if(value == 0 or value == -63 or value == -2 or value == KEY_ESC) {
                return;
            }
            EEPROM.write(offset + starting_key, (uint8_t)value);
            doKey(offset);
            return;
        }
        offset++;
    }
}

// Gets the stored value for a specific key.
int Macro::getKey(int offset) {
    if(offset >= max_keys) return 0;
    return EEPROM.read(starting_key+offset);
}