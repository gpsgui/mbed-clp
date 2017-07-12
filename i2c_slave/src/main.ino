#include<Wire.h>
#define reg0  0 //input
#define reg1  1 //input
#define reg2  2 //output
#define reg3  3 //output
#define reg4  4 //analog_out1
#define reg5  5 //analog_out2
#define reg6  6 //analog_out3
#define reg7  7 //analog_out4
#define reg8  8 //analog_in1
#define reg9  9 //analog_in2
#define reg10 10 //nao utilizado
#define reg11 11 //nao utilizado
#define reg12 12 //nao utilizado
int i, pino, i2c_adr = 9;
unsigned char reg_adr;
unsigned char reg[12] = {0,0,1,0,0,0,0,0,0,0,0,0};

void receiveEvent(int howMany) {
  unsigned char dado;
  reg_adr = Wire.read();       // recebe um byte que é o endereço do registrador
  if(Wire.available() == 1){    /// Operação de escrita
    dado =  Wire.read();         // recebendo o byte que é o valor a ser colocado no registrador de endereço reg_adr
    if(reg_adr >=2 && reg_adr <= 7)   // registradores que podem ser escritos
      reg[reg_adr] = dado;      // escrevendo o dado no registrador
  }
}
void requestEvent() {               // operação de leitura
  char valor = reg[reg_adr];
  Wire.write(valor);   // enviando a informação dentro do registrador desejado
}

void setup() {
  Wire.begin(i2c_adr);          // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // evento de escrita
  Wire.onRequest(requestEvent); // evento de leitura
  Serial.begin(9600);
  for(i =2; i<10;i++){  // inicializando pinos
    pinMode(i,OUTPUT);          // saidas analogicas (PWM): de 2 a 9 - TOT: 8
    if(i<=15)pinMode(i+8,INPUT);// entradas analogicas: de 10 a 15 - TOT: 6
    pinMode(i+22,INPUT);        // entradas digitais: de 22 a 29 - TOT: 8
    pinMode(i+38,OUTPUT);       // saidas digitais: 40 a 47 - TOT: 8
  }
}
void loop() { // atualizando os valores dos registradores
  // //----------- entradas digitais
  // pino = 22;
  // for(i = reg0; i <= reg1; i++){
  //   unsigned char estado = digitalRead(pino);
  //   if(estado != reg[i]&(2*(pino-22))) // se o pino tiver mudado de estado
  //     reg[i] = (reg[i]>(pino-22))^estado; // invertendo o bit = (pino - 22) do registrador de entradas digitais
  //   pino++;
  // }
  // //----------- saidas digitais
  // pino = 40;
  // for(i = reg2; i <= reg3; i++){
  //   if(pino == 40)
  //     digitalWrite(pino, reg[i]&1);   // bits
  //   else
  //     digitalWrite(pino, reg[i]&(2*(pino-40)));   // bits
  //   pino++;
  // }
  // //----------- saidas analogicas
  // pino = 2;
  // for(i = reg4; i <= reg7; i++){
  //   analogWrite(reg[i],pino);
  //   pino++;
  // }
  // //----------- entradas analogicas
  // pino = 10;
  // for(i = reg9; i <= reg9; i++){
  //   reg[i] = analogRead(pino);
  //   pino++;
  // }
  // delay(100);
}
