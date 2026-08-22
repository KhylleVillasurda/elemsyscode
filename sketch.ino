// 7-segment pins
//             A  B  C  D  E  F  G
const int segPins[] = {2, 3, 4, 5, 6, 7, 8};

// Binary LED pins
// LED1 = bit 0 (LSB)
// LED4 = bit 3 (MSB)
const int ledPins[] = {9, 10, 11, 12};

// 7-segment patterns for hexadecimal 0-F
// Order: A B C D E F G
const byte hexPatterns[16][7] = {
  // A  B  C  D  E  F  G
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

void setup() {

  // Set 7-segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  // Set binary LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
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
