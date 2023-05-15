#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define F_CU 16000000UL
#define UBRR_VAL 103
void init_uart(uint16_t ubrr);
void uart_tx(uint8_t data);

int main(void){
//interrupt 
MCUCR=(1<<ISC11)|(1<<ISC01);//falling edge
GICR=(1<<INT0)|(1<<INT0);//activation


 init_uart(UBRR_VAL);
 sei();
 uart_tx('%');
 while(1){

 }
}

ISR(INT0_vect){
uart_tx('1');
}

ISR(INT1_vect){
  uart_tx('0');
}




void init_uart(uint16_t ubrr){
  UBRRH=(uint8_t)(ubrr>>8); //casting 8 bits 
  UBRRL=(uint8_t) ubrr;
  UCSRB=(1<<RXEN|(1<<TXEN)); // to activate transmit and receiveing moods
  UCSRC= (1<<UCSZ0)|(1<<UCSZ1); //8 bit serial communication

}

void uart_tx(uint8_t data){

  while(!(UCSRA&(1<<UDRE)));  // UDRE is a flag if it is 1 it means the reg is empty but the condition says :loop as long as udr is not empty
  UDR=data;//udr holds the data to be transmitted
}


