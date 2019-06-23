#include <WiFi.h>

#define Ain1 23
#define Ain2 22
#define Bin1 19
#define Bin2 18

/*
 * Arduino IDE Setup:
 * * Board: NodeMCU-32S
 * * Programer: AVRISP mkll
 * 
 * Required Libraries
 * * (none yet)
 */

const char* ssid     = "Fas-IoT";
const char* password = "";

int speed = 0;

void setup() {
  pinMode(Ain1, OUTPUT);  //Ain1
  pinMode(Ain2, OUTPUT);  //Ain2
  pinMode(Bin1, OUTPUT);  //Bin1
  pinMode(Bin2, OUTPUT);  //Bin2

  // Start with drivers off, motors coasting.
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void forwardA() {
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,HIGH);
}

void forwardB() {
    digitalWrite(Bin1,HIGH);
    digitalWrite(Bin2,LOW);
}

void stopA() {
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
}

void stopB() {
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
}

void stopp() {
  stopA();
  stopB();
}

void forward() {
  forwardA();
  forwardB();
}

void strangeMoves() {

    bool a = true;
    bool b = true;

    forward();

    delay(5);

    stopp();

    delay(20);
    
    /*
    delay(700);
    
    if (a) {
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,LOW);
    }
    
    if (b) {
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,LOW);
    }
    
    if (a) {
      digitalWrite(Ain1,LOW);   
      digitalWrite(Ain2,HIGH);
    }
    if (b) {
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,HIGH);
    }
    
    delay(700);
    
    if (a) {
      digitalWrite(Ain1,LOW);
      digitalWrite(Ain2,LOW);
    }
    if (b) {
      digitalWrite(Bin1,LOW);
      digitalWrite(Bin2,LOW);
    }

    */
}
void loop() {
    strangeMoves();
}
