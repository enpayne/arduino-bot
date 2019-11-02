#include <Arduino.h>

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

void setup() {
  pinMode(FL1, OUTPUT);  
  pinMode(FL2, OUTPUT);

  pinMode(FR1, OUTPUT);  
  pinMode(FR2, OUTPUT);

  pinMode(BL1, OUTPUT);  
  pinMode(BL2, OUTPUT);

  pinMode(BR1, OUTPUT);  
  pinMode(BR2, OUTPUT);

  Serial.begin(115200);
  
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

  Serial.println("Hello World");
}

void loop() {
  // digitalWrite(FL1,HIGH);
  // digitalWrite(FL2,LOW);

  // digitalWrite(FR1,HIGH);
  // digitalWrite(FR2,LOW);

  // digitalWrite(BL1,HIGH);
  // digitalWrite(BL2,LOW);
  
  // digitalWrite(BR1,HIGH);
  // digitalWrite(BR2,LOW);

    int speed = 200;

    digitalWrite(FL1,HIGH);
    ledcWrite(pwmChannel, speed);

    digitalWrite(FR1,HIGH);
    ledcWrite(pwmChannel, speed);

    digitalWrite(BL1,HIGH);
    ledcWrite(pwmChannel, speed);

    digitalWrite(BR1,HIGH);
    ledcWrite(pwmChannel, speed);
} 