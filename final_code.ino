#include <Stepper.h> //library for stepper motor
#include <IRremote.h> //library for IR sensor + controller
#include <HCSR04.h> //library for HCSR04 ultrasonic distance sensor
#include <avr/sleep.h> //built in arduino IDE library for sleep modes

#define IR_RECEIVE_PIN 14 //define receiveing pin for IR sensor as digital pin 14/analog pin 0

//define buttons of IR controller according to the 'message' they're sending to arduiuno through IR sensor
#define button_1 69
#define button_2 70
#define button_3 71
#define button_4 68
#define button_5 64
#define button_6 67 //in cases for button 6-9 motors make only 1 step in loop to achieve "smooth" movement
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
int buttonState;     // the current state of button

unsigned long debounceDuration = 200; // millis
unsigned long lastTimeButtonStateChanged = 0; 

// Number of steps per output rotation
const int stepsPerRevolution = 200;

int speed1 = 60; //60 revolutions per minute
int speed2 = 100; //100 revolutions per minute
int speed3 = 200; //200 revolutions per minute

// Create Instance of Stepper library
Stepper myStepper1(stepsPerRevolution, 2, 3, 4, 5); //define pins for lower motor as digital pins 2-5
Stepper myStepper2(stepsPerRevolution, 9, 10, 11, 12); //define pins for the upper motor as digital pins 9-12

HCSR04 hc(6, new int[2]{7, 8}, 2); //initialisation class HCSR04 for the ultrasonic disstance sensors (trigger pin , echo pins, number of sensors)

