#include <IRremote.h>

#define IR_RECEIVE_PIN 14
#define button_star 22

int powerState;     // the current state of power
int buttonState; // the current state of button


void setup() {
  // put your setup code here, to run once:
IrReceiver.begin(IR_RECEIVE_PIN);

  // initialize the serial port:
Serial.begin(9600);

buttonState = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    IrReceiver.resume();

    int command = IrReceiver.decodedIRData.command;

    switch (command) {

      case button_star: {
        buttonState =! buttonState;
        if (buttonState == true) {
        Serial.println("power on");
        
        }
        else {
        Serial.println("power off");
        }
      }
    }
  }
}
