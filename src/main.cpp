#include "Arduino.h"
#include "HID.h"
#include "Keyboard.h"
// FIXME: arduino-mk does not allow to change the linker, and use avr-gcc
// instead of avr-g++.
// Using `-fno-threadsafe-statics' link option as workaround does not work.
// https://github.com/arduino/Arduino/commit/37ee800abdfc4b602083ef35f942d4f46917433a
#include "arduino_mk-linker_workarounds.h"

#define VERSION               "0.0.1"
#define SERIAL_SPEED          115200
#define INPUT_ROW_0           2
#define INPUT_ROW_1           3
#define OUTPUT_COL_0          4
#define OUTPUT_COL_1          5
#define ROWS_COUNT            2
#define COLS_COUNT            2


void setup() {
  pinMode(INPUT_ROW_0, INPUT);
  pinMode(INPUT_ROW_1, INPUT);
  pinMode(OUTPUT_COL_0, OUTPUT);
  pinMode(OUTPUT_COL_1, OUTPUT);

  Keyboard.begin();
}

void loop() {
  int ir = 0;
  int ic = 0;

  for (ic = 0; ic < COLS_COUNT; ic += 1) {
    digitalWrite(OUTPUT_COL_0 + ic, HIGH);

    for (ir = 0; ir < ROWS_COUNT; ir += 1) {
      if (digitalRead(INPUT_ROW_0 + ir)) {
        Keyboard.press('t');
      }
      else {
        Keyboard.release('t');
      }
    }

    digitalWrite(OUTPUT_COL_0 + ic, LOW);
  }

  delay(8);
}
