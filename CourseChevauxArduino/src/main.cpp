#include <Arduino.h>
#include <AccelStepper.h>

#define BUTTON_PIN 22
#define PIN_STEP1  4
#define PIN_DIR1   5
#define PIN_EN1    6

#define POS_INIT  0
#define POS_FINAL 900
#define MAX_SPEED 200
#define MIN_SPEED 20
#define MAX_ACCELERATION 100
#define MIN_ACCELERATION 30

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

void setup()
{  
    Serial.begin(9600);
    stepper1.setEnablePin(PIN_EN1);
    stepper1.disableOutputs();
    stepper1.setMaxSpeed(MAX_SPEED);
    pinMode(BUTTON_PIN, INPUT);
    
    setMaxSpeed();
    stepper1.enableOutputs();
    stepper1.moveTo(POS_INIT);
    delay(1000);
    stepper1.disableOutputs();
}

bool buttonState = false;
void buttonToogle(){
  if(digitalRead(BUTTON_PIN) == HIGH){
    buttonState = !buttonState;
    setRandomSpeed();
    stepper1.moveTo(POS_FINAL);
    Serial.println("bouton go boom");
  }
}

void loop()
{
    buttonToogle();
    stepper1.run();
}