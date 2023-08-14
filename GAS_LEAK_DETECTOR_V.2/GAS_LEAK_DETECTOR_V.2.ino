#include<SoftwareSerial.h>
#include <Servo.h>

Servo servo;

int redLed = 12; //led red
int greenLed = 11; //led green
int buzzer = 10; //buzzer
int smokeA0 = A5; //mq2 sensor
int sensorThres = 40; //change the threshold value asper your need
SoftwareSerial gsm(2, 3); // TX to pin 2 and RX to pin 3

void setup() {
  gsm.begin(9600);
  Serial.begin (9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  servo.attach(9);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("GAS LEVEL ");
  Serial.println(analogSensor);

  if (analogSensor > sensorThres) //checks if it has reached threshold value
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    servo.write(180);
    gsm.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode

delay(1000);

gsm.println("AT+CMGS=\"+917021213704\"\r"); // Replace x with mobile number

delay(1000);

gsm.println("GAS LEAK DETECTED! ACTION SHOULD BE TAKEN USING APP"); // The SMS text you want to send 

delay(100);

gsm.println((char)26); // ASCII code of CTRL+Z

  }
  else
  {
    servo.write(0);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
    delay(100);
}
}
