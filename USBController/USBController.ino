#include <HID-Project.h>
#include <HID-Settings.h>

#include <HID.h>

/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Gamepad example
  Press a button and demonstrate Gamepad actions

  You can also use Gamepad1,2,3 and 4 as single report.
  This will use 1 endpoint for each gamepad.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Gamepad-API
*/

#include "HID-Project.h"

#define NUM_BUTTONS 32

struct InputState {
  bool btns[NUM_BUTTONS];
  int axes[6];
  // values: 0-8 (0==centered)
  int dpad[2];  
} inputState = {};
const unsigned long uBufSize = sizeof(InputState);

//const int pinLed = LED_BUILTIN;
//const int pinButton = 2;

void setup() {
  //pinMode(pinLed, OUTPUT);
  //pinMode(pinButton, INPUT_PULLUP);

  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();

  Serial.begin(115200);
}

void loop() {
  //if (Serial1.available() < uBufSize)
  //  return;

  size_t bytesRead = 0;
  if ((bytesRead = Serial1.readBytes((byte *)&inputState, uBufSize)) > 0) {

    if (bytesRead == uBufSize) {

      for(int i = 0; i < NUM_BUTTONS; i++) {
        (inputState.btns[i]) ? Gamepad.press(i+1) : Gamepad.release(i+1);
      }
      
      // Move x/y Axis to a new position (16bit)
      Gamepad.xAxis(inputState.axes[0]);
      Gamepad.yAxis(inputState.axes[1]);
      Gamepad.zAxis(inputState.axes[2]);
  
      Gamepad.rxAxis(inputState.axes[3]);
      Gamepad.ryAxis(inputState.axes[4]);
      Gamepad.rzAxis(inputState.axes[5]);
      
      // values: 0-8 (0==centered)
      Gamepad.dPad1(inputState.dpad[0]);
      Gamepad.dPad1(inputState.dpad[1]);
      
      // Functions above only set the values.
      // This writes the report to the host.
      Gamepad.write();
    } else {
      Serial.print("wrong bytes read: ");
      Serial.print(bytesRead);
      Serial.print(", needed: ");
      Serial.println(uBufSize);
    }
  }
  #if 0
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, LOW);

    // Press button 1-32
    static uint8_t count = 0;
    count++;
    if (count == 33) {
      Gamepad.releaseAll();
      count = 0;
    }
    else
      Gamepad.press(count);

    // Move x/y Axis to a new position (16bit)
    Gamepad.xAxis(random(0xFFFF));
    Gamepad.yAxis(random(0xFFFF));
    Gamepad.zAxis(random(0xFFFF));

    Gamepad.rxAxis(random(0xFFFF));
    Gamepad.ryAxis(random(0xFFFF));
    Gamepad.rzAxis(random(0xFFFF));

    // Go through all dPad positions
    // values: 0-8 (0==centered)
    static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad1(dpad1++);
    if (dpad1 > GAMEPAD_DPAD_UP_LEFT)
      dpad1 = GAMEPAD_DPAD_CENTERED;

    static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad2(dpad2--);
    if (dpad2 < GAMEPAD_DPAD_CENTERED)
      dpad2 = GAMEPAD_DPAD_UP_LEFT;

    // Functions above only set the values.
    // This writes the report to the host.
    Gamepad.write();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, HIGH);
  }
  #endif
}
