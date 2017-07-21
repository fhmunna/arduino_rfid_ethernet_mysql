#include <SoftwareSerial.h>
#include <SPI.h>
SoftwareSerial rfid = SoftwareSerial(6, 7);
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0x3A, 0xDC};
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
IPAddress server(10,42,0,1);   // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10,42,0,10);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
  String msg;
String ID = "020043601736, 020043DFF866" ;  //string to store allowed cards
int speakerOut = 5;
void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial Ready");
    delay(100);

  pinMode(speakerOut, OUTPUT);
}

void loop(){
  
    rfid.begin(9600);
  Serial.println("RFID Ready");
  
  while(rfid.available()>0){
    char c;
  Serial.println("Access 1.");
    for(int thin = 0; thin <14; thin++)
    {                            
      c=rfid.read(); 
      msg += c;
      
    }   Serial.println("Access 2.");
       digitalWrite(speakerOut,HIGH);
    delay(100);
    digitalWrite(speakerOut,LOW);
    delay(100);
  Serial.println(msg);
     if(msg.length()==14) {
  msg=msg.substring(1,13);
  Serial.println(msg);
  if(ID.indexOf(msg)>=0) { 
    Serial.println("Access granted.");
    digitalWrite(speakerOut,HIGH);
    delay(100);
    digitalWrite(speakerOut,LOW);
    delay(100);
    digitalWrite(speakerOut,HIGH);
    delay(100);
    digitalWrite(speakerOut,LOW);
    
     Serial.println("connecting DB...");
 // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
   //client.print("GET /rec.php HTTP/1.1\n");
    client.print("GET /inm.php?name=");
    client.print(msg);
    client.println(" HTTP/1.1");    
    client.println("Host: 10.42.0.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }    
     
     msg="";
      rfid.end();
      delay(1000);
  while(rfid.read() != -1) {}; //This one to clear the buffer?
   
     
  }   
  else {
    Serial.println("Access denied.");
    digitalWrite(speakerOut,HIGH);   
    delay(1000);
    digitalWrite(speakerOut,LOW);
     delay(1000);
     msg="";
     while(rfid.read() != -1) {}; //This one to clear the buffer?
  }
}
   
 
}
rfid.end();
}
