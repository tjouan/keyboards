#include "Arduino.h"
#include "Keyboard.h"
// FIXME: arduino-mk does not allow to change the linker, and use avr-gcc
// instead of avr-g++.
// Using `-fno-threadsafe-statics' link option as workaround does not work.
// https://github.com/arduino/Arduino/commit/37ee800abdfc4b602083ef35f942d4f46917433a
#include "arduino_mk-linker_workarounds.h"
#include "ascii_to_dvorak.h"


#define VERSION               "0.0.1"
#define SERIAL_SPEED          115200
#define INPUT_ROW_0           A0
#define INPUT_ROW_1           A1
#define INPUT_ROW_2           A2
#define INPUT_ROW_3           A3
#define INPUT_ROW_4           A4
#define INPUT_ROW_5           A5
#define OUTPUT_COL_00         0
#define OUTPUT_COL_01         1
#define OUTPUT_COL_02         2
#define OUTPUT_COL_03         3
#define OUTPUT_COL_04         4
#define OUTPUT_COL_05         5
#define OUTPUT_COL_06         6
#define OUTPUT_COL_07         7
#define OUTPUT_COL_08         8
#define OUTPUT_COL_09         9
#define OUTPUT_COL_10         10
#define OUTPUT_COL_11         11
#define OUTPUT_COL_12         12
#define OUTPUT_COL_13         13
#define ROWS_COUNT            6
#define COLS_COUNT            14

#define KEY_ESC               0x29

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

KeyReport report          = { 0 };
KeyReport report_compare  = { 0 };

void key_press(int key);
void report_key_add(int key);
void report_key_remove(int key);
void report_modifier_add(int key);
void report_modifier_remove(int key);


int is_printable(int key) {
  if (asciimap[key]) {
    return true;
  }

  return false;
}

int is_modifier(int key) {
  if (key >= KEY_LEFT_CTRL && key <= KEY_RIGHT_GUI) {
    return true;
  }

  return false;
}

void key_press(int key) {
  if (is_modifier(key)) {
    report_modifier_add(key);
  }
  else if (is_printable(key)) {
    report_key_add(asciimap[key]);
  }
  else {
    report_key_add(key);
  }
}

void key_release(int key) {
  if (is_modifier(key)) {
    report_modifier_remove(key);
  }
  else if (is_printable(key)) {
    report_key_remove(asciimap[key]);
  }
  else {
    report_key_remove(key);
  }
}

void report_key_add(int key) {
  report.keys[0] = key;
}

void report_key_remove(int key) {
  if (report.keys[0] == key)
    report.keys[0] = 0;
}

void report_modifier_add(int key) {
  report.modifiers |= (1 << (key - 128));
}

void report_modifier_remove(int key) {
  report.modifiers &= ~(1 << (key - 128));
}

void setup() {
  pinMode(INPUT_ROW_0, INPUT);
  pinMode(INPUT_ROW_1, INPUT);
  pinMode(INPUT_ROW_2, INPUT);
  pinMode(INPUT_ROW_3, INPUT);
  pinMode(INPUT_ROW_4, INPUT);
  pinMode(INPUT_ROW_5, INPUT);
  pinMode(OUTPUT_COL_00, OUTPUT);
  pinMode(OUTPUT_COL_01, OUTPUT);
  pinMode(OUTPUT_COL_02, OUTPUT);
  pinMode(OUTPUT_COL_03, OUTPUT);
  pinMode(OUTPUT_COL_04, OUTPUT);
  pinMode(OUTPUT_COL_05, OUTPUT);
  pinMode(OUTPUT_COL_06, OUTPUT);
  pinMode(OUTPUT_COL_07, OUTPUT);
  pinMode(OUTPUT_COL_08, OUTPUT);
  pinMode(OUTPUT_COL_09, OUTPUT);
  pinMode(OUTPUT_COL_10, OUTPUT);
  pinMode(OUTPUT_COL_11, OUTPUT);
  pinMode(OUTPUT_COL_12, OUTPUT);
  pinMode(OUTPUT_COL_13, OUTPUT);

  Keyboard.begin();
}

void loop() {
  int ir = 0;
  int ic = 0;

  for (ic = 0; ic < COLS_COUNT; ic += 1) {
    digitalWrite(OUTPUT_COL_00 + ic, HIGH);

    for (ir = 0; ir < ROWS_COUNT; ir += 1) {
      if (!keymap[ir][ic])
        continue;

      if (digitalRead(INPUT_ROW_0 + ir)) {
        key_press(keymap[ir][ic]);
      }
      else {
        key_release(keymap[ir][ic]);
      }
    }

    digitalWrite(OUTPUT_COL_00 + ic, LOW);
  }

  if (report.keys[0] != report_compare.keys[0] ||
      report.modifiers != report_compare.modifiers) {
    Keyboard.sendReport(&report);
  }
  report_compare = report;
}
