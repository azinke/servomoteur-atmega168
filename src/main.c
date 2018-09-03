/**
    THIS CODE IS NOT WORKING YET

    TODO checkout timer 0 & 1 register configurations
**/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 8000000UL

#define WAIT 1000

volatile unsigned int sens = 0;	// Détermine le sens de rotation du servomoteur
						// 0: pour le sens ->  et 1 pour le sens <-

// La pause entre de sens de rotation sera de ~1s
volatile unsigned int compteur = 0;	// Pour mettre une pause entre les deux sens de rotation

volatile unsigned long rotation = 1500; // 1.5ms

volatile unsigned int _flag = 0;    // flag d'interruption

unsigned int _timer = 0;



int main(){
	/*
	 * La configuration par défaut à la reinitialisation du µC de l'horloge 
	 * est de 8MHz.
	 * Horloge utilisée: Internal RC oscillator
	 */

	/** Configuration de PIN **/
	DDRB = 0xFF; // Configurer le port B en sortie
	PORTB = 0x00;
	
	/** Configuration du timer 
	 * F_osc = 8 MHz
	 * Prescaler = 1024
	 * Timer_osc = 7812.5 Hz
	 * 0 - 255 : 256 pas
	 * 1 pas = 1/7812.5 MHz = 128µs
	 * 256 pas = 32768 µs = 32.768 ms
	 * 195 pas = 24960 µs = 24.960 ms ~ 25ms
	 *
	 */
	TCCR0A = 0x00;	// mode normal
	TCCR0B |= 0x05;	// clock/2014
	
	TCNT0 = 255 - 194;
	TIFR0 = 0x00;	// Effacer le registrer de notification des interruptions
	TIMSK0 |= 0x01;	// activer l'interruption de débordement

	sei();

	while(1){
	    if(_flag && (_timer >= WAIT)){
            if(sens == 0){
                if(rotation < 2000){ rotation += 10; }
                else{ sens = 1; }
            }else if(sens == 1){
	            if(rotation > 1500){ rotation -= 10; }
	            else{ sens = 0; }
            }
            _timer = 0;
        }
        
	    if(_flag){
	        PORTB |= 0x01;
	        _delay_us(rotation);
	        PORTB &= ~(1);
	        _flag = 0;
        }
        
        _delay_ms(1);
        _timer++;
	};

	return 0;
}

/*
void write(unsigned int value){
    if(_flag && (_timer >= 1000)){
        if(sens == 0){
            if(rotation < 2000){ rotation += 10; }
            else{ sens = 1; }
        }else if(sens == 1){
	        if(rotation > 1500){ rotation -= 10; }
	        else{ sens = 0; }
        }
        _timer = 0;
    }
}
*/

/*
 * Sous routine d'interruption
 *
 * TIMER0_OVF: Vecteur d'interruption du timer
 */
ISR (TIMER0_OVF_vect){
    _flag = 1;

	TCNT0 = 255 - 194; // Mettre à jour la valeur initial du counter du timer0
}

