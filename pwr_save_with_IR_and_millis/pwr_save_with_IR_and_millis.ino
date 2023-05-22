#include <Stepper.h> //library for stepper motor
#include <IRremote.h> //library for IR sensor + controller
#include <HCSR04.h> //library for HCSR04 ultrasonic sensor
#include <avr/sleep.h> //built in arduino IDE library for sleep modes

#define IR_RECEIVE_PIN 14 //define receiveing pin for IR sensor as digital pin 14/analo pin 0

//define buttons of IR controller according to the 'message' they're sending to arduiuno through IR sensor
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
#define button_tag 13
#define button_ok 28
#define button_up 24
#define button_right 90
#define button_down 82
#define button_left 8

bool powerState;     // the current state of power
int buttonState; // the current state of button

unsigned long debounceDuration = 200; // millis
unsigned long lastTimeButtonStateChanged = 0; 

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper1(stepsPerRevolution, 5, 2, 3, 4);
Stepper myStepper2(stepsPerRevolution, 9, 10, 11, 12);

HCSR04 hc(6, new int[2]{7, 8}, 2); //initialisation class HCSR04 (trigger pin , echo pins, number of sensors)

void setup() {
  // put your setup code here, to run once:
IrReceiver.begin(IR_RECEIVE_PIN); //set IR reciever pin as pin 14
set_sleep_mode(SLEEP_MODE_PWR_SAVE); //setting the sleep mode, we're using "power save" sleep mode 

  // initialize the serial port:
Serial.begin(9600);

buttonState = true;

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
  if (IrReceiver.decode()) { //checks if there is any signal from IR sensor and decodes it
      delay(1);
    IrReceiver.resume(); //if some signal is received IR sensor resets and waits for new signal

    int command = IrReceiver.decodedIRData.command; //stores received signal (integer) into command variable

     if(command == button_0) { //if button 0 is pressed, it's separate so the only button that works during sleep mode is this one

        if (millis() - lastTimeButtonStateChanged > debounceDuration) { // debounce button

        buttonState =! buttonState; // change state to the opposite
        
          if (buttonState == true) { // power on, wake up arduino
          lastTimeButtonStateChanged = millis();
          Serial.println("power on");
          delay(50);
          }
          else { // power off, sleep mode
          lastTimeButtonStateChanged = millis();
          Serial.println("power off");
          delay(50);
          sleep_enable(); //enables sleep mode
          sleep_mode(); //executes sleep mode, after this arduino is asleep
          }
        }
      }

      if(buttonState){ //if arduino is awake sensor will register input
    
     switch (command) {
       case button_1: {
       int speed1 = 60;
        // set the speed 60 rpm
        Serial.println("Speed 1 chosen");
       /myStepper1.setSpeed(speed1);
        myStepper2.setSpeed(speed1);
        break;
      }
      case button_2: {
        int speed2 = 100;
        // set the speed 100 rpm
        Serial.println("Speed 2 chosen");
        myStepper1.setSpeed(speed2);
        /myStepper2.setSpeed(speed2); 
        break;
      }
      case button_3: {
        int speed3 = 200; //when 0.7 A current, 250 runs only forward (recomended is 186 so 200 max)
        // set the speed 150 rpm
        Serial.println("Speed 3 chosen");
        myStepper1.setSpeed(speed3);
        myStepper2.setSpeed(speed3); 
        break;
      }  

    }
  }
  }  
   

}
