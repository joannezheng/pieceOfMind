

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;
unsigned long time;
unsigned long countdown;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  accelemeter.init();
  lcd.setBacklight(WHITE);
  lcd.print("Hello");
  delay(1000);
  lcd.clear();

  // Take in User ID
  int id = 0;
  uint8_t buttons = lcd.readButtons();
  while (!buttons) {
    lcd.setCursor(0, 0);
    lcd.print("User ID: ");
    lcd.setCursor(0, 1);
    lcd.print(id);
    buttons = lcd.readButtons();
    //Serial.print(0);
    if (buttons & BUTTON_UP) {
      lcd.setCursor(0, 1);
      id = id + 1;
      lcd.print(id);

    }
    if (buttons & BUTTON_DOWN) {
      lcd.setCursor(0, 1);
      id = id - 1;
      lcd.print(id);
    }
    if (id < 0) {
      lcd.setCursor(0, 1);
      lcd.print("Wrong #!");
      delay(50);
    }
    if (buttons & BUTTON_SELECT) {
      break;
    }
    buttons = 0;
    delay(50);
    lcd.clear();
  }
  Serial.print(id);
  Serial.print(" ");
  lcd.clear();
  lcd.print("Symptom Check");
  delay(1500);
  lcd.clear();
}

uint8_t i = 0;
int count = -1;
int status = 0;
int symp = 0;
int sev = 0;
int DELAY_QUESTION = 1500;
int DELAY_BETWEEN = 1000;
int score = 0;

