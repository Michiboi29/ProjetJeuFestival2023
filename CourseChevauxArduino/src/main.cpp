#include <Arduino.h>
#include <AccelStepper.h>

#define BUTTON_PIN 22
#define PIN_STEP1  23
#define PIN_DIR1   24
#define PIN_EN1    25
#define PIN_STEP2  26
#define PIN_DIR2   27
#define PIN_EN2    28
#define PIN_STEP3  29
#define PIN_DIR3   30
#define PIN_EN3    31
#define PIN_STEP4  32
#define PIN_DIR4   33
#define PIN_EN4    34

#define POS_INIT  0
#define POS_FINAL 16000
#define MAX_SPEED 300
#define MIN_SPEED 30
#define MAX_ACCELERATION 30
#define MIN_ACCELERATION 1

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, PIN_STEP1, PIN_DIR1);
AccelStepper stepper2(AccelStepper::DRIVER, PIN_STEP2, PIN_DIR2);
AccelStepper stepper3(AccelStepper::DRIVER, PIN_STEP3, PIN_DIR3);
AccelStepper stepper4(AccelStepper::DRIVER, PIN_STEP4, PIN_DIR4);

void setRandomSpeed(){
  int speed1 = random(MIN_SPEED,MAX_SPEED);
  int acceleration1 = random(MIN_ACCELERATION,MAX_ACCELERATION);
  stepper1.setSpeed(speed1);
  stepper1.setAcceleration(acceleration1);

  int speed2 = random(MIN_SPEED,MAX_SPEED);
  int acceleration2 = random(MIN_ACCELERATION,MAX_ACCELERATION);
  stepper2.setSpeed(speed2);
  stepper2.setAcceleration(acceleration2);

  int speed3 = random(MIN_SPEED,MAX_SPEED);
  int acceleration3 = random(MIN_ACCELERATION,MAX_ACCELERATION);
  stepper3.setSpeed(speed3);
  stepper3.setAcceleration(acceleration3);

  int speed4 = random(MIN_SPEED,MAX_SPEED);
  int acceleration4 = random(MIN_ACCELERATION,MAX_ACCELERATION);
  stepper4.setSpeed(speed4);
  stepper4.setAcceleration(acceleration4);
}

void setMaxSpeed(){
  stepper1.setSpeed(MAX_SPEED);
  stepper1.setAcceleration(MIN_ACCELERATION);

  stepper2.setSpeed(MAX_SPEED);
  stepper2.setAcceleration(MIN_ACCELERATION);

  stepper3.setSpeed(MAX_SPEED);
  stepper3.setAcceleration(MIN_ACCELERATION);

  stepper4.setSpeed(MAX_SPEED);
  stepper4.setAcceleration(MIN_ACCELERATION);
}

void goEnd(){
  setRandomSpeed();
  stepper1.enableOutputs();
  stepper1.moveTo(POS_FINAL);
  stepper2.enableOutputs();
  stepper2.moveTo(POS_FINAL);
  stepper3.enableOutputs();
  stepper3.moveTo(POS_FINAL);
  stepper4.enableOutputs();
  stepper4.moveTo(POS_FINAL);
  Serial.println("bouton go boom");
  delay(200);
  stepper1.disableOutputs();
  stepper2.disableOutputs();
  stepper3.disableOutputs();
  stepper4.disableOutputs();
}

void goStart(){
  setMaxSpeed();
  stepper1.enableOutputs();
  stepper1.moveTo(POS_INIT);
  stepper2.enableOutputs();
  stepper2.moveTo(POS_INIT);
  stepper3.enableOutputs();
  stepper3.moveTo(POS_INIT);
  stepper4.enableOutputs();
  stepper4.moveTo(POS_INIT);
  Serial.println("bouton go back");
  delay(500);
  stepper1.disableOutputs();
  stepper2.disableOutputs();
  stepper3.disableOutputs();
  stepper4.disableOutputs();
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
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    stepper1.setEnablePin(PIN_EN1);
    stepper1.disableOutputs();
    stepper1.setMaxSpeed(MAX_SPEED);
    
    stepper2.setEnablePin(PIN_EN1);
    stepper2.disableOutputs();
    stepper2.setMaxSpeed(MAX_SPEED);

    stepper3.setEnablePin(PIN_EN1);
    stepper3.disableOutputs();
    stepper3.setMaxSpeed(MAX_SPEED);

    stepper4.setEnablePin(PIN_EN1);
    stepper4.disableOutputs();
    stepper4.setMaxSpeed(MAX_SPEED);

    goStart();
}



void loop()
{
    buttonToogle();
    stepper1.run();
    stepper2.run();
    stepper3.run();
    stepper4.run();
}