/*
 * Touchsensor.h
 *
 * Created: 2024-01-05 12:50:53 PM
 *  Author: Glein
 */ 


#ifndef TOUCHSENSOR_H_
#define TOUCHSENSOR_H_
#define TOUCH_SENSOR_PIN PB0

void initservo() {
	DDRB |= (1 << PORTB5) | (1 << PORTB6); // Set PB5 and PB6 as outputs for Timer 1
	
	// set waveform generation mode Timer 1
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	

	// set the top value
	ICR1 = 19999; // Timer 1


	// set the pre-scaler which is no prescaling:
	TCCR1B |= (1 << CS10); // Timer 1
	


	// set Compare Output Mode Timer 1
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	TCCR1A |= (1 << COM1B1) | (1 << COM1B0); // Set COM1B for PB6


	// set the current servo position (1.5ms pulse, middle position)
	OCR1A = ICR1 - 1500; // Timer 1, PB5
	OCR1B = ICR1 - 1500; // Timer 1, PB6
	
}






#endif /* TOUCHSENSOR_H_ */

