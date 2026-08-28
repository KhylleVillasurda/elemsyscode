// NAME: KHYLLE P. VILLASURDA
// BSIT - 4
// SAT 7:30 - 1:30
// Wiring Color Coded
// Green = A, B
// Brown = C, D, E
// Yellow = F, G

// Instead of having to set them one by one, I decided to put them on a array.
const int segPins [] = {2, 3, 4, 5, 6, 7, 8};
const int ledPins [] = {9, 10, 11, 12};

const byte hexPatterns[16][7] = {
// A, B, C, D, E, F, G
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
  {1, 1, 1, 0, 1, 1, 1}, // A
  {0, 0, 1, 1, 1, 1, 1}, // b
  {1, 0, 0, 1, 1, 1, 0}, // C
  {0, 1, 1, 1, 1, 0, 1}, // d
  {1, 0, 0, 1, 1, 1, 1}, // E
  {1, 0, 0, 0, 1, 1, 1}  // F
};

// Regarding the type of 7 segment you have:
// If Common Anode, connecting the COM Pin to the 5V and setting the digitalWrite to LOW makes it light up.
// While Common Cathode connecting the COM Pin to the GND and setting the digitalWrite to HIGH turns on the LED.

void setup() {
  // Looping each segPins to set its pinMode to output.
for (int i = 0; i < 7; i++) {
  pinMode(segPins[i], OUTPUT);

// digitalWrite(segPins[i], HIGH);
}

for (int i = 0; i < 4; i++) {
  pinMode(ledPins[i], OUTPUT);

// digitalWrite(ledPins[i], HIGH);
}

}

void displayHex(int number) {

  // Display the hexadecimal character
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], hexPatterns[number][i]);
  }

  // Display the binary value
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], bitRead(number, i));
  }
}

void loop() {

  // Count from 0 to 15
  for (int number = 0; number < 16; number++) {

    displayHex(number);

    delay(1000);
  }
}

// These are the expected results

// 0 = 0 0 0 0
// 1 = 0 0 0 1
// 2 = 0 0 1 0
// 3 = 0 0 1 1
// 4 = 0 1 0 0
// 5 = 0 1 0 1
// 6 = 0 1 1 0
// 7 = 0 1 1 1
// 8 = 1 0 0 0
// 9 = 1 0 0 1
// 10 (A) = 1 0 1 0
// 11 (b) = 1 0 1 1
// 12 (C) = 1 1 0 0
// 13 (d) = 1 1 0 1
// 14 (E) = 1 1 1 0
// 15 (F) = 1 1 1 1
