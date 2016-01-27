#include "keyboards.h"


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
  for (int ir = 0; ir < ROWS_COUNT; ir += 1) {
    pinMode(INPUT_ROW_START + ir, INPUT);
  }

  for (int ic = 0; ic < COLS_COUNT; ic += 1) {
    pinMode(OUTPUT_COL_START + ic, OUTPUT);
  }

  Keyboard.begin();
}

void loop() {
  int ir = 0;
  int ic = 0;

  for (ic = 0; ic < COLS_COUNT; ic += 1) {
    digitalWrite(OUTPUT_COL_START + ic, HIGH);

    for (ir = 0; ir < ROWS_COUNT; ir += 1) {
      if (!keymap[ir][ic])
        continue;

      if (digitalRead(INPUT_ROW_START + ir)) {
        key_press(keymap[ir][ic]);
      }
      else {
        key_release(keymap[ir][ic]);
      }
    }

    digitalWrite(OUTPUT_COL_START + ic, LOW);
  }

  if (report.keys[0] != report_compare.keys[0] ||
      report.modifiers != report_compare.modifiers) {
    Keyboard.sendReport(&report);
  }
  report_compare = report;
}
