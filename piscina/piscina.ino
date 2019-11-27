int led = D4; //Define led como sendo o pino 2
int micro = D2; //Define micro como sendo o pino 3

bool valor=false; //Variavel para leitura do microfone

// Variaveis para ajudar na captação do bater de palmas
bool estado=false;

void setup() {
  pinMode(led, OUTPUT); //Configura LED como saída
  pinMode(micro, INPUT); //Configura o microfone como entrada
 
  digitalWrite(led, LOW); //Começa com o LED apagado
}

void loop() {
  valor = digitalRead(micro);//Le o pino digital
  if (valor){
    estado=!estado;
    digitalWrite(led, estado);
    delay(500);
  }
 
}
