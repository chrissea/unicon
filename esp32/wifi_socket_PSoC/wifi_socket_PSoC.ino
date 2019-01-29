#include <WiFi.h>
#include <HardwareSerial.h>

const char* ssid = "Heirloom Guest";
const char* password =  "";

/*           
 *            CONTROLLER LAYOUT
 *   
 *    ZL                                 ZR
 *    L ________________________________ R
 *   |                SEL                 |
 *   |    LU                       RU     |
 *   |  LL  LR    LJ       RJ    RL  RR   |
 *   |    LD                       RD     |
 *   |________________ST__________________|
 *  
 *  
 *  
 */


HardwareSerial UART_PSOC(0);//(1);

WiFiServer wifiServer(8000);
 
void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
  
  // connect to WiFi network
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  // start WiFi server
  wifiServer.begin();

  // setup UART serial communication with the PSoC
  //                                 RX, TX
  UART_PSOC.begin(115200, SERIAL_8N1, 3, 1);
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
 
  while (client) {
    if (client.connected()){
      Serial.println("Client connected");
    }
    while (client.connected()) {
      while (client.available() > 0) {
        char c = client.read();
        Serial.println(c);
        
        if (UART_PSOC.available()) {
          UART_PSOC.write(c);
          Serial.print("Sending to psoc: ");
          Serial.println(c);
        }
        if (UART_PSOC.available()) {
          char c = UART_PSOC.read();
          Serial.print("Received from psoc: ");
          Serial.print(c);
          
          client.write(c);
          Serial.println("Sending to app: ");
          Serial.println(c);
        }
      
      }
      delay(10);
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}


//    while (client.connected()) {client.available() > 0) {
