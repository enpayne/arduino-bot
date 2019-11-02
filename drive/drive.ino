#include <HTTP_Method.h>
#include <WebServer.h>

#include <ESPmDNS.h>

#include "FS.h"
#include "SPIFFS.h"

#include "src/Configuration.h"
#include "src/Bootstrapper.cpp"

WebServer server(80);

int direction = HIGH;
int speedLeft = 255;
int speedRight = 255;

void setup() {
  Bootstrapper::waitForSerial();
  Serial.write("Serial ready");
  
  Bootstrapper::initializePins();
  Serial.write("Pins initialized");

  Bootstrapper::setupWifi();
  Serial.write("Wifi ready");
  
  Bootstrapper::initializeFilesystem();
  Serial.write("Filesystem initialized");
  
  server.on("/", handleRoot);
  server.on("/index.js", handleJs);
  server.on("/style.css", handleCss);
  
  server.on("/left/{}", changeSpeedLeft);
  server.on("/right/{}", changeSpeedRight);
  server.begin();
}

void changeSpeedLeft() {
  String arg = server.pathArg(0);
  int speed = arg.toInt();
  speedLeft = 255 - speed;
  Serial.print("New left speed: ");
  Serial.println(speedLeft);
  server.send(200);
}

void changeSpeedRight() {
  String arg = server.pathArg(0);
  int speed = arg.toInt();
  speedRight = 255 - speed;
  Serial.print("New right speed: ");
  Serial.println(speedRight);
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

void handleCss() {
  File file = SPIFFS.open("/style.css", FILE_READ);

  if(!file){
    server.send(404);
    return;
  }

  server.streamFile(file, "text/stylesheet");
  file.close();
}

void loop() {
  server.handleClient();

  digitalWrite(FL1, direction);
  ledcWrite(pwmChannel, speedLeft);

  digitalWrite(BL1, direction);
  ledcWrite(pwmChannel, speedLeft);

  digitalWrite(FR1, direction);
  ledcWrite(pwmChannel, speedRight);

  digitalWrite(BR1, direction);
  ledcWrite(pwmChannel, speedRight);
}