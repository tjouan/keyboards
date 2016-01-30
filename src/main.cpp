#include "keyboards.h"


int is_printable(int key) {
  if (key < 128 && asciimap[key])
    return true;

  return false;
}

int is_modifier(int key) {
  if (key >= KEY_LEFT_CTRL && key <= KEY_RIGHT_GUI)
    return true;

  return false;
}

void key_press(int key) {
  if (is_modifier(key))
    report_modifier_add(key);
  else if (is_printable(key))
    report_key_add(asciimap[key]);
  else
    report_key_add(key);
}

void key_release(int key) {
  if (is_modifier(key))
    report_modifier_remove(key);
  else if (is_printable(key))
    report_key_remove(asciimap[key]);
  else
    report_key_remove(key);
}

uint8_t *report_key_chr(int key) {
  return (uint8_t *) memchr(report.keys, key, KEYS_STATE_MAX);
}

void report_key_add(int key) {
  uint8_t *b;

  if (report_key_chr(key) == NULL)
    if ((b = report_key_chr(0)))
      *b = key;
}

void report_key_remove(int key) {
  uint8_t *b;

  if ((b = report_key_chr(key)) != NULL)
    memmove(b, b + 1, KEYS_STATE_MAX - (b - report.keys));
}

void report_modifier_add(int key) {
  report.modifiers |= (1 << (key - 128));
}

void report_modifier_remove(int key) {
  report.modifiers &= ~(1 << (key - 128));
}

int report_compare() {
  if (memcmp(report.keys, report_reference.keys, KEYS_STATE_MAX) != 0)
    return 1;

  if (report.modifiers != report_reference.modifiers)
    return 1;

  return 0;
}

void report_update() {
  if (report_compare() != 0)
    Keyboard.sendReport(&report);

  report_reference = report;
}

void setup() {
  for (int ir = 0; ir < ROWS_COUNT; ir += 1)
    pinMode(INPUT_ROW_START + ir, INPUT);

  for (int ic = 0; ic < COLS_COUNT; ic += 1)
    pinMode(OUTPUT_COL_START + ic, OUTPUT);

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

      if (digitalRead(INPUT_ROW_START + ir))
        key_press(keymap[ir][ic]);
      else
        key_release(keymap[ir][ic]);
    }

    digitalWrite(OUTPUT_COL_START + ic, LOW);
  }

  report_update();
}
