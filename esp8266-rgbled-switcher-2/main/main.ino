#include<Wire.h>
#include "Color.h"
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

#define LED_R 14
#define LED_G 12
#define LED_B 13

#define LED_ERROR 2

#define BUTTON_R 4
#define BUTTON_G 5
#define BUTTON_B 16
#define BUTTON_ERR 0

int STATE_R = 1;
int STATE_G = 1;
int STATE_B = 1;

Color R(BUTTON_R, LED_R, STATE_R);
Color G(BUTTON_G, LED_G, STATE_G);
Color B(BUTTON_B, LED_B, STATE_B);

String ssid = "home";
String wifipass = "Nowogrod74";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_R, INPUT);
  pinMode(BUTTON_G, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_ERR, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);

  
  // wifi and server stuff
  WiFi.begin(ssid, wifipass);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Wifi connected!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/switch", handleSwitch);
  server.onNotFound(handle404);
  server.begin();
  reportError();
  Serial.println("Started!");
}

void loop() {
  handleColor(R, "r");
  handleColor(G, "g");
  handleColor(B, "b");
  handleErrorButton();
  server.handleClient();
}

int newButtonState = 0;
void handleColor(Color &color, String colorString) {
  int newButtonState = digitalRead(color.buttonPin);
  if(newButtonState != color.buttonState){
    Serial.println("new button state " + colorString);
    color.setButtonState(newButtonState);
    if(color.buttonState == 1) {
      Serial.println("new button state: 1 " + colorString);
      color.switchState();
    }
  }
  delay(10);
}

void reportError(){
  int i;
  for(i = 0; i < 3; i++){
    digitalWrite(LED_ERROR, HIGH);
    delay(200);
    digitalWrite(LED_ERROR, LOW);
    delay(200);
  }
}

void handle404(){
  server.send(404, "text/html", "404 - not found");
  reportError();
}

void handleSwitch() {
  String param = server.arg("color");
  Serial.println("Param = " + param);
  if(param == "R") switchAndReply(R);
  else if(param == "G") switchAndReply(G);
  else if(param == "B") switchAndReply(B);
  else {
    server.send(400, "text/html", "bad request");
    reportError();
  }

}

void switchAndReply(Color &color){
  color.switchState();
  server.send(200, "text/html", "done!");
}

int errButtonState = 0;
void handleErrorButton(){
  int newButtonState = digitalRead(BUTTON_ERR);
  if(errButtonState != newButtonState) {
     errButtonState = newButtonState;
     if(errButtonState == 1) {
      reportError();
     }
  }
  delay(10);
}
