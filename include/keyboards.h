#include "Arduino.h"
// FIXME: arduino-mk does not allow to change the linker, and use avr-gcc
// instead of avr-g++.
// Using `-fno-threadsafe-statics' link option as workaround does not work.
// https://github.com/arduino/Arduino/commit/37ee800abdfc4b602083ef35f942d4f46917433a
#include "arduino_mk-linker_workarounds.h"
#include "arduino_keyboard.h"

#ifdef KEYMAP_DVORAK
#include "ascii_to_dvorak.h"
#else
#include "ascii_to_qwerty.h"
#endif


#define ROWS_COUNT            6
#define COLS_COUNT            14
#define KEYS_STATE_MAX        6
#define KEY_FUNCTION          0xe8

const uint8_t rows_pins[ROWS_COUNT] = {
  A5, A4, A3, A2, A1, A0
};
const uint8_t cols_pins[COLS_COUNT] = {
  0, 1, 13, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

int keymap[ROWS_COUNT][COLS_COUNT] = {
  {'`', '1', '2', '3', '4', '5', '\b',
    '6', '7', '8', '9', '0', '[', ']'},
  {'\t', '\'', ',', '.', 'p', 'y', 0,
    'f', 'g', 'c', 'r', 'l', '/', '='},
  {0, 'a', 'o', 'e', 'u', 'i', '\n',
    'd', 'h', 't', 'n', 's', '-', 0},
  {KEY_LEFT_GUI, ';', 'q', 'j', 'k', 'x', 0,
    'b', 'm', 'w', 'v', 'z', '\\', KEY_RIGHT_GUI},
  {0, KEY_ESC, KEY_FUNCTION, 0, KEY_INSERT, KEY_DELETE, ' ',
    0, KEY_RIGHT_SHIFT, KEY_PAGE_UP, KEY_HOME, 0, 0, 0},
  {KEY_LEFT_CTRL, 0, KEY_LEFT_ALT, 0, KEY_LEFT_SHIFT, 0, 0,
    0, 0, KEY_PAGE_DOWN, KEY_END, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, 0}
};
int keymap_function[ROWS_COUNT][COLS_COUNT] = {
  {0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, 0,
    KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0,
    0, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, KEY_FUNCTION, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

KeyReport report            = { 0 };
KeyReport report_reference  = { 0 };

int ir, ic;

int function_active;


int is_function_active();
int is_function_key(int key);
int is_printable(int key);
int is_modifier(int key);

void function_activate();
void function_deactivate();

void key_press(int key);
void key_release(int key);

uint8_t *report_key_chr(int key);
void report_key_add(int key);
void report_key_remove(int key);
void report_modifier_add(int key);
void report_modifier_remove(int key);
int report_compare();
void report_update();
void scan();
int scan_cell(int row, int col);
