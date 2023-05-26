#include <IRremote.h>
#include <HCSR04.h>

#define IR_RECEIVE_PIN 14

#define button_1 69
#define button_2 70

HCSR04 hc(6, new int[2]{7, 8}, 2); //initialisation class HCSR04 (trigger pin , echo pins, number of sensors)

void setup() {
  // put your setup code here, to run once:
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
        while(1){
          Serial.println(hc.dist(0));
          delay(1);
        }
        break;
      }
      case button_2: {
        while(1){
          Serial.println(hc.dist(1));
          delay(1);
        }
        break;
      }

}
