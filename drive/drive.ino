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

#include <SPI.h>
#include "src/lib/MAX7219LedMatrix/LedMatrix.h"

#define NUMBER_OF_DEVICES 1
#define CS_PIN 5

/* How to connect
   DIN: HSPID PIN, MOSI
   CS:: Any free pin (CS_PIN)
   CLK: HSPICLK PIN
   GND: Ground
   VCC: 3V3 - 5V
*/

LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

void setup() {
  Bootstrapper::waitForSerial();
  Serial.println("Serial ready");
  
  SPIClass spiRFID;
  spiRFID.begin(14,12,13,15); //CLK,MISO,MOIS,SS
  ledMatrix.init(spiRFID);
  ledMatrix.setIntensity(15); // range is 0-15
  clearLed();
  fullLed();

  Bootstrapper::initializePins();
  Serial.println("Pins initialized");

  Bootstrapper::setupWifi();
  Serial.println("Wifi ready");
  
  Bootstrapper::initializeFilesystem();
  Serial.println("Filesystem initialized");
  
  
  server.on("/", handleRoot);
  server.on("/index.js", handleJs);
  server.on("/style.css", handleCss);
  

  server.on("/left/{}", changeSpeedLeft);
  server.on("/right/{}", changeSpeedRight);
  server.begin();

  Serial.println("ready");
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  clearLed();
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

void clearLed() {
  ledMatrix.clear();
  ledMatrix.commit();
}

void fullLed() {
  ledMatrix.setColumn(0, B11111111);
  ledMatrix.setColumn(1, B11111111);
  ledMatrix.setColumn(2, B11111111);
  ledMatrix.setColumn(3, B11111111);
  ledMatrix.setColumn(4, B11111111);
  ledMatrix.setColumn(5, B11111111);
  ledMatrix.setColumn(6, B11111111);
  ledMatrix.setColumn(7, B11111111);

  ledMatrix.commit();
}

void loop() {
  server.handleClient();

  digitalWrite(FL1, direction);
  ledcWrite(pwmChannelL, speedLeft);

  digitalWrite(BL1, direction);
  ledcWrite(pwmChannelL, speedLeft);

  digitalWrite(FR1, direction);
  ledcWrite(pwmChannelR, speedRight);

  digitalWrite(BR1, direction);
  ledcWrite(pwmChannelR, speedRight);
}