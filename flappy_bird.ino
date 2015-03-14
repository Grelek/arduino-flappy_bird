#include <LiquidCrystal.h>

#define LED_PIN 13
#define LCD_RS_PIN 16
#define LCD_ENABLE_PIN 17
#define LCD_D04_PIN 23
#define LCD_D05_PIN 25
#define LCD_D06_PIN 27
#define LCD_D07_PIN 29
#define BTN_PIN 41
#define BEEP_PIN 37

LiquidCrystal lcd(
  LCD_RS_PIN,
  LCD_ENABLE_PIN,
  LCD_D04_PIN,
  LCD_D05_PIN,
  LCD_D06_PIN,
  LCD_D07_PIN
);

int holePosY;
int holePosX;
int playerPosY;
int playerPosX;
int score = 0;
bool isGameOver = false;

void beep() {
  digitalWrite(BEEP_PIN, HIGH);
  delay(50);
  digitalWrite(BEEP_PIN, LOW);
}

void setup() {  
  // Init display
  lcd.begin(20, 4);
  
  // Indicate that NEW program is running
  beep();
  
  // Activate button
  digitalWrite(BTN_PIN, HIGH);
  
  // Setup random seed
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  holePosY = random(0, 4);
  holePosX = 16;
  playerPosY = 1;
  playerPosX = 1;
}

int lastTime = 0;
void loop() {
  if (millis() - lastTime >= 900 && !isGameOver) {
    if (digitalRead(BTN_PIN)) {
      if (playerPosY + 1 < 4) {
        playerPosY++;
      }
    } else {
      if (playerPosY - 1 >= 0) {
        playerPosY--;
      }
    }
    
    lastTime = millis();
  }
  
  if (millis() % 250 == 0 && !isGameOver) {
    if (playerPosY != holePosY && playerPosX == holePosX) {
      isGameOver = true;
      return;
    }
    
    lcd.clear();
    
    if (holePosX == 0) {
      holePosY = random(0, 4);
      holePosX = 16;
      score++;
      beep();
    }
    
    for (int i = 0; i < 4; i++) {
      lcd.setCursor(holePosX, i);
      if (i == holePosY) {
        lcd.write(" ");
      } else {
        lcd.write("X");
      }
    }
    
    holePosX--;
    
    lcd.setCursor(playerPosX, playerPosY);
    lcd.write("P");
    
    lcd.setCursor(19, 3);
    lcd.rightToLeft();
    lcd.print(score);
  }
  
  if (isGameOver) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("YOU LOST!");
    lcd.setCursor(0, 2);
    lcd.print("Your score: ");
    lcd.setCursor(0, 3);
    lcd.print(score);
    lastTime = millis();
    delay(10000);
  }
}
