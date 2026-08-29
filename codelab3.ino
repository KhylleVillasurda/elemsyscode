// const byte ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
// const byte NUM_LEDS = 9;
// const byte buttonPin = 12;
 
// const unsigned long DEBOUNCE_DELAY = 50;   // ms - stops accidental double-presses
// const unsigned long STEP_DELAY = 100;      // ms - the 100ms delay your professor asked for
 
// int mode = 1;
// bool lastRawState = HIGH;      // tracks the raw, possibly-noisy reading
// bool stableButtonState = HIGH; // tracks the confirmed, debounced state
// unsigned long lastDebounceTime = 0;
// int step = 0; // tracks which LED/frame we're currently on
 
// // Sequence used by mode 4 (bounce)
// const int bounceSequence[] = {0, 8, 1, 7, 2, 6, 3, 5, 4, 3, 5, 2, 6, 1, 7, 0, 8};
// const byte bounceLength = 17;
 
// void setup() {
//   pinMode(buttonPin, INPUT_PULLUP);
//   for (int i = 0; i < NUM_LEDS; i++) {
//     pinMode(ledPins[i], OUTPUT);
//   }
//   randomSeed(analogRead(A0)); // makes mode 5 more random each run
// }
 
// void loop() {
//   checkButton();      // read the button FIRST, before the delay
//   runPattern();        // update the LEDs for the current mode
//   delay(STEP_DELAY);   // the actual 100ms delay, applied once per loop
// }
 
// // ---- Button handling ----
// void checkButton() {
//   bool reading = digitalRead(buttonPin);
 
//   if (reading != lastRawState) {
//     lastDebounceTime = millis(); // reset the debounce timer whenever the raw reading flickers
//   }
 
//   if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
//     // reading has been stable for long enough - safe to trust it now
//     if (reading != stableButtonState) {
//       stableButtonState = reading; // commit the new stable state
//       if (stableButtonState == LOW) {
//         // this only runs once per confirmed press, not once per loop
//         mode++;
//         if (mode > 5) mode = 1;
//         step = 0;   // restart animation cleanly on mode change
//         allOff();
//       }
//     }
//   }
//   lastRawState = reading;
// }
 
// void allOff() {
//   for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], LOW);
// }
 
// // ---- Pattern handling ----
// void runPattern() {
//   switch (mode) {
//     case 1: modeChase();  break;
//     case 2: modeEven();   break;
//     case 3: modeOdd();    break;
//     case 4: modeBounce(); break;
//     case 5: modeRandom(); break;
//   }
// }
 
// void modeChase() {
//   allOff();
//   digitalWrite(ledPins[step], HIGH);
//   step++;
//   if (step >= NUM_LEDS) step = 0;
// }
 
// void modeEven() {
//   for (int i = 0; i < NUM_LEDS; i++) {
//     digitalWrite(ledPins[i], (i % 2 == 0) ? HIGH : LOW);
//   }
// }
 
// void modeOdd() {
//   for (int i = 0; i < NUM_LEDS; i++) {
//     digitalWrite(ledPins[i], (i % 2 != 0) ? HIGH : LOW);
//   }
// }
 
// void modeBounce() {
//   allOff();
//   digitalWrite(ledPins[bounceSequence[step]], HIGH);
//   step++;
//   if (step >= bounceLength) step = 0;
// }
 
// void modeRandom() {
//   for (int i = 0; i < NUM_LEDS; i++) {
//     digitalWrite(ledPins[i], random(2) ? HIGH : LOW);
//   }
// }

const byte ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
const byte numLEDs = 9;
const byte buttonPin = 12;

int currentMode = 1;
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long previousMillis = 0;
int animStep = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Read button with debouncing
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      // Detect button press (falling edge because of INPUT_PULLUP)
      if (buttonState == LOW) {
        currentMode++;
        if (currentMode > 5) {
          currentMode = 1; // 6th click reverts to 1st mode
        }
        animStep = 0; // Reset animation step on mode change
      }
    }
  }
  lastButtonState = reading;

  // Execute pattern based on active mode
  unsigned long currentMillis = millis();

  switch (currentMode) {
    case 1: // Mode 1: Left to right chase
      if (currentMillis - previousMillis >= 150) {
        previousMillis = currentMillis;
        for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], (i == animStep) ? HIGH : LOW);
        }
        animStep = (animStep + 1) % numLEDs;
      }
      break;

    case 2: // Mode 2: All even-positioned LEDs ON
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], (i % 2 == 0) ? HIGH : LOW);
      }
      break;

    case 3: // Mode 3: All odd-positioned LEDs ON
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], (i % 2 != 0) ? HIGH : LOW);
      }
      break;

    case 4: // Mode 4: Outer-to-inner then inner-to-outer bounce
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
        for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], LOW);
        }
        int targetPair = animStep <= 4 ? animStep : (8 - animStep);
        digitalWrite(ledPins[targetPair], HIGH);
        if (targetPair != 4) {
          digitalWrite(ledPins[8 - targetPair], HIGH);
        }
        animStep = (animStep + 1) % 9;
      }
      break;

    case 5: // Mode 5: Randomized pattern
      if (currentMillis - previousMillis >= 250) {
        previousMillis = currentMillis;
        for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], random(2) ? HIGH : LOW);
        }
      }
      break;
  }
}
