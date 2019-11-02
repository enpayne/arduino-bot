#include <HTTP_Method.h>
#include <WebServer.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "src/pins.h"
#include "src/bootstrapper.cpp";

const char *ssid = "kandersteg";
const char *password = "tunnel";

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
  server.send(200, "text/plain", "hello driver!");
  drive = true;
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