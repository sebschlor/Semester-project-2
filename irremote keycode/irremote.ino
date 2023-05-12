
#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
 if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
  }
}
