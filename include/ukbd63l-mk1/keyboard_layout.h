#include "ascii_to_dvorak.h"


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