void loop() {

  if (status == 0) {
    lcd.setCursor(0, 0);
    lcd.print("1=L 2=U 3=R 4=D");
    lcd.setCursor(0, 1);
    lcd.print("NO=SELECT");
    checkPress();
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Headache?");
    symptomCheck();
  }
  if (status == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Pressure in head?");
    symptomCheck();
  }
  if (status == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Neck pain?");
    symptomCheck();
  }
  if (status == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Nausea/Vomiting?");
    symptomCheck();
  }
  if (status == 4) {
    lcd.setCursor(0, 0);
    lcd.print("Dizziness?");
    symptomCheck();
  }
//  if (status == 5) {
//    lcd.setCursor(0, 0);
//    lcd.print("Blurred vision? ");
//    symptomCheck();
//  }
  if (status == 5) {
    lcd.clear();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("# symptoms: ");
    lcd.print(symp);
    lcd.print("/22");
    lcd.setCursor(0, 1);
    lcd.print("Severity: ");
    lcd.print(sev);
    lcd.print("/88");
    checkPress();
    delay(500);
    status = status + 1;
  }
  // Cognitive Assessment
  if (status == 6) {
    lcd.setCursor(0, 0);
    uint8_t buttons = lcd.readButtons();
    int score = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    
    // Question 1
    lcd.print("Cognitive test");
    delay(1500);
    lcd.clear();
    lcd.print("What month?");
    delay(DELAY_QUESTION);
    lcd.setCursor(0, 1);
    lcd.print("Y=UP, N=DOWN");
    score = response(score);
    delay(DELAY_BETWEEN);
    lcd.clear();
    status = status + 1;
  }
  if (status == 7) {
    lcd.print("What's the date?");
    delay(DELAY_QUESTION);
    lcd.setCursor(0, 1);
    lcd.print("Y=UP, N=DOWN");
    score = response(score);
    delay(DELAY_BETWEEN);
    lcd.clear();
    status = status + 1;
  }
  if (status == 8) {
    lcd.print("Day of the week?");
    delay(DELAY_QUESTION);
    lcd.setCursor(0, 1);
    lcd.print("Y=UP, N=DOWN");
    score = response(score);
    delay(DELAY_BETWEEN);
    lcd.clear();
    status = status + 1;
  }
  if (status == 9) {
    lcd.print("What year?");
    delay(DELAY_QUESTION);
    lcd.setCursor(0, 1);
    lcd.print("Y=UP, N=DOWN");
    score = response(score);
    delay(DELAY_BETWEEN);
    lcd.clear();
    status = status + 1;
  }
  if (status == 10) {
    lcd.print("What time (hr)?");
    delay(DELAY_QUESTION);
    lcd.setCursor(0, 1);
    lcd.print("Y=UP, N=DOWN");
    score = response(score);
    delay(DELAY_BETWEEN);
    lcd.clear();
    status = status + 1;
  }
   if (status == 11) {
      String wordList[] = {"elbow", "apple", "carpet", "saddle", "bubble"};
      lcd.setCursor(0, 0);
      lcd.print("Read the next");
      lcd.setCursor(0, 1);
      lcd.print("five words");
      delay(DELAY_QUESTION);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press any key");
      lcd.setCursor(0, 1);
      lcd.print("to advance");
      checkPress();
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      for (int i = 0; i <= 4; i++) {
        lcd.print(wordList[i]);
        checkPress();
        lcd.clear();
        delay(300);
      }
  // }

      delay(500);
      lcd.print("Please mark if");
      lcd.setCursor(0, 1);
      lcd.print("word remembered");
      lcd.setCursor(0, 0);
      delay(DELAY_QUESTION);
      lcd.clear();

      for (int i = 0; i <= 4; i++) {
        lcd.setCursor(0, 0);
        lcd.print(wordList[i]);
        delay(200);
        lcd.setCursor(0, 1);
        lcd.print("Y=UP, N=DOWN");
        score = response(score);
        delay(DELAY_BETWEEN);
        lcd.clear();
      }
      status = status + 1;
    }

    /*
    if (status == 13) {
      lcd.setCursor(0, 0);
      lcd.print("Read digits");
      delay(DELAY_QUESTION);
      lcd.clear();
      lcd.print("Response must be");
      lcd.setCursor(0, 1);
      lcd.print("backwards");
      delay(DELAY_QUESTION);
      lcd.clear();
      lcd.setCursor(0, 0);

      for (int i = 0; i <= 3; i++) {
        String digitList[] = {"4 9 3", "3 8 1 4", "6 2 9 7 1", "7 1 8 4 6 2"};
        lcd.setCursor(0, 0);
        lcd.print(digitList[i]);
        delay(200);
        lcd.setCursor(0, 1);
        lcd.print("Y=UP, N=DOWN");
        score = response(score);
        delay(DELAY_BETWEEN);
        lcd.clear();
        status = status + 1;
      }
      if (status == 14) {
        lcd.setCursor(0, 0);
        lcd.print("Ask for months");
        lcd.setCursor(0, 1);
        lcd.print("backwards");
        delay(DELAY_QUESTION);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Y=UP, N=DOWN");
        score = response(score);
        delay(10);
        lcd.clear();
        status = status + 1;
      }
      if (status == 15) {
        String wordList[] = {"elbow", "apple", "carpet", "saddle", "bubble"};
        lcd.setCursor(0, 0);
        lcd.print("Please mark if");
        lcd.setCursor(0, 1);
        lcd.print("word remembered");
        lcd.setCursor(0, 0);
        delay(DELAY_QUESTION);
        lcd.clear();

        for (int i = 0; i <= 4; i++) {
          lcd.setCursor(0, 0);
          lcd.print(wordList[i]);
          delay(200);
          lcd.setCursor(0, 1);
          lcd.print("Y=UP, N=DOWN");
          score = response(score);
          delay(DELAY_BETWEEN);
          lcd.clear();
        }

        lcd.setCursor(0, 0);
        lcd.print("score = ");
        lcd.print(score);
        lcd.setCursor(0, 1);
        lcd.print("Thank you!");

      }
    }*/
  if (status == 12) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tilt test 1: ");
    checkPress();
    delay(500);
    time = millis();
    tilt();
    Serial.println();
  }
}




