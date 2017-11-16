const int analogInPin = A0;		         // Pino analógico que o sensor está conectado

int sensorValue = 0;                     // valor que será lido do sensor

int setpoint = 200;                      // Este valor deverá ser alterado de acordo com a intensidade de
										 // luz desejada.                       

void setup() {
  Serial.begin(9600);                    // inicializa a comunicação serial com a taxa de 9600 bps
}

void loop() {
  
  sensorValue = analogRead(analogInPin); // Faz a leitura do pino analógico
  
  Serial.print("sensor = " );            // Imprime o resultado no monitor serial
  Serial.println(sensorValue);      
 

  delay(500);                              // Aguarda 2 milisegundos para estabilizar o conversor ADC                  
}
