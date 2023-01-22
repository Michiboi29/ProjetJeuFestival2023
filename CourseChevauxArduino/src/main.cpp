#include <Arduino.h>
#include <AccelStepper.h>

#define BUTTON_PIN 22
#define PIN_STEP1  4
#define PIN_DIR1   5
#define PIN_EN1    6

#define POS_INIT  0
#define POS_FINAL 900
#define MAX_SPEED 700
#define MIN_SPEED 50
#define MAX_ACCELERATION 50
#define MIN_ACCELERATION 1

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1);

void test(){
  stepper1.setMaxSpeed(200.0);
  stepper1.setSpeed(50);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(24);
}

void setRandomSpeed(){
  int speed = random(MIN_SPEED,MAX_SPEED);
  int acceleration = random(MIN_ACCELERATION,MAX_ACCELERATION);
  stepper1.setSpeed(speed);
  stepper1.setAcceleration(acceleration);
}

void setMaxSpeed(){
  stepper1.setSpeed(MAX_SPEED);
  stepper1.setAcceleration(MAX_ACCELERATION);
}

void goEnd(){
  setRandomSpeed();
  stepper1.enableOutputs();
  stepper1.moveTo(POS_FINAL);
  Serial.println("bouton go boom");
  delay(200);
  stepper1.disableOutputs();
}

void goStart(){
  setMaxSpeed();
  stepper1.enableOutputs();
  stepper1.moveTo(POS_INIT);
  Serial.println("bouton go back");
  delay(500);
  stepper1.disableOutputs();
}

bool toogleButts = false;
bool buttonState = false;
bool buttonLastState = false;
void buttonToogle(){
  buttonLastState = buttonState;
  if(digitalRead(BUTTON_PIN) == HIGH){
    buttonState = true;
  }
  else{
    buttonState = false;
  }
   
  if(buttonState && !buttonLastState){
    toogleButts = !toogleButts;
    if (toogleButts){
      goEnd();
    }
    else{
      goStart();
    }
    delay(125);
  }
  
}

void setup()
{  
    Serial.begin(9600);
    stepper1.setEnablePin(PIN_EN1);
    stepper1.disableOutputs();
    stepper1.setMaxSpeed(MAX_SPEED);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    goStart();
}



void loop()
{
    buttonToogle();
    stepper1.run();
}