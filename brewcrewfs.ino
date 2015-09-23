#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h>

// Local Network Settings
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x98, 0xCF }; // Must be unique on local network
byte ip[]  = { 192, 168, 0, 183 };                // Must be unique on local network


// ThingSpeak Settings
byte server[]  = { 184, 106, 153, 149 };         // IP Address for the ThingSpeak API
String thingtweetAPIKey = "YLT3ZPGMYUYL9ULJ";  // Write API Key for a ThingSpeak Channel
EthernetClient client;

// Variable Setup
boolean lastConnected = false;

void setup()
{
  Twitter twitter("2351957653-MGPH7DmrzmNcKWOYi3NbAZsjjHvMmq5hoxEE9HV");  // this was YourID:Password in 1.0.1
  Serial.begin(57600);
  Ethernet.begin(mac, ip);
  delay(1000);
  
  // Update Twitter via ThingTweet
  if(!client.connected())
  {
    updateTwitterStatus("I just tweeted @brewcrewfs #WebDevKids #ArduinoLife");
  }
}

void loop()
{  
  // Print Update Response to Serial Monitor
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
  
  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println();
    Serial.println("...disconnected.");
    Serial.println();
    
    client.stop();
  }
  
  lastConnected = client.connected();
}

void updateTwitterStatus(String tsData)
{
  if (client.connected() && tsData.length() > 0)
  { 
    // Create HTTP POST Data
    tsData = "api_key="+thingtweetAPIKey+"&status="+tsData;
    
    Serial.println("Connected to ThingTweet...");
    Serial.println();
        
    client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");

    client.print(tsData);
  }
  else
  {
    Serial.println("Connection Failed.");   
    Serial.println();
  }
}
