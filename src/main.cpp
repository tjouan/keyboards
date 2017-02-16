#include "keyboards.h"


int is_function_active() {
  return function_active;
}

int is_function_key(int key) {
  if (key == KEY_FUNCTION)
    return true;

  return false;
}

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

void function_activate() {
  if (is_function_active())
    return;

  function_active = true;
  report = { 0 };
}

void function_deactivate() {
  if (!is_function_active())
    return;

  function_active = false;
  report = { 0 };
}

void key_press(int key) {
  if (is_function_key(key))
    function_activate();
  if (is_modifier(key))
    report_modifier_add(key);
  else if (is_printable(key) && !is_function_active())
    report_key_add(asciimap[key]);
  else
    report_key_add(key);
}

void key_release(int key) {
  if (is_function_key(key))
    function_active = 0;
  if (is_modifier(key))
    report_modifier_remove(key);
  else if (is_printable(key) && !is_function_active())
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

void scan() {
  int scan_state = 0;

  for (ic = 0; ic < COLS_COUNT; ic += 1) {
    digitalWrite(cols_pins[ic], HIGH);

    for (ir = 0; ir < ROWS_COUNT; ir += 1) {
      if (!scan_cell(ir, ic))
        continue;

      scan_state = digitalRead(rows_pins[ir]);
#ifdef DEBUG_SERIAL
      sprintf(serial_buf, "SCANNING %d,%d state: %d", ic, ir, scan_state);
      Serial.println(serial_buf);
#endif
      if (scan_state)
        key_press(scan_cell(ir, ic));
      else
        key_release(scan_cell(ir, ic));
    }

    digitalWrite(cols_pins[ic], LOW);
  }
}

int scan_cell(int row, int col) {
  if (is_function_active())
    return keymap_function[row][col];

  return keymap[row][col];
}

void setup() {
  function_deactivate();

  for (ir = 0; ir < ROWS_COUNT; ir += 1)
    pinMode(rows_pins[ir], INPUT);

  for (ic = 0; ic < COLS_COUNT; ic += 1)
    pinMode(cols_pins[ic], OUTPUT);

  Keyboard.begin();
#ifdef DEBUG_SERIAL
  Serial.begin(SERIAL_SPEED);
#endif
}

void loop() {
  scan();
  report_update();
}
