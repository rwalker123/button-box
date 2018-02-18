
const int pinLed = LED_BUILTIN;

#define N_ELEMENTS(array) (sizeof(array)/sizeof((array)[0])) 

int pinButtons[] = { 2, 3 };
const int numPinButtons = N_ELEMENTS(pinButtons);

int pinAxes[] = { 0 };
const int numPinAxes = N_ELEMENTS(pinAxes);

#define NUM_BUTTONS 32

struct InputState {
  bool btns[NUM_BUTTONS];
  int axes[6];
  int dpad[2];  
} inputState = {};

const unsigned long uBufSize = sizeof(InputState);

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 2; i++) {
    pinMode(pinButtons[i], INPUT);
  }
  
  pinMode(pinLed, OUTPUT);

  // Start the Serial which is connected with the USB MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial.begin(115200);
}

void loop() {

  bool stateChanged = false;

  // buttons
  for (int i = 0; i < 2; i++) {
    bool buttonState = !digitalRead(pinButtons[i]);
    stateChanged |= (inputState.btns[i] != buttonState);
    inputState.btns[i] = buttonState;
  }

  // axes
  for (int t = 0; t < 1; t++) {
    //int newVal = analogRead(pinAxes[t]); //(float)analogRead(pinAxes[t]) / 1023.0 * (float)0xFFFF;
    //stateChanged |= (inputState.axes[t] != newVal);
    //inputState.axes[t] = newVal;
  }

  if (stateChanged) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.write((byte *)&inputState, uBufSize);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