void symptomCheck() {
  uint8_t buttons = lcd.readButtons();
  while (!buttons) {
    buttons = lcd.readButtons();
  }
  lcd.setCursor(0, 1);
  if (buttons & BUTTON_LEFT) {
    lcd.print("Severity: 1");
    delay(1000);
    symp = symp + 1;
    sev = sev + 1;
    Serial.print("1 ");
  }
  if (buttons & BUTTON_UP) {
    lcd.print("Severity: 2");
    delay(1000);
    symp = symp + 1;
    sev = sev + 2;
    Serial.print("2 ");
  }
  if (buttons & BUTTON_RIGHT) {
    lcd.print("Severity: 3");
    delay(1000);
    symp = symp + 1;
    sev = sev + 3;
    Serial.print("3 ");
  }
  if (buttons & BUTTON_DOWN) {
    lcd.print("Severity: 4");
    delay(1000);
    symp = symp + 1;
    sev = sev + 4;
    Serial.print("4 ");
  }
  if (buttons & BUTTON_SELECT) {
    lcd.print("No");
    Serial.print("0 ");
    delay(1000);
  }
  status = status + 1;
  lcd.clear();
}


void tilt() {
  int8_t x;
  int8_t y;
  int8_t z;
  int8_t xf;
  int8_t yf;
  int8_t zf;
  float ax, ay, az;
  float axf, ayf, azf;
  countdown = millis();
  while (millis() - countdown < 5000) {
    int second = 5 - (millis() - countdown) / 1000;
    lcd.print(second);
  }
  lcd.clear();
  while (1) {
    accelemeter.getXYZ(&x, &y, &z);
    accelemeter.getAcceleration(&ax, &ay, &az);
    delay(100);
    accelemeter.getXYZ(&xf, &yf, &zf);
    accelemeter.getAcceleration(&axf, &ayf, &azf);
    if (abs(axf - ax) >= 0.1 || abs(ayf - ay) >= 0.1 || abs(azf - az) >= 0.1) {
      lcd.setBacklight(RED);
      delay(100);
      lcd.setBacklight(WHITE);
      count = count + 1;
    }
    if (millis() - time > 20000) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Total: ");
      lcd.print(count);
      delay(3000);
      break;
    }
  }
  lcd.clear();

  Serial.print(count);
  Serial.print(" ");

  int open = 0;

  uint8_t buttons = lcd.readButtons();
  while (!buttons) {
    lcd.setCursor(0, 0);
    lcd.print("# of open eyes: ");
    lcd.setCursor(0, 1);
    lcd.print(open);
    buttons = lcd.readButtons();
    //Serial.print(0);
    if (buttons & BUTTON_UP) {
      lcd.setCursor(0, 1);
      open = open + 1;
      lcd.print(open);

    }
    if (buttons & BUTTON_DOWN) {
      lcd.setCursor(0, 1);
      open = open - 1;
      lcd.print(open);
    }
    if (open < 0) {
      lcd.setCursor(0, 1);
      lcd.print("Wrong #!");
      delay(50);
    }
    if (buttons & BUTTON_SELECT) {
      break;
    }
    buttons = 0;
    delay(50);
    lcd.clear();
  }
  Serial.print(open);
  count = count + open;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total count: ");
  lcd.print(count);
  delay(4000);
  status = status + 1;
  lcd.clear();
  lcd.print("Thank you!");
}

int response (int tempscore) {
  uint8_t buttons = lcd.readButtons();
  while (buttons == 0) {
    lcd.setCursor(0, 0);
    buttons = lcd.readButtons();
    if (buttons & BUTTON_UP) {
      lcd.clear();
      lcd.print("Correct!");
      tempscore += 1;
      Serial.print("1 ");
    }
    else if (buttons & BUTTON_DOWN) {
      lcd.clear();
      lcd.print("Incorrect.");
      Serial.print("0 ");
    }
  }
  return tempscore;
}

int checkPress() {
  uint8_t buttons = lcd.readButtons();
  while (buttons == 0) {
    buttons = lcd.readButtons();
    if (buttons) {
      return 0;
    }
  }
}


