
#define Ain1 23
#define Ain2 22
#define Bin1 1 // working
#define Bin2 3 // working


int speed = 0;

void setup() {
  pinMode(Ain1, OUTPUT);  //Ain1
  pinMode(Ain2, OUTPUT);  //Ain2
  pinMode(Bin1, OUTPUT);  //Bin1
  pinMode(Bin2, OUTPUT);  //Bin2
}


void loop() {
 
digitalWrite(Ain1,HIGH);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,HIGH);
    digitalWrite(Bin2,LOW);
    delay(700);
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,HIGH);
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,HIGH);
    delay(700);
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
  
}
