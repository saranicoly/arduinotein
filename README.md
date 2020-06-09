# arduinotein

Código para ligar led ao bater palmas (usando microfone), ligar led usando sensor de luminosidade LDR e alarme usando sensor ultrassom e buzzer, com arduíno (ESP8266).

arquivo todos.ino => contém todas as funcionalidades e o aplicativo.
codigowifi.ino => contém um código para servir de base para criação do wifi e ligar e desligar LED do ESP (senha: 12345678; acessar pelo ip 192.168.0.65).
LDR, Piscina e sensor_de_ultrassom => código para cada uma das funcionalidades separadamente.
todosv2.ino => código com todas as funcionalidades juntas, sem o aplicativo, como segurança caso o aquivo todos.ino dê problema.
