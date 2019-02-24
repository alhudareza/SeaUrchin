#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
#include <Servo.h> //library for servo motor

Servo servo1;  // servo motor object for its control
Servo servo2;  // servo motor object for its control
Servo servo3;  // servo motor object for its control
Servo servo4;  // servo motor object for its control

int ang1 = 0;    // a variable to store the servo angle
int ang2 = 0;    // a variable to store the servo angle
int ang3 = 0;    // a variable to store the servo angle
int ang4 = 0;    // a variable to store the servo angle
int ang = 0;    // a variable to store the servo angle

const int irSensorPin = 2;     // the number of the irsensor pin
const int pinMerah = 5;
const int pinBiru = 4;
// variables will change:
volatile int irState = HIGH;   // variable for reading the irsensor status

SoftwareSerial mySerial(10, 11);

void setup () {
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  delay(10);
  
  servo1.attach(6);  // servo motor is attached to pin no 6 og Arduino
  servo2.attach(7);  // servo motor is attached to pin no 7 og Arduino
  servo3.attach(8);  // servo motor is attached to pin no 8 og Arduino
  servo4.attach(9);  // servo motor is attached to pin no 9 og Arduino

  // initialize the irsensor pin as an input:
  pinMode(irSensorPin, INPUT);
  pinMode(pinMerah, OUTPUT);
  pinMode(pinBiru, OUTPUT);
  digitalWrite(pinMerah, HIGH);
  digitalWrite(pinBiru, LOW);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, CHANGE);

  mp3_set_volume (25);
  delay(10);
  mp3_play (1);
  delay(10);

  /*ang = 90;
  servo1.write(ang);
  servo2.write(ang);
  servo3.write(ang);
  servo4.write(ang);
  while(true){
  }*/
}
 
void loop () {
  if (irState == HIGH){
    ang1=0;
    ang2=22;
    ang3=45;
    ang4=67;
    while (true){
       if(irState == LOW){
        int x = random(2)+2;
        mp3_play (x);
        delay(10);
        break;
      }
      servo1.write(90-ang1%90);
      servo2.write(90-ang2%90);
      servo3.write(90-ang3%90);
      servo4.write(90-ang4%90);
      delay(25);
      ang1 +=2;
      ang2 +=2;
      ang3 +=2;
      ang4 +=2;
    }
  } else{
    ang = 0;
    servo1.write(ang);
    servo2.write(ang);
    servo3.write(ang);
    servo4.write(ang);
    delay(50);
    while(true){
      if(irState == HIGH){
        mp3_play (1);
        delay(10);
        break;
      }
    }
  }
}

void pin_ISR() {
  irState = digitalRead(irSensorPin);
  if (irState == HIGH){
    digitalWrite(pinMerah, HIGH);
    digitalWrite(pinBiru, LOW);
  }else{
    digitalWrite(pinMerah, LOW);
    digitalWrite(pinBiru, HIGH);
  }
}
