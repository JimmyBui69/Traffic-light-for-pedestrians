#include <Arduino.h>
const byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

const byte digitMap[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}  // 9
};

bool redPhase = true;

void showDigit(byte digit) {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], digitMap[digit][i]);
  }
}

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(10, OUTPUT); // xanh
  pinMode(11, OUTPUT); // vàng
  pinMode(12, OUTPUT); // đỏ
}

void loop() {

  for (byte digit = 0; digit < 10; digit++) {

    showDigit(digit);

    if (redPhase) {

   
        digitalWrite(12, HIGH); // đỏ
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
      

    } else {

      if (digit <= 7) {
        digitalWrite(10, HIGH); // xanh
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
      }
      else {
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH); // vàng
        digitalWrite(12, LOW);
      }

    }

    delay(1000);
  }

  redPhase = !redPhase; // đổi pha sau mỗi chu kỳ 0-9
}
