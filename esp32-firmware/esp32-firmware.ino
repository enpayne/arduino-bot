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

const char* ssid     = "SINGTEL-A5E7";
const char* password = "aeghuanech";

WiFiServer server(80);

String header;

bool moveForward = false;

int speed = 0;

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n') {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
  
              if (header.indexOf("GET /forward") >= 0) {
                Serial.println("Move forward!");
                moveForward = true;
              } else if (header.indexOf("GET /stop") >= 0) {
                Serial.println("Stop!");
                moveForward = false;
              }
  
              // Display HTML page
              sendHtml(client);
              break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected");
  }
  
  if (moveForward) {
    forward();

    delay(10);

    stopp();

    delay(20);
  } else {
    stopp();
  }
}

void sendHtml(WiFiClient client) {
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<body><h1>ESP32 Web Server</h1>");
  client.println("</body></html>");
  client.println();
}

void stopp() {
  stopA();
  stopB();
}

void forward() {
  forwardA();
  forwardB();
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

  server.begin();
}
