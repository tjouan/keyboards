#include "Arduino.h"
// FIXME: arduino-mk does not allow to change the linker, and use avr-gcc
// instead of avr-g++.
// Using `-fno-threadsafe-statics' link option as workaround does not work.
// https://github.com/arduino/Arduino/commit/37ee800abdfc4b602083ef35f942d4f46917433a
#include "arduino_mk-linker_workarounds.h"
#include "arduino_keyboard.h"

#include "ascii_to_dvorak.h"


#define INPUT_ROW_START       A0
#define OUTPUT_COL_START      0
#define ROWS_COUNT            6
#define COLS_COUNT            14
#define KEYS_STATE_MAX        6

int keymap[6][14] = {
  {'`', '1', '2', '3', '4', '5', '\b',
    '6', '7', '8', '9', '0', '[', ']'},
  {'\t', '\'', ',', '.', 'p', 'y', 0,
    'f', 'g', 'c', 'r', 'l', '/', '='},
  {0, 'a', 'o', 'e', 'u', 'i', '\n',
    'd', 'h', 't', 'n', 's', '-', 0},
  {KEY_LEFT_GUI, ';', 'q', 'j', 'k', 'x', 0,
    'b', 'm', 'w', 'v', 'z', '\\', KEY_RIGHT_GUI},
  {0, KEY_ESC, 0, 0, KEY_INSERT, KEY_DELETE, ' ',
    0, KEY_RIGHT_SHIFT, KEY_PAGE_UP, KEY_HOME, 0, 0, 0},
  {KEY_LEFT_CTRL, 0, KEY_LEFT_ALT, 0, KEY_LEFT_SHIFT, 0, 0,
    0, 0, KEY_PAGE_DOWN, KEY_END, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, 0}
};

KeyReport report            = { 0 };
KeyReport report_reference  = { 0 };


int is_printable(int key);
int is_modifier(int key);

void key_press(int key);
void key_release(int key);

uint8_t *report_key_chr(int key);
void report_key_add(int key);
void report_key_remove(int key);
void report_modifier_add(int key);
void report_modifier_remove(int key);
int report_compare();
void report_update();
