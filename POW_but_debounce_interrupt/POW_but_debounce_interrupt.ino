#include <IRremote.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define IR_RECEIVE_PIN 2
#define button_tag 13
#define button_star 22

int powerState;     // the current state of power
int buttonState; // the current state of button

const int interruptPin = 2;

unsigned long debounceDuration = 200; // millis
unsigned long lastTimeButtonStateChanged = 0;

void wakeUp();

void setup() {
  // put your setup code here, to run once:
IrReceiver.begin(IR_RECEIVE_PIN);

  // initialize the serial port:
Serial.begin(9600);

buttonState = true;

set_sleep_mode(SLEEP_MODE_PWR_DOWN);

attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp, FALLING);

pinMode(interruptPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  sei();
  if (IrReceiver.decode()) {
    IrReceiver.resume();

    int command = IrReceiver.decodedIRData.command; 

    switch (command) {

      case button_tag: { // if tag button is pressed

        if (millis() - lastTimeButtonStateChanged > debounceDuration) { // debounce button

          buttonState =! buttonState; // change state to the opposite
        
          if (buttonState == true) { // power on, wake up arduino
          lastTimeButtonStateChanged = millis();
          Serial.println("power on");
          }

          else { // power off, sleep mode
          lastTimeButtonStateChanged = millis();
          Serial.println("power off");
          delay(1000);
          sleep_enable();
          sleep_mode();
          }
      }
      }
      case button_star: {
        Serial.println("hello");
        }
      
    }
  }

}
void wakeUp() {
  detachInterrupt(interruptPin);
}
