// Made by chkrr00k
// released in GNU GPL

#include <ESP8266WiFi.h>
#include <string.h>

const char* ssid = "myWiFi"; // SSID of your WiFi;
const char* pass = "hunter2"; // Your WiFi password;

String nick = "NodeMCULedController"; // the nick of your bot;
String chan = "#nietzsche"; // the channel it will join;
String server = "irc.rizon.net"; // the server it will join;
int port = 6667; // the port of the server to join;


void setup() {
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  Serial.begin(9600);
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  
  pinMode(D1, OUTPUT);
}

void loop() {
  bool conn = true;
  if(conn){
    WiFiClient client;
    bool keep = true, auth = false;
    String line;
    unsigned int l = 0;
    
    conn = false;
  
    if(!client.connect(server, port)){
      Serial.println("Error connecting");
    }else{
      Serial.println("Connected");
      client.print("NICK " + nick + "\r\n");
      client.print("USER A B C :NodeMCU System\r\n");
  
      while(keep){
        if(!client.connected()){
          keep = false;
          conn = true;
        }
        if(client.available()){
          line = client.readStringUntil('\n'); // read a line;
          line.trim(); // removes the extra \r\n;
          Serial.println(line); // prints the line;
          
          if(line.startsWith("PING")){ // pings back;
            client.print("PONG " + line.substring(6) + "\r\n");
          }else if(line.indexOf("PRIVMSG") > 0){ // in case of pm;
            int mp = line.substring(1).indexOf(':'); // removes the first : and then asks for the second;
            String mess = line.substring(mp + 2);
            // bot actions;
            if(mess.equals(".on")){
              Serial.println("ON");
              digitalWrite(D1, HIGH);
            }else if(mess.equals(".off")){
              Serial.println("OFF");
              digitalWrite(D1, LOW);
            }
          }
          
          if(!auth && l++ == 6){
            auth = true;
            
            client.print("JOIN " + chan + "\r\n");
          }
        }
        if(Serial.available()){
          line = Serial.readStringUntil('\n');
          line.trim();
          if(line.startsWith("/")){
            client.print(line.substring(1));
          }else{
            client.print("PRIVMSG " + chan + " :" + line + "\r\n");
          }
        }
      }
    }
  }
}
