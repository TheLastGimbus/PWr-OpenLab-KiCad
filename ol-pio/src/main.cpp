#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO 4
#define PIN_555 3
#define PIN_MIC 5
#define PIN_TRIG 6
#define PIN_ECHO 7


Servo servo;
bool open = false;

// Clap detection
bool lastMicState = false;
unsigned long lastRaise = 0;
#define IGNORE_TIME 200
#define DOUBLE_TIME 1000

void setup() {
  pinMode(PIN_MIC, INPUT);
  servo.attach(PIN_SERVO);
}

bool risingEdge() {
	return !lastMicState && digitalRead(PIN_MIC);
}

void loop() {
  if(risingEdge() && (millis() - lastRaise) > IGNORE_TIME){
    if(millis() - lastRaise < DOUBLE_TIME){
    	lastRaise = millis() - DOUBLE_TIME;
	  	open = !open;
    } else {
    	lastRaise = millis();    	
    }
  }

  lastMicState = digitalRead(PIN_MIC);
  servo.write(open ? 160 : 90);
}
