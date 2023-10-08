#include <ArduinoIoTCloud.h>

#include "thingProperties.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>

//sensor de temperatura
int sensor_temp = 5;
DHT dht11(sensor_temp, DHT11);
int temp;
int hum;

//sensores infrarrojos
int sensor_ir1 = 4;
int valor_ir1;
int sensor_ir2 = 0;
int valor_ir2;

//sensor de humo
int sensor_mq = A0;

//led de emergencia
int led = 16;

void setup() {
  Serial.begin(9600);
  delay(1500); 
  dht11.begin();
  pinMode(sensor_temp, INPUT);
  pinMode(sensor_ir1, INPUT);
  pinMode(sensor_ir2, INPUT);
  pinMode(led, OUTPUT);

  initProperties();

  //conexion a la IOT cloud de arduino
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  temp = dht11.readTemperature();
  hum = dht11.readHumidity();
  
  valor_ir1 = digitalRead(sensor_ir1);
  valor_ir2 = digitalRead(sensor_ir2);
  
  int i;
  int j;
  int k;
  int aux1; //auxiliar infrarrojo1
  int aux2; //auxiliar infrarrojo2
  
  for(i = 0; i < 100; i++){
    temperatura = temperatura + temp;
  }
  temperatura = round(temperatura/100);
  
  for(j = 0; j < 50; j++){
    humedad = humedad + hum;
  }
  humedad = humedad/50;
  
  for(k = 0; k < 100; k++){
    aux1 = aux1 + valor_ir1;
    aux2 = aux2 + valor_ir2;
  }
  aux1 = aux1/100;
  aux2 = aux2/100;
  
  if((aux1 == 1)||(aux2 == 1)){
    aux1 = 0;
    aux2 = 0;
    if((aux1 == 0) || (aux2 == 0)){
      infrarrojo1 = "Normal";
      infrarrojo2 = "Normal";
    }
  }
  else{
    aux1 = 1;
    aux2 = 1;
    if((aux1 == 1) || (aux2 == 1)){
      infrarrojo1 = "Flama";
      infrarrojo2 = "Flama";
    }
  }
  
  gas = lecturaMQ2()*10000/255;
  
  if (((aux1 == HIGH) || (aux2 == HIGH)) && (temperatura >= 25) && (humedad <= 30) && (gas ))) {
    Serial.println("Las condiciones del ambiente aumentaron. Es posible que se este generando un incendio");
    Serial.print("IR1 = ");
    Serial.print(aux1);
    Serial.print("; IR2 = ");
    Serial.print( aux2);
    Serial.print("; Temperatura = ");
    Serial.println( temperatura);
    Serial.print("; Humedad = ");
    Serial.println( humedad);
    Serial.print("; Cantidad de gas/humo = ");
    Serial.println( gas);


    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);

  } else {
    digitalWrite(led, LOW);
  }
  delay(1000);
  
  i = 0;
  j = 0;
  k = 0;
  aux1 = 0;
  aux2 = 0;
}

int lecturaMQ2() {
  unsigned int valor0_mq = analogRead(sensor_mq); 
  unsigned int valor1_mq = map(valor0_mq, 0, 1023, 0, 255);
  
  return valor1_m; 

}