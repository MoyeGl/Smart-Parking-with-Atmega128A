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
	// set pin as output.
	DDRB = (1 << PORTB5); // Timer 1, Channel A (Pin PB5)
	
	
	// set the waveform generation mode Timer 1
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	
	// set the waveform generation mode Timer 3 Channel A
	TCCR3A |= (1 << WGM31);
	TCCR3B |= (1 << WGM32) | (1 << WGM33);

	// set the top value
	ICR1 = 19999; // Timer 1
	
	// set the pre-scaler which is no prescaling:
	TCCR1B |= (1 << CS10); // Timer 1
	
	
	// set Compare Output Mode Timer 1
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	// set Compare Output Mode Timer 3
	TCCR3A |= (1 << COM3A1) | (1 << COM3A0);
	// set the current servo position (1.5ms pulse, middle position)
	OCR1A = ICR1 - 1500; // Timer 1
	
}





#endif /* TOUCHSENSOR_H_ */

