#include "Arduino.h"
#include "HID.h"
#include "Keyboard.h"

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};


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
        Keyboard.print("t");
      }
    }

    digitalWrite(OUTPUT_COL_0 + ic, LOW);
  }

  delay(8);
}
