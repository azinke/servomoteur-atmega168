#include <avr/io.h>
#include<util/delay.h>

int main(void)
   {
   DDRB = 0xFF;
   TCCR1A |= 1<<WGM11 | 1<<COM1A1 ;
   TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10 | 1<<CS11;
   
   TCNT1 = 0x00;
   ICR1 = 2499;

  while (1){
     OCR1A = 65;
     _delay_ms(1500);
     OCR1A = 175;
     _delay_ms(1500);
     OCR1A= 300;
     _delay_ms(1500);
  }
}
