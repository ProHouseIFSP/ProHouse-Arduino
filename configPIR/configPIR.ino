//Programa : Sensor de presenca com modulo PIR
//Autor : FILIPEFLOP
 
int pinopir = 7; //Pino ligado ao sensor PIR
int acionamento; //Variavel para guardar valor do sensor
 
void setup(){
  pinMode(pinopir, INPUT); //Define pino sensor como entrada
  Serial.begin(9600);
}
 
void loop(){
  acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
   
  if (acionamento == LOW){
    Serial.println("Parado");
  }else{
    Serial.println("Movimento !!!");
  }
  delay(500);
}
