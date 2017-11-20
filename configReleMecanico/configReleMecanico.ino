const int pinRele01 = 2;
const int pinRele02 = 3;
const int pinPIR = 4;

boolean ligado = false;
int acionamento;

void setup() {
  pinMode(pinRele01, OUTPUT);
  pinMode(pinRele02, OUTPUT);
  pinMode(pinPIR, INPUT);
  Serial.begin(9600);
  
  // Desligando os equipamentos
  digitalWrite(pinRele01, HIGH);
  digitalWrite(pinRele02, HIGH); 
}

void loop() {
   
  acionamento = digitalRead(pinPIR);
  Serial.println("Acionamento:" + acionamento);

  if(acionamento != LOW){
    if(!ligado){
      Serial.println("Ligado:");
      digitalWrite(pinRele01, LOW);
      digitalWrite(pinRele02, LOW);
      ligado = true;
    }else{
      Serial.println("Desligado:");
      digitalWrite(pinRele01, HIGH);
      digitalWrite(pinRele02, HIGH);
      ligado = false;
    }
    delay(3000);
  }  
  delay(500);
}
