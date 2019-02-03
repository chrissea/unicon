#include <HardwareSerial.h>

HardwareSerial UART_PSOC(1);//(1);

 
void setup() {
 
  Serial.begin(115200);
 
  // setup UART serial communication with the PSoC
  //                                  RX, TX
  UART_PSOC.begin(57600, SERIAL_8N1, 16, 17);
}
 
void loop() {
  Serial.print("available? ");
  Serial.println(UART_PSOC.available());
//  if (UART_PSOC.available()) {
    UART_PSOC.write('A');
    Serial.println("sending to psoc");
//  }
    Serial.println((char) UART_PSOC.read());
  delay(10);
}
