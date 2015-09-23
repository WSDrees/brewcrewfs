#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h>


// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x98, 0xCF };
 
//the IP address for the shield:
byte ip[] = { 192, 168, 0, 183 };

char msg[] = "I just tweeted @brewcrewfs #WebDevKids #ArduinoLife";

EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Twitter twitter("2351957653-MGPH7DmrzmNcKWOYi3NbAZsjjHvMmq5hoxEE9HV");  // this was YourID:Password in 1.0.1
  Serial.begin(57600);
  // Start Ethernet on Arduino
  Ethernet.begin(mac);

  delay(1000);
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }



}

void loop() {
  // put your main code here, to run repeatedly:
  

}





