#include<DHT.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

#define DHTPIN 14
#define DHTTYPE DHT22

#define CIRCLE 0
#define DEGREE 1
#define BACKSLASH 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

float temperature, humidity;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  dht.begin();

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
  humidity = dht.readHumidity();
  temperature = dht.readTemperature(false);
  delay(500);
  clearScreen();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temperature));
  lcd.write(byte(DEGREE));
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity " + String(humidity) + "%"); 

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
