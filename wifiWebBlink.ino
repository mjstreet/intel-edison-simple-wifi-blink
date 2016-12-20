//arduino simplewebserver + blink on WPA network connected Intel Edison

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "YOURSSID";           // network SSID
char pass[] = "PASSWORD1";          // network password
int ledPin = 7;                     // led pin on breakout
int status = WL_IDLE_STATUS;        // initial server state
WiFiServer server(8080);            // server port


void setup() {
  Serial.begin(9600);               // setup serial comms
  pinMode(ledPin, OUTPUT);          // set the LED pin

 // try to connect to my WPA network
  while ( status != WL_CONNECTED) { 
    Serial.print("Connecting to: ");
    Serial.println(ssid);                  
    status = WiFi.begin(ssid, pass);        
    delay(10000);
  } 
  server.begin();                           // start the web server on port 8080
  printWifiStatus();                        // print connection confirmation
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming connections/client

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    digitalWrite(ledPin, HIGH);             // turn LED on..
    delay(2000);                            // ..wait..
    digitalWrite(ledPin, LOW);              // ...turn LED off

    client.println("HTTP/1.1 200 OK");      //print to client
    client.println("Content-type:text/html");
    client.println();
    client.print("boop");
    client.println();

    client.stop();                          // close the connection:
    Serial.println("client disonnected");   // log to serial

  }
}

void printWifiStatus() {
  Serial.print("SSID: ");                   // SSID
  Serial.println(WiFi.SSID());
  
  IPAddress ip = WiFi.localIP();            // IP Adress
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  Serial.print("Server up!");               // Confirmation message
}
