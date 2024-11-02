//====================================================================
// ATIVIDADE FIAP - Cap 12 - A Eletrônica de uma IA
//====================================================================
// Autor.....: Diego Nunes Veiga
// RM........: 560658
// Turma.....: Graduação - 1TIAOR
// Data......: 01/11/2024
//====================================================================

//Bibliotecas utilizadas
#include <DHT.h>

// Sensor DHT22 - Definições
#define pinoDHT 23        // Pino GPIO conectado
#define modelo DHT22      // Modelo do sensor
DHT dht(pinoDHT, modelo);

//Sensor HC-SR04 - Definições
#define trigHC 22        // Pino GPIO conectado ao Trig 
#define echoHC 21        // Pino GPIO conectado ao Echo
#define ledHC 18         // Pino GPIO conectado ao LED

//Sensor PIR - Definições
#define OutPIR 19         // Pino GPIO conectado ao OUT
#define ledPIR 5          // Pino GPIO conectado ao LED
#define buzzer 17         // Pino GPIO conectado ao Buzzer

//Sensor LDR - Definições
#define ldrPin 34         // Pino GPIO conectado ao ADC


//====================================================================
// STARTUP INICIAL
//====================================================================

void setup() {

  // Configurações dos pinos
  pinMode(trigHC, OUTPUT);
  pinMode(echoHC, INPUT); 	
  pinMode(OutPIR, INPUT);    	
  pinMode(ledHC, OUTPUT);
  pinMode(ledPIR, OUTPUT);
  pinMode(buzzer, OUTPUT);
    
  // Inicia a comunicação serial
  Serial.begin(9600);         
  
  // Inicia a comunicação do sensor DHT22
  dht.begin();

}

//====================================================================
// PROGRAMA PRINCIPAL
//====================================================================

void loop() {

  for (int i = 0; i <=21; i++) {

    //-----------------------------------------------------------
    // SENSOR DHT22 - TEMPERATURA E UMIDADE
    // Realiza leitura da saída do sensor
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    int irrigar = 0;

    // analise de temperatura
    if (temp > 30.0) {
      irrigar --;
    }
    else if (temp < 15.0) {
      irrigar ++;
    }

    //analise de humidade
    if (hum > 85){
      irrigar --;
    }
    else if(hum < 50){
      irrigar++;
    }
    


    //-----------------------------------------------------------
    // SENSOR HC-SR04 - DISTÂNCIA
    long duracao;
    int dist;
    int conv;

    // Envia um pulso de 10us para o Trig
    digitalWrite(trigHC, LOW);
    delayMicroseconds(2);
    digitalWrite(trigHC, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigHC, LOW);

    // Calcula o tempo de duração do pulso de retorno no Echo
    duracao = pulseIn(echoHC, HIGH);

    // Calcula a distância em centímetros
    dist = duracao * 0.034 / 2;
    conv = 400 - dist;

    // LED piscando conforme distância
    digitalWrite(ledHC,HIGH);
    delay(dist);
    digitalWrite(ledHC,LOW);

    //-----------------------------------------------------------
    // SENSOR PIR - DISTÂNCIA

    // Realiza leitura da saída do sensor
    int statusPIR = digitalRead(OutPIR);
    
    // Verificação do status de leitura
    if (statusPIR == HIGH) {  
        digitalWrite(ledPIR, HIGH);
        digitalWrite(buzzer, HIGH);
    } else {
        digitalWrite(ledPIR, LOW);
        digitalWrite(buzzer, LOW);
    }

    //-----------------------------------------------------------
    // SENSOR LDR - ILUMINAÇÃO
    const float GAMMA = 0.7;
    const float RL10 = 50;

    // Realiza leitura da saída do sensor
    int ldrValue = analogRead(ldrPin);

    // Converte o valor analógico em valor lux:
    float voltage = ldrValue / 1024. * 5;
    float resistance = 2000 * voltage / (1 - voltage / 5);
    float lux = pow((RL10 * 1e3 * pow(10, GAMMA) / resistance), (1.0 / GAMMA));

    //delay para reinicar o ciclo de leitura dos sensores
    delay(100);

    //Apresentação dos valores
    if (i==21){ 

      //-----------------------------------------------------------
      // SENSOR DHT22 - TEMPERATURA E UMIDADE
      Serial.println("");
      Serial.println("SENSOR DHT22 - TEMPERATURA E UMIDADE");

      // Em caso de erro de leitura
      if (isnan(hum) || isnan(temp)) {
          Serial.println("Falha ao ler do sensor DHT!");
      }

      // Apresentação dos dados no terminal
      Serial.print("Umidade: ");
      Serial.print(hum);
      Serial.print(" %	");
      Serial.print("Temperatura: ");
      Serial.print(temp);
      Serial.println(" °C");

      // Mensagem de alerta
      if(irrigar > 0){
        Serial.println("Alerta: Aumentando a irrigação!");
      } else if (irrigar == 0){
        Serial.println("Irrigação em operação padrão");
      }else{
        Serial.println("Alerta: Reduzindo a irrigação!");
      }
      
      //-----------------------------------------------------------
      // SENSOR HC-SR04 - DISTÂNCIA
      Serial.println("");
      Serial.println("SENSOR HC-SR04 - DISTÂNCIA");
        
      // Apresentação dos dados no terminal
      Serial.print("Altura de água: ");
      Serial.print(conv);
      Serial.println(" cm");

      // Mensagem de alerta
      if(conv < 50){
        Serial.println("Alerta: Abastecer tanque de água!");
      }
    
      //-----------------------------------------------------------
      // SENSOR PIR - DISTÂNCIA
      Serial.println("");
      Serial.println("SENSOR PIR - PRESENÇA / AUSÊNCIA");

      // Realiza leitura da saída do sensor
      int statusPIR = digitalRead(OutPIR);
      
      // Verificação do status de leitura
      if (statusPIR == HIGH) {  
          Serial.println("Movimento detectado na colheita!");
      } else {
          Serial.println("Colheita normal");
      }

      //-----------------------------------------------------------
      // SENSOR LDR - ILUMINAÇÃO
      Serial.println("");
      Serial.println("SENSOR LDR - ILUMINAÇÃO");

      // Apresentação dos dados no terminal
      Serial.print("Nível de Luz: ");
      Serial.print(lux);
      Serial.println(" lux");
      
      // Mensagem de alerta
      if (lux >= 10000) {
        Serial.println("Alerta: Dia ensolarado!");
      }
      else if (lux > 1000 && lux < 10000) {
        Serial.println("Dia padrão");
      }
      else {
        Serial.println("Alerta: Dia nublado!");
      }

    }
  }
} 