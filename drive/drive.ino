#include <HTTP_Method.h>
#include <WebServer.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>


#define FL1 32
#define FL2 33

#define FR1 18
#define FR2 19

#define BL1 25
#define BL2 26

#define BR1 22
#define BR2 23

#define pwmChannel 5

#define pwmChannelFL 0
#define pwmChannelFR 1

#define pwmChannelBL 2
#define pwmChannelBR 3

const char *ssid = "kandersteg";
const char *password = "tunnel";

WebServer server(80);

int direction = HIGH;
int speed = 100;
bool drive = false;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);

  while (!Serial) {
  }

  WiFi.softAP(ssid);
  pinMode(FL1, OUTPUT);  
  pinMode(FL2, OUTPUT);

  pinMode(FR1, OUTPUT);  
  pinMode(FR2, OUTPUT);

  pinMode(BL1, OUTPUT);  
  pinMode(BL2, OUTPUT);

  pinMode(BR1, OUTPUT);  
  pinMode(BR2, OUTPUT);

  Serial.println("helloooo");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  int frequency = 5000;
  int resolution = 8;

  ledcSetup(pwmChannelFL, frequency, resolution);
  ledcAttachPin(FL2, pwmChannel);

  ledcSetup(pwmChannelFR, frequency, resolution);
  ledcAttachPin(FR2, pwmChannel);

  ledcSetup(pwmChannelBL, frequency, resolution);
  ledcAttachPin(BL2, pwmChannel);

  ledcSetup(pwmChannelBR, frequency, resolution);
  ledcAttachPin(BR2, pwmChannel);

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
  // digitalWrite(FL1,HIGH);
  // digitalWrite(FL2,LOW);

  // digitalWrite(FR1,HIGH);
  // digitalWrite(FR2,LOW);

  // digitalWrite(BL1,HIGH);
  // digitalWrite(BL2,LOW);
  
  // digitalWrite(BR1,HIGH);
  // digitalWrite(BR2,LOW);

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