#include "Arduino.h"
#include "HID.h"
#include "Keyboard.h"

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};


void setup() {
  Keyboard.begin();
}

void loop() {
  Keyboard.print("t");
  delay(2000);
}
