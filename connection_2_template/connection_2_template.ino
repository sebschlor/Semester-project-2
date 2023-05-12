// Include the Arduino Stepper Library
#include <Stepper.h>
#include <IRremote.h>
#include <HCSR04.h>

#define IR_RECEIVE_PIN 14

#define button_1 69
#define button_2 70 
#define button_3 71 
#define button_4 68 
#define button_5 64 
#define button_6 67 
#define button_7 7 
#define button_8 21 
#define button_9 9 
#define button_0 25
#define button_star 22 
#define button_tag 30 
#define button_ok 28 
#define button_up 24
#define button_right 90
#define button_down 82
#define button_left 8  

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 5, 2, 3, 4);

HCSR04 hc(6, new int[2]{7, 8}, 2); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)

void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(IR_RECEIVE_PIN);

  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

 // step one revolution in one direction:
if (IrReceiver.decode()) {
    IrReceiver.resume();
    
    int command = IrReceiver.decodedIRData.command;

    switch (command) {
      case button_1: {
       int speed1 = 60;
        // set the speed 60 rpm
        Serial.println("Speed 1 chosen");
        myStepper.setSpeed(speed1);
        break;
      }
      case button_2: {
        int speed2 = 100;
        // set the speed 100 rpm
        Serial.println("Speed 2 chosen");
        myStepper.setSpeed(speed2); 
        break;
      }
      case button_3: {
        int speed3 = 200; //when 0.7 A current, 250 runs only forward (recomended is 186 so 200 max)
        // set the speed 150 rpm
        Serial.println("Speed 3 chosen");
        myStepper.setSpeed(speed3); 
        break;
      }
      case button_4: {
        Serial.println( hc.dist(0) );//return curent distance (cm) in serial for sensor 1 to 2
        delay(60);
        break;
      }
      case button_5: {
        Serial.println( hc.dist(1) );//return curent distance (cm) in serial for sensor 1 to 2
        delay(60);
        break;
      }
      case button_star: {
        // on off power
        break;
      }
      case button_tag: {
        // interrupt stop
        break;
      }
      case button_up: {
        Serial.println("Going forward");
        myStepper.step(stepsPerRevolution);  //it does exactly 2 rotations
        break;
      }
      case button_down: {
        Serial.println("Going backward");
        myStepper.step(-stepsPerRevolution);
        break;
      }
      case button_right: {
        // motor 2 forward
        break;
      }
      case button_left: {
        // motor 2 backward
        break;
      }
      default: {
        Serial.println("Button not recognized");
      }
    }
  }
}