#include<DHT.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

#define DHT22PIN 14
#define DHT22TYPE DHT22
#define DHT11PIN 12
#define DHT11TYPE DHT11


#define CIRCLE 0
#define DEGREE 1
#define BACKSLASH 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht22(DHT22PIN, DHT22TYPE);
DHT dht11(DHT11PIN, DHT11TYPE);

float t11, h11, t22, h22;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  dht22.begin();
  dht11.begin();

  byte circle[8] = {14, 10, 14, 0,0,0,0,0};
  byte degree[8] = {4, 10, 4, 0,0,0,0,0};
  byte backslash[8] = {0, 16, 8, 4,2,1,0,0};
  lcd.createChar(CIRCLE, circle);
  lcd.createChar(DEGREE, degree);
  lcd.createChar(BACKSLASH, backslash);
  lcd.cursor();
}

void loop() {
  loaderScreen();
  h22 = dht22.readHumidity();
  t22 = dht22.readTemperature(false);

  h11 = dht11.readHumidity();
  t11 = dht11.readTemperature(false);
  delay(500);
  clearScreen();
  lcd.setCursor(0, 0);
  lcd.print("11T" + String(t11));
  lcd.write(byte(DEGREE));
  lcd.print("CH"+ String(h11));
  lcd.setCursor(0, 1);
  lcd.print("22T" + String(t22));
  lcd.write(byte(DEGREE));
  lcd.print("CH: "+ String(h22));

  turnCursor(3000);
}

void loaderScreen() {
  lcd.setCursor(0, 0);
  lcd.print("----------------");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
}

void clearScreen() {
  lcd.clear();
}

const int step = 100; //ms
void turnCursor(int delayTime){
  int time = 0;
  int frame = 0;
  
  
  while(time < delayTime) {
    lcd.setCursor(15, 1);
    writeFrame(frame);
    time += step;
    frame = (frame + 1)%4;
    delay(step);
  }
}

const char frames[3] = {'|', '/', '-'};
void writeFrame(int frame){
  switch(frame){
    case 3: lcd.write(byte(BACKSLASH)); break;
    default: lcd.print(frames[frame]); break;
  }
}
