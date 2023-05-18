#include <IRremote.h>

#define IR_RECEIVE_PIN 7

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
if (IrReceiver.decode()) {
    IrReceiver.resume();
    
    int command = IrReceiver.decodedIRData.command;

    switch (command) {
      case button_1: {
        //speed low
        break;
      }
      case button_2: {
        // speed medium
        break;
      }
      case button_3: {
        // speed high
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
        // motor 1 forward
        break;
      }
      case button_down: {
        // motor 1 backward
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
