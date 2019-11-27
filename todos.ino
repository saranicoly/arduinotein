#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
String botao1="";

void pagina(){
    String s="";
    s+= " <!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Testando</title><meta charset=\"utf-8\"><style type=\"text/css\"> ";
    s+= " .onoffswitch {position: relative; width: 90px;-webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;margin-left:70%;} ";
    s+= " .entradaonoff {display: none;}.texto-onoff {display: block; overflow: hidden; cursor: pointer;border: 2px solid #999999; border-radius: 20px;} ";
    s+= " .spanonoff {display: block; width: 200%; margin-left: -100%;transition: margin 0.3s ease-in 0s;} ";
    s+= " .spanonoff:before, .spanonoff:after {display: block; float: left; width: 50%; height: 30px; padding: 0; line-height: 30px; ";
    s+= " font-size: 14px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold;box-sizing: border-box;} ";
    s+= " .spanonoff:before {content: 'ON';padding-left: 10px;background-color: green; color: #FFFFFF;} ";
    s+= " .spanonoff:after {content: 'OFF';padding-right: 10px;background-color: red; color: #FFF;text-align: right;} ";
    s+= " .bola-onoff {display: block; width: 18px; margin: 6px;background: #FFFFFF;position: absolute; top: 0; bottom: 0; ";
    s+= " right: 56px;border: 2px solid #999999; border-radius: 20px;transition: all 0.3s ease-in 0s;} ";
    s+= " .entradaonoff:checked + .texto-onoff .spanonoff {margin-left: 0px;}.entradaonoff:checked + .texto-onoff .bola-onoff {right: 0px;} ";
    s+= " .teste{background-color: green;border: 2px solid black;}</style></head> ";
    s+= " <body><h1 class=\"teste\">Botão 1 - alarme</h1><div class='onoffswitch'><form action='/salvo1' method='POST' id='formu1'> ";
    s+= " <input onclick= enviar1() name='tes1' type='checkbox' class='entradaonoff' id='onoff' "+botao1+"><label class='texto-onoff' for='onoff'><span class='spanonoff'></span> ";
    s+= " <span class='bola-onoff'></span></label></form></div><br><h1 class=\"teste\">Botão 2</h1> ";
    s+= " <div class='onoffswitch'><form action='/salvo2' method='POST' id='formu2'><input name='tes2' type='checkbox' class='entradaonoff' id='onoff2' onclick= enviar2() "+botao2+" > ";
    s+= " <label class='texto-onoff' for='onoff2'><span class='spanonoff'></span> ";
    s+= " <span class='bola-onoff'></span></label></form></div>";
    s+= " <script type='text/javascript'>function enviar1() {document.getElementById('formu1').submit();}";
    s+= " function enviar2() {document.getElementById('formu2').submit();}";
    s+= "function enviar3() {document.getElementById('formu3').submit();} </script>";
    s+= "</body></html> ";
    server.send(200,"text/html",s);
}

void altera_botao1(){
    if (server.arg("tes1")=="on"){
        botao1="checked";
    }
    else{
        botao1="";
        funUltra();
    }
    pagina();
}
void altera_botao2(){
    if (server.arg("tes2")=="on"){
        botao2="checked";
        digitalWrite(pinBotao2,LOW);
    }
    else{
        botao2="";
        digitalWrite(pinBotao2,HIGH);
    }
    pagina();
}

void configurarAP(void) {
    WiFi.mode(WIFI_AP);
    delay(100);
    WiFi.softAP("Esp-septo", "12345678", 10);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig (IPAddress(192, 168, 0, 65), IPAddress (192, 168, 0, 1), subnet);
}

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
  attachInterrupt(digitalPinToInterrupt(micro), funMicro, RISING);
  
  //Sensor de luz com LDR
  pinMode(ledPin,OUTPUT); //define a porta 7 como saída
  Serial.begin(9600); //Inicia a comunicação serial

  //ultrassom
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  //aplicativo
  pinMode(pinBotao1,OUTPUT);
  pinMode(pinBotao2,OUTPUT);
  digitalWrite(pinBotao1,HIGH);
  digitalWrite(pinBotao2,HIGH);

  configurarAP();
  server.on("/",pagina);
  server.on("/salvo1",altera_botao1);
  server.on("/salvo2",altera_botao2);
  server.begin();
}


void loop() {
  //aplicativo
  server.handleClient();
  
  //piscina
  valor = digitalRead(micro);//Le o pino digital
  

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


}

void funUltra(){
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
if (safetyDistance <= 18){
  digitalWrite(buzzer, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
}
}

ICACHE_RAM_ATTR void funMicro(){
//  if (valor){
    Serial.println("SOM TESTANDO");
    estado=!estado;
    digitalWrite(led, estado);
//    delay(500);
//  }
}
