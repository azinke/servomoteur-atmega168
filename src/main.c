#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>


unsigned int sens = 0;	// Détermine le sens de rotation du servomoteur
						// 0: pour le sens ->  et 1 pour le sens <-

// La pause entre de sens de rotation sera de ~1s
unsigned int compteur = 0;	// Pour mettre une pause entre les deux sens de rotation

unsigned long rotation = 1500; // 1.5ms

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

	while(true){ };

	return 0;
}

/*
 *	En admettant une horloge de 8 MHz
 *	@fonction: delay d'une milliseconde
 */
void delay_us(unsigned long value){
	unsigned long i = 0;
	volatile unsigned int j = 0;
	for(i = 0; i < value; i++){
		for(j = 0; j < 8; j++){ }
	}
}

ISR (TIMER0_OVF_vect){
	PORTB |= 0x01;
	delay_ms(rotation);
	PORTB &= ~(1);
	if(sens = 0){
		if(rotation < 2000) rotation += 10;
		else {
			compteur++;
			if(compteur >= 41) { compteur = 0; sens = 1; }
		}
	}else if(sens = 1){
		if(rotation > 1500) rotation -= 10;
		else {
			compteur++;
			if(compteur >= 41){ compteur = 0; sens = 0; }
		}
	}
}

