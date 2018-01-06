#include "ascii_to_dvorak.h"


#define ROWS_COUNT            2
#define COLS_COUNT            2
#define KEYS_STATE_MAX        6
#define KEY_FUNCTION          0xe8
#define UKBD_INPUT_PULLUP

const uint8_t rows_pins[ROWS_COUNT] = {
  A1, A0
};
const uint8_t cols_pins[COLS_COUNT] = {
  0, 1
};

int keymap[ROWS_COUNT][COLS_COUNT] = {
  {'h', 't'},
  {'n', 's'}
};
int keymap_function[ROWS_COUNT][COLS_COUNT] = {
  {'h', 't'},
  {'n', 's'}
};
