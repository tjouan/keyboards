#include <Arduino.h>

#include "arduino_keyboard.h"
#include "keyboard_layout.h"

#define SERIAL_SPEED 115200

KeyReport report            = { 0 };
KeyReport report_reference  = { 0 };

int ir, ic;

int function_active;

#ifdef DEBUG_SERIAL
  char serial_buf[80];
#endif


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
