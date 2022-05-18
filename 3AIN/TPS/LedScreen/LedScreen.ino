#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

const byte numbers[16] = {
                    0b11111100, // 0
                    0b01100000, // 1
                    0b11011010, // 2
                    0b11110010, // 3
                    0b01100110, // 4
                    0b10110110, // 5
                    0b10111110, // 6
                    0b11100000, // 7
                    0b11111110, // 8
                    0b11100110, // 9
                    0b11101110, // 10 A
                    0b00111110, // 11 B
                    0b10011100, // 12 C
                    0b01111010, // 13 D
                    0b10011110, // 14 E
                    0b10001110  // 15 F
};

void setup() {
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
  lcd.begin(16, 2);
  int  x = 15;
  lcd.print("X: ", x);
  lcd.setCursor(0,1);
  lcd.print("<3");
}

void loop() {
}
