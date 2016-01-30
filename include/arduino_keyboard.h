/*
  Keyboard.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef KEYBOARD_h
#define KEYBOARD_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Keyboard

#define KEY_LEFT_CTRL     0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT      0x82
#define KEY_LEFT_GUI      0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT     0x86
#define KEY_RIGHT_GUI     0x87

#define KEY_UP_ARROW      0xda
#define KEY_DOWN_ARROW    0xd9
#define KEY_LEFT_ARROW    0xd8
#define KEY_RIGHT_ARROW   0xd7
#define KEY_BACKSPACE     0xb2
#define KEY_TAB           0xb3
#define KEY_RETURN        0xb0
#define KEY_ESC           0x29
#define KEY_INSERT        0xd1
#define KEY_DELETE        0xd4
#define KEY_PAGE_UP       0x4b
#define KEY_PAGE_DOWN     0x4e
#define KEY_HOME          0xd2
#define KEY_END           0xd5
#define KEY_CAPS_LOCK     0xc1
#define KEY_F1            0xc2
#define KEY_F2            0xc3
#define KEY_F3            0xc4
#define KEY_F4            0xc5
#define KEY_F5            0xc6
#define KEY_F6            0xc7
#define KEY_F7            0xc8
#define KEY_F8            0xc9
#define KEY_F9            0xca
#define KEY_F10           0xcb
#define KEY_F11           0xcc
#define KEY_F12           0xcd

//  Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class Keyboard_ : public Print
{
private:
  KeyReport _keyReport;
public:
  void sendReport(KeyReport* keys);
  Keyboard_(void);
  void begin(void);
  void end(void);
  size_t write(uint8_t k);
  size_t press(uint8_t k);
  size_t release(uint8_t k);
  void releaseAll(void);
};
extern Keyboard_ Keyboard;

#endif
#endif
