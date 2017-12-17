#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xAC, 0xCD, 0x12, 0x34, 0xFF, 0xCA };

//Os valores abaixo definem o endereço IP, gateway e máscara.

IPAddress ip(192,168,0,250);  // Define o endereço IP.
IPAddress gateway(192,168,0,1);  // Define o gateway.
IPAddress subnet(255, 255, 255, 0);  // Define a máscara de rede.
EthernetServer server(80); //server port

String readString;

const int ldr = A0;
const int pinRele01 = 2;
const int pinRele02 = 3;
const int pinPIR = 4;

int luminosidade = 0;
boolean ligadoE = false;
boolean ligadoL = false;
int movimento;
int tempo = 0;

void setup(){

  pinMode(pinRele01, OUTPUT);
  pinMode(pinRele02, OUTPUT);
  pinMode(pinPIR, INPUT);
  
  digitalWrite(pinRele01, HIGH);
  digitalWrite(pinRele02, HIGH);
  
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void loop(){
  // Fazendo a leitura da luminosidade
  luminosidade = analogRead(ldr);
  
  //recuperando dados do sensor de movimento (PIR)
  movimento = digitalRead(pinPIR);
  if(movimento != LOW){
    if(luminosidade < 300){
      digitalWrite(pinRele02, LOW);
      ligadoL = true;
      tempo = 0;
    }
  }
  
  if(ligadoL){
    tempo++;
    delay(1000);
  }
  
  if(tempo > 30){
    digitalWrite(pinRele02, HIGH);
    ligadoL = false;
    tempo = 0;
  }
  
  
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
          /* 
            Verificando se a pagina para ligar o equipamento foi acessada
            Rele 01
          */
          if(readString.indexOf("?ligarEquipamento") >0){
            digitalWrite(pinRele01, LOW);
            ligadoE = true;
          }
          /* 
            Verificando se a pagina para desligar o equipamento foi acessado
            Rele 01
          */
          if(readString.indexOf("?desligarEquipamento") >0){
              digitalWrite(pinRele01, HIGH);
              ligadoE = false;
          }
          
          
          /* 
            Verificando se a pagina de ligar a luz foi acessada
            Rele 02
          */
          if(readString.indexOf("?ligarLuz") >0){
             if(luminosidade < 300){
                digitalWrite(pinRele02, LOW);
                ligadoL = true;
                tempo = 0;
              }
          }
          
          /* 
            Verificando se a pagina de desligar a luz foi acessada
            Rele 02
          */
          if(readString.indexOf("?desligarLuz") >0){
              digitalWrite(pinRele02, HIGH);
              ligadoL = false;
              tempo = 0;
          }
          
          //clearing string for next read
          readString="";


         paginaPadrao(client);

          delay(1);
          //stopping client
          client.stop();
        }
      }
    }
  }
}


void paginaPadrao(EthernetClient client){
  client.println("HTTP/1.1 200 OK"); //send new page
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html>");
  client.println("<head>");
  //client.println("<meta http-equiv='refresh' content='5;url=/'>");
  client.println("<title>ProHouse</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<button type='submit'><a href='/?ligarEquipamento'>Ligar E</a></button>");
  client.println("<button type='submit'><a href='/?desligarEquipamento'>Desligar E</a></button>");
  client.println("<button type='submit'><a href='/?ligarLuz'>Ligar L</a></button>");
  client.println("<button type='submit'><a href='/?desligarLuz'>Desligar L</a></button>");
  client.println("</div>");
  client.println("</body>");
  client.println("</head>");
}
