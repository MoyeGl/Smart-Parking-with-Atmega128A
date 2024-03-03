/*
 * HCSRO4.h
 *
 * Created: 2024-01-06 5:51:48 PM
 *  Author: Glein
 */ 


#ifndef HCSRO4_H_
#define HCSRO4_H_

#define ECHO_PIN PORTE7
#define TRIG_PIN PORTE3


volatile uint8_t gFalg = 0x00;
volatile uint32_t gCounter = 0x00;

ISR(INT7_vect)
{
	gFalg++;
	
	// Check if it's the rising edge
	if (gFalg == 1)
	{
		// Start Timer 3 by setting the prescaler to 1 (CS30 = 1)
		SET_BIT(TCCR3B, CS30);
		// Reset Counter
		gCounter = 0;
		// Set Interrupt for the falling edge
		CLEAR_BIT(EICRB, ISC70);
		SET_BIT(EICRB, ISC71);
	}
	// Falling edge
	else
	{
		// Stop Timer 3 by setting CS30 to ZERO
		CLEAR_BIT(TCCR3B, CS30);
		// Get the counted value, Reset counter and flag to Zero.
		gCounter = TCNT3;
		gFalg = 0;
		TCNT3 = 0;
		// Set Interrupt for the rising edge.
		SET_BIT(EICRB, ISC70);
		SET_BIT(EICRB, ISC71);
	}
}

void initHC()
{
	// Configure Timer 3
	// Use the clock frequency of the uC 1MHz, but for now, the timer must be stopped.
	CLEAR_BIT(TCCR3B, CS30);
	CLEAR_BIT(TCCR3B, CS31);
	CLEAR_BIT(TCCR3B, CS32);

	// Configure the Ultrasonic Pins
	// Configure PE7 as input, enable Pull-up resistor, and PE3 as output.
	CLEAR_BIT(DDRE, ECHO_PIN);
	SET_BIT(PORTE, ECHO_PIN);
	SET_BIT(DDRE, TRIG_PIN);

	// Configure the external interrupt on the input Echo Pin PE7 (INT7) -> Enable INT7
	SET_BIT(EIMSK, INT7);

	// Set sense to the Rising edge:
	SET_BIT(EICRB, ISC70);
	SET_BIT(EICRB, ISC71);

	// Enable global interrupt
	sei();
}



#endif /* HCSRO4_H_ */