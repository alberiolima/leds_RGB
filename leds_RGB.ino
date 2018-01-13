#include <SoftwareSerial.h> //Biblioteca de comunicação serial virtual

//Definição dos pinos dos LEDs
#define pinLED_R  3 
#define pinLED_G  9
#define pinLED_B  6

#define tempoIntervalo 6 //Intervalo entre mudança de luminosidade ( 6 e 1 é o mesmo que 30ms que estava sendo usando )

boolean fadeLED_R = false;     
byte posicaoLED_R = 0;         
boolean direcaoLED_R = false;  

boolean fadeLED_G = false;     
byte posicaoLED_G = 0;         
boolean direcaoLED_G = false;  

boolean fadeLED_B = false;     
byte posicaoLED_B = 0;         
boolean direcaoLED_B = false;  

SoftwareSerial bluetooth(10, 11);
unsigned long tempoProximo = 0;

void setup() {
  bluetooth.begin(9600); //Inicia comunicação bom o módulo bluetooth
  
  Serial.begin(9600); //Inicia comunicação com a porta serialdo Arduino (HardSerial)
  Serial.println( "Controle de LEDs RGB" );
  
  //Define pinos dos LEDs como SAIDA
  pinMode(pinLED_R, OUTPUT);
  pinMode(pinLED_G, OUTPUT);
  pinMode(pinLED_B, OUTPUT);
  
  pinMode( 2, OUTPUT );
  digitalWrite( 2,LOW );
}

void loop() {
  if ( millis() > tempoProximo) {
    tempoProximo += tempoIntervalo;
    //Operação do LED_R
    if (fadeLED_R ) {
      if ( direcaoLED_R ) {
        posicaoLED_R ++;
      } else { 
        posicaoLED_R --;
      }

      analogWrite( pinLED_R, posicaoLED_R );
            
      //Inverta a direção do fade
      if (( posicaoLED_R == 255 )||(posicaoLED_R == 0)){
        direcaoLED_R = !direcaoLED_R;
      }
    }

    //Operação do LED_G
    if (fadeLED_G ) {
      
    }

    //Operação do LED_B
    if (fadeLED_B ) {
      
    }
  }

  //Recebe comandos pela serial do arduino ou pela serial do bluetooth
  if (( bluetooth.available() > 0 )||(Serial.available()>0)) {
    byte cByteRecebido;
    if ( bluetooth.available() > 0 ) {
      cByteRecebido = bluetooth.read();
    } else if ((Serial.available()>0)){
      cByteRecebido = Serial.read();
    }
    
    if ( cByteRecebido == '0' ) { //Liga ou Desliga fade LED_R
      fadeLED_R = !fadeLED_R;
      direcaoLED_R = true;
      if ( fadeLED_R ) {
        Serial.println( "Acionado LED_R" );
        posicaoLED_R = 0;
      } else {
        analogWrite( pinLED_R, 0 );
      }      
    } else if (cByteRecebido == '1') {
      //Aqui instruções para a outra cor
    } else if (cByteRecebido == '2') {
      //Aqui instruções para a outra cor
    }
  }    
}
