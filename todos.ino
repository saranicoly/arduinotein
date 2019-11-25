//piscina
int led = D4; //Define led como sendo o pino 2
int micro = D2; //Define micro como sendo o pino 3
bool valor=false; //Variavel para leitura do microfone
bool estado=false;  // Variável para ajudar na captação do bater de palmas

//Sensor de luz com LDR
int ledPin = D3; //Led no pino D3
int ldrPin = A0; //LDR no pino analógico 0
int ldrValor = 0; //Valor lido do LDR

//ultrassom
const int trigPin = 16;
const int echoPin = 5;
const int buzzer = 14;

long duration;
int distance;
int safetyDistance;
 

void setup() {
  // piscina
  pinMode(led, OUTPUT); //Configura LED como saída
  pinMode(micro, INPUT); //Configura o microfone como entrada
  digitalWrite(led, LOW); //Começa com o LED apagado
  
  //Sensor de luz com LDR
  pinMode(ledPin,OUTPUT); //define a porta 7 como saída
  Serial.begin(9600); //Inicia a comunicação serial

  //ultrassom
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}


void loop() {
  //piscina
  valor = digitalRead(micro);//Le o pino digital
  if (valor){
    estado=!estado;
    digitalWrite(led, estado);
    delay(500);
  }

  //Sensor de luz com LDR
  ///ler o valor do LDR
 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 
 //se o valor lido for maior que 600, liga o led
 if (ldrValor>= 600) digitalWrite(ledPin,HIGH);
 // se não, apaga o led
 else digitalWrite(ledPin,LOW);
 
 //imprime o valor lido do LDR no monitor serial
 Serial.println(ldrValor);
 //delay(100);

 //ultrassom
 // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= (duration*0.034)/2;

safetyDistance = distance;
if (safetyDistance <= 16){
  digitalWrite(buzzer, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
}

// Prints the distance on the Serial Monitor
Serial.print("Distancia: ");
Serial.println(distance);
}
