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
unsigned char reg[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void receiveEvent(int howMany) { // leitura
  unsigned char dado;
  reg_adr = Wire.read();       // recebe um byte que é o endereço do registrador
  if(Wire.available() == 1){    /// Operação de escrita
    dado =  Wire.read();         // recebendo o byte que é o valor a ser colocado no registrador de endereço reg_adr
    //if(reg_adr >=2 && reg_adr <= 7)   // registradores que podem ser escritos
    reg[reg_adr] = dado;      // escrevendo o dado no registrador
    Serial.print("escrita : adr : ");
    Serial.print(reg_adr);
    Serial.print("\t valor : ");
    Serial.println(dado);
  }
}
void requestEvent() {               // operação de escrita
  unsigned char valor = reg[reg_adr];
  Serial.print("leitura : adr : ");
  Serial.print(reg_adr);
  Serial.print("\t valor : ");
  Serial.println(valor);
  Wire.write(valor);   // enviando a informação dentro do registrador desejado
}

void setup() {
  Wire.begin(i2c_adr);          // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // evento de escrita
  Wire.onRequest(requestEvent); // evento de leitura
  Serial.begin(9600);
  for(i=2; i<10;i++){  // inicializando pinos
    pinMode(i,OUTPUT);          // saidas analogicas (PWM): de 2 a 9 - TOT: 8
    if(i<9)pinMode(54 + i-2,INPUT);// entradas analogicas: de A0 a A6 - TOT: 6
    pinMode(i+20,INPUT);        // entradas digitais: de 22 a 29 - TOT: 8
    //pinMode(i+40,OUTPUT);       // saidas digitais: 42 a 49 - TOT: 8
  }
  DDRL = 255;   // definindo o PORTL como saidas
}
void loop() { // atualizando os valores dos registradores
  //----------- entradas digitais
  reg[reg0] = PINA;    // copiando os valores do registrador de entradas 'A' para o registrador usado na com. i2c
  // falta fazer para reg1
  //----------- saidas digitais
  PORTL = reg[reg2];   // copiando os valores do registrador da com. i2c para o registrador de saidas 'L'
  // falta fazer para reg3
  //----------- saidas analogicas
  pino = 2;
  for(i = reg4; i <= reg7; i++){
    analogWrite(reg[i],pino);
    pino++;
  }
  //----------- entradas analogicas
  pino = 10;
  for(i = reg9; i <= reg9; i++){
    reg[i] = char(map(analogRead(pino), 0 , 1023, 0, 255));   // convertendo o valor de 0 - 1023
    pino++;
  }
}
