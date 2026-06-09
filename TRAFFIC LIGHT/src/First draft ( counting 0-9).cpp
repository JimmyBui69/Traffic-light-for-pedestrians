#include <Arduino.h>

const byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

// Segment order: A, B, C, D, E, F, G, DP
// Logic below assumes a common-cathode display.
const byte digitMap[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8
  {1, 1, 1, 1, 0, 1, 1, 0}, // 9
};

void showDigit(byte digit) {
  for (byte segment = 0; segment < 8; segment++) {
    digitalWrite(segmentPins[segment], digitMap[digit][segment]);
  }
}

void setup() {
  for (byte segment = 0; segment < 8; segment++) {
    pinMode(segmentPins[segment], OUTPUT);
  }
}

void loop() {
  for (byte digit = 0; digit < 10; digit++) {
    showDigit(digit);
    delay(1000);
  }
}
