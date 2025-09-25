#include <avr/interrupt.h>
#include <Arduino.h>

unsigned char cnt = 0; // contador que define a parada por interrupcao do timer
unsigned char valor, modo; // A variavel "valor" sera usada para 
unsigned int tempo = 0; // Intervalo de tempo para liberar a racao 
bool racao; // Variavel que decide se liberara a racao 

void setup() {
  // put your setup code here, to run once:

  // Port B initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  PORTB = 0x00; 
  DDRB = 0x01;  // PB0 = saida pro alimentador
  TCCR0 = 0X05; // Interrupcao por comparacao
  OCR0A = ; // Valor a ser comparado
  TIMSK = 0x00; //

}

ISR(TIMO_COMP) // Funcao para interrupca por comparacao
{
      TCNT0 = 0;
      if(++cnt == tempo)
      {
          PORTB.0 = 1;
          if(racao == "False")
          {
            delay(20); // Valor em segundos em que o sistema ira servir a comida
          }
          elseif(racao == "True")
          {
            delay(1.5); // Valor em segundos em que o sistema ira servir a comida
          }
          PORTB.0 = 0;
          tempo = 0;
      }

}

#asm("sei") // Habilitando as interrupcoes 

void loop() {
  // put your main code here, to run repeatedly:
  
  if(tempo == 0)
  { 

    if(PINB.1 == 1)
    {


    }elseif(PINB.3 == 1)
    {
        

    }

  }
