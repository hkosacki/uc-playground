/*
*  LCM1602 & Arduino Uno
*  VCC - > 5 V
*  GND - GND
*  SCL -> A5
*  SDA -> A4
*/
 
#include <Wire.h>   // standardowa biblioteka Arduino
#include <DHT.h>   
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

#define DHTPIN 1
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Ustawienie adresu ukladu na 0x27
 
 
void setup()  
{
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  dht.begin();
  
  lcd.begin(16,2);   // Inicjalizacja LCD 2x16
//  lcd.init();
  lcd.backlight(); // zalaczenie podwietlenia 
//  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
//  lcd.print("Hello, world!");
//  delay(500);
//  lcd.setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
//  lcd.print("BOTLAND.com.pl");
 
}
 
void loop() 
{
   lcd.setCursor(0,0);
   lcd.print("Loading data...");
   delay(1000);
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   clearRow(lcd, 0);
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  clearRow(lcd, 1);
  lcd.setCursor(0,1);
 
  if (isnan(t) || isnan(h)) {
    lcd.print("Read error");
  } else {
    lcd.print("T:");
    lcd.print(t);
    lcd.print("*C,H:");
    lcd.print(h);
  }
  delay(5000);
}


void clearRow(LiquidCrystal_I2C lcd, int lineRow) {
    lcd.setCursor(0, lineRow);
    lcd.print("               ");
}