void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(IR_RECEIVE_PIN); //set IR reciever pin as pin 14
  set_sleep_mode(SLEEP_MODE_PWR_SAVE); //setting the sleep mode, we're using "power save" sleep mode 

  // initialize the serial port = communication with laptop so Arduino can send (print function) or receive data (uploading the code) through the serial port (usb cable)
  Serial.begin(9600); //9600 is the baud rate of the communication, meaning speed of sending data is 9600 bits per second

  buttonState = true; //setting buttonState to true so arduino is awake when the program starts

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1); //little delay not ot overwork arduino
  if (IrReceiver.decode()) { //checks if there is any signal from IR sensor and decodes it
      delay(1); //little delay not ot overwork arduino
    IrReceiver.resume(); //if some signal is received IR sensor resets and waits for new signal

    int command = IrReceiver.decodedIRData.command; //stores received signal (integer) into command variable

     if(command == button_0) { //if button 0 is pressed

        if (millis() - lastTimeButtonStateChanged > debounceDuration) { // debounce button

        buttonState =! buttonState; // change state to the opposite so when arduino is awake and button is pressed it goes to sleep & vice versa
        
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

    if(buttonState){ //if variable buttonState is true, meaning arduino is awake this code works, if arduino is asleep buttonStste is false 
    
     switch (command) {
       case button_1: {       
        // set the speed 60 rpm for both motors & prints the chosen speed
        Serial.println("Speed 1 chosen");
        myStepper1.setSpeed(speed1);
        myStepper2.setSpeed(speed1);
        break; //so the code won't be stuck inside of the case
      }
      case button_2: {        
        // set the speed 100 rpm for both motors & prints the chosen speed
        Serial.println("Speed 2 chosen");
        myStepper1.setSpeed(speed2);
        myStepper2.setSpeed(speed2); 
        break; //so the code won't be stuck inside of the case
      }
      case button_3: {        
        // set the speed 200 rpm for both motors & prints the chosen speed
        Serial.println("Speed 3 chosen");
        myStepper1.setSpeed(speed3);
        myStepper2.setSpeed(speed3); 
        break; //so the code won't be stuck inside of the case
      }
      case button_4: {
        Serial.println( hc.dist(0));//return curent distance (cm) in serial for sensor 1 (on lower axis)
        delay(60);
        break; //so the code won't be stuck inside of the case
      }
      case button_5: {
        Serial.println( hc.dist(1) );//return curent distance (cm) in serial for sensor 2 (on the upper axis)
        delay(60);
        break; //so the code won't be stuck inside of the case
      }
      case button_6: {
        delay(1);
        while((hc.dist(0) > 4.5) || (hc.dist(1) > 3)){//if condition checks distance from the sensors so the slider won't fall off 
            myStepper1.step(1); //lower motor goes forward //it does exactly 2 rotations
            myStepper2.step(1); //upper motor goees forward
          
        }return 0; //sending 0 to indicate loop was succesfully terminated and code is waiting for another signal (button press)
        break; //so the code won't be stuck inside of the case
      }
       case button_7: {
         delay(1);
        while((hc.dist(0) > 4.5) || (hc.dist(1) < 32)){//if condition checks distance from the sensors so the slider won't fall off 
            myStepper1.step(1);  //lower motor goes forward //it does exactly 2 rotations
            myStepper2.step(-1); //upper motor goes back
        }return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
      }
       case button_8: {
         delay(1);
        while((hc.dist(0) < 41) || (hc.dist(1) > 3)){// condition checks distance from the sensors so the slider won't fall off 
            myStepper1.step(-1); //lower motor goes back  //it does exactly 2 rotations
            myStepper2.step(1); //upper motor goes forward
        }return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
      }
       case button_9: {
         delay(1);
        while((hc.dist(0) < 41) || (hc.dist(1) < 30)){// condition checks distance from the sensors so the slider won't fall off 
            myStepper1.step(-1); //lower motor goes back //it does exactly 2 rotations
            myStepper2.step(-1); //upper motor goes back
        }return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
      }
      case button_star: { //this button moves the slider forward and then to the right
        delay(1);
        myStepper1.setSpeed(speed3);
        myStepper2.setSpeed(speed2); 
        while((hc.dist(0) > 5)){// condition checks distance from the sensors so the slider won't fall off   
            myStepper1.step(stepsPerRevolution); //lower motor goes forward, slider moves to the end
          }
        while((hc.dist(1) < 36)){ // condition checks distance from the sensors so the slider won't fall off 
            myStepper2.step(-stepsPerRevolution); //upper motor goes backward, slider moves to the motor
          }return 0; //sending 0 to indicate loop was succesfully terminated
          break; //so the code won't be stuck inside of the case
        }
        
      
      case button_tag: { //this button moves slider backward and then left
        delay(1);
        myStepper1.setSpeed(speed3);
        myStepper2.setSpeed(speed2); 
        while((hc.dist(0)<41)){ // condition checks distance from the sensors so the slider won't fall off 
            myStepper1.step(-stepsPerRevolution); //lower motor goes backward, slider moves to the motor
          }
        while((hc.dist(1)>4)){
            myStepper2.step(stepsPerRevolution); //upper motor goes forwawrd, slider moves to the end
          }return 0; //sending 0 to indicate loop was succesfully terminated
        
        break; //so the code won't be stuck inside of the case
      }
      case button_up: {
        delay(1);
        while((hc.dist(0) > 5.5)){ // condition checks distance from the sensors so the slider won't fall off  
            myStepper1.step(stepsPerRevolution);  //it does exactly 2 rotations forward (lower motor)
        } return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
      }
      case button_down: {
        delay(1);
        while((hc.dist(0)<41)){//if condition checks distance from the sensors so the slider won't fall of
            myStepper1.step(-stepsPerRevolution);  //it does exactly 2 rotations back (lower motor)
        } return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
      }
      case button_right: {
        delay(1);
        while((hc.dist(1) < 37)){ //if condition checks distance from the sensors so the slider won't fall of
            myStepper2.step(-stepsPerRevolution);  //it does exactly 2 rotations back (upper motor)
        }return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
        
      case button_left: {
        case button_right: {
        while((hc.dist(1)>4)){//if condition checks distance from the sensors so the slider won't fall of
            myStepper2.step(stepsPerRevolution);  //it does exactly 2 rotations forward (upper motor)
        } return 0; //sending 0 to indicate loop was succesfully terminated
        break; //so the code won't be stuck inside of the case
      }
      default: { //if signal from the controller isn't caught
        Serial.println("Button not recognized"); //prints this message on serial monitor
      }
     }
    }
  }
}   
