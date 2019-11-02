#include <HTTP_Method.h>
#include <WebServer.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "FS.h"
#include "SPIFFS.h"

#include "src/Configuration.h"
#include "src/Bootstrapper.cpp"

WebServer server(80);

int direction = HIGH;
int speed = 100;
bool drive = false;

void setup() {

  Bootstrapper::waitForSerial();
  Bootstrapper::initializePins();
  Bootstrapper::setupWifi();

  Serial.println("helloooo");

  server.on("/", handleRoot);
  server.on("/index.js", handleJs);
  server.on("/forward", goForward);
  server.on("/backwards", goBackwards);
  server.on("/halt", halt);
  
  server.begin();
}

void halt() {
  drive = false;
}

void goForward() {
  Serial.println("Going forward");
  direction = HIGH;
  server.send(200);
}

void goBackwards() {
  Serial.println("Going backwards");
  direction = LOW;
  server.send(200);
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", FILE_READ);

  if(!file){
    server.send(404);
    return;
  }

  server.streamFile(file, "text/plain");
  file.close();
}

void handleJs() {
  File file = SPIFFS.open("/test.js", FILE_READ);

  if(!file){
    server.send(404);
    return;
  }

  server.streamFile(file, "text/javascript");
  file.close();
}

void loop() {
  server.handleClient();

  if (!drive) {
    direction = HIGH;
    speed = 255;
    return;
  }

  digitalWrite(FL1,direction);
  ledcWrite(pwmChannel, speed);

  digitalWrite(FR1,direction);
  ledcWrite(pwmChannel, speed);

  digitalWrite(BL1,direction);
  ledcWrite(pwmChannel, speed);

  digitalWrite(BR1,direction);
  ledcWrite(pwmChannel, speed);
}