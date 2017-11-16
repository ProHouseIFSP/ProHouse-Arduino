#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xAB, 0xCD, 0x12, 0x34, 0xFF, 0xCA };

//Os valores abaixo definem o endereço IP, gateway e máscara.

IPAddress ip(192,168,0,2);  // Define o endereço IP.
IPAddress gateway(192,168,0,1);  // Define o gateway.
IPAddress subnet(255, 255, 255, 0);  // Define a máscara de rede.
EthernetServer server(80); //server port

String readString;

int pin = 13; 
boolean ligado = true;

//////////////////////

void setup(){

  pinMode(pin, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("RoboCore Remote Automation V1.1"); // so I can keep track of what is loaded
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////////// control arduino pin
          Serial.println(readString); //print to serial monitor for debuging
          if(readString.indexOf("?ligar") >0)//checks for on
          {
            digitalWrite(pin, HIGH);    // set pin 4 high
            Serial.println("On");
            ligado = true;
          }
          else{
            if(readString.indexOf("?desligar") >0)//checks for off
            {
              digitalWrite(pin, LOW);    // set pin 4 low
              Serial.println("Off");
              ligado = false;
            }
          }
          //clearing string for next read
          readString="";


          ///////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<title>ProHouse</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div>Status");
          if(ligado){
            client.println("<div>Equipamento ligado</div>");
          }else{
            client.println("<div>Equipamento desligado</div>");
          }
          client.println("</div>");
          client.println("<div id='botao'></div>");
          client.println("</div>");
          client.println("</body>");
          client.println("</head>");

          delay(1);
          //stopping client
          client.stop();



        }
      }
    }
  }
}

