#include <Arduino.h>
// ======================
// SEVEN SEGMENT
// ======================

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

// ======================
// TRAFFIC LIGHT
// ======================

const int GREEN_LED  = 10;
const int YELLOW_LED = 11;
const int RED_LED    = 12;

// ======================
// BUTTON
// ======================

const int BUTTON_PIN = A0;

// true = pha đỏ
// false = pha xanh
bool redPhase = false;

// ======================
// HIỂN THỊ 1 CHỮ SỐ
// ======================

void showDigit(byte digit)
{
  for (byte i = 0; i < 8; i++)
  {
    // Common Cathode
    digitalWrite(segmentPins[i], digitMap[digit][i]);

    // Nếu dùng Common Anode thì thay bằng:
    // digitalWrite(segmentPins[i], !digitMap[digit][i]);
  }
}

// ======================
// NGƯỜI ĐI BỘ QUA ĐƯỜNG
// ======================

void pedestrianMode()
{
  Serial.println("PEDESTRIAN CROSSING");

  // Vàng cảnh báo 2 giây
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

  showDigit(2);
  delay(1000);

  showDigit(1);
  delay(1000);

  // Đỏ
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // Đếm ngược 5 -> 0
  for (int i = 5; i >= 0; i--)
  {
    showDigit(i);
    delay(1000);
  }
}

// ======================
// SETUP
// ======================

void setup()
{
  for (byte i = 0; i < 8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("START");
}

// ======================
// LOOP
// ======================

void loop()
{
    for (byte digit = 0; digit < 10; digit++)
    {
      showDigit(digit);
		
      if (redPhase)
      {
        // 0 -> 7 : Đỏ
        if (digit <= 7)
        {
          digitalWrite(RED_LED, HIGH);
          digitalWrite(YELLOW_LED, LOW);
          digitalWrite(GREEN_LED, LOW);
        }
        // 8 -> 9 : Vàng
        else
        {
          digitalWrite(RED_LED, LOW);
          digitalWrite(YELLOW_LED, HIGH);
          digitalWrite(GREEN_LED, LOW);
        }
      }
      else
      {
        

        // 0 -> 7 : Xanh
        if (digit <= 7)
        {
          digitalWrite(RED_LED, LOW);
          digitalWrite(YELLOW_LED, LOW);
          digitalWrite(GREEN_LED, HIGH);
        }
        // 8 -> 9 : Vàng
        else
        {
          digitalWrite(RED_LED, LOW);
          digitalWrite(YELLOW_LED, HIGH);
          digitalWrite(GREEN_LED, LOW);
        }
        if (digitalRead(BUTTON_PIN) == HIGH)
        {
          pedestrianMode();
          redPhase = false;

          while (digitalRead(BUTTON_PIN) == HIGH)
          {
            delay(10);
          }

          return;
        }
      }

      delay(1000);
    }

    // đổi pha
    redPhase = !redPhase;
  
}