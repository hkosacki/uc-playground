#include<DHT.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DHTPIN 14
#define DHTTYPE DHT22
#define BUTTONPIN 16

#define CIRCLE 0
#define DEGREE 1
#define BACKSLASH 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

float temperature, humidity;
bool backlight = true;

String ssid = "home";
String wifipass = "Nowogrod74";

ESP8266WebServer server(80);

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

  // wifi and server stuff
  WiFi.begin(ssid, wifipass);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Wifi connected!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handleRootRequest);
  server.onNotFound(handle404);
  server.begin();

  pinMode(BUTTONPIN, INPUT);
}

int counter = 0;

void loop() {
  if((counter+2) %4 ==0){//1
    humidity = dht.readHumidity();
    temperature = dht.readTemperature(false);
  }
  if(counter%4 ==0){//2
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temperature));
    lcd.write(byte(DEGREE));
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP().toString() + "/"); 
  }
  //3
  server.handleClient();
  handleButton();

  counter++;
}

void clearScreen() {
  lcd.clear();
}

void handleRootRequest(){
  server.send(200, "text/html", String(temperature));
}

void handle404(){
  server.send(404, "text/html", "404 - not found");
}

int bState = 0;
void handleButton() {
  int newState = digitalRead(BUTTONPIN);
  if (bState != newState) {
    bState = newState;
    if(bState){
      switchBacklight();
    }
  }
}

void switchBacklight(){
  backlight = !backlight;
  if(backlight) {
      lcd.backlight();
    } else {
      lcd.noBacklight();
    }
}
