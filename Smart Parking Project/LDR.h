/*
 * LDR.h
 *
 * Created: 2024-01-05 12:30:14 PM
 *  Author: Glein
 */ 


#ifndef LDR_H_
#define LDR_H_

void ADC_Init() {
	
	ADMUX = (1 << REFS0); // Reference voltage at AVCC
	ADCSRA = (1 << ADEN) |  (1 << ADPS1) | (1 << ADPS0| 1 << ADSC); // Enable ADC, set prescaler
	while (ADCSRA & (1 << ADSC)); // Wait for conversion to finish
	ADCSRA |= (1 << ADIF); 
 
}

// Function to read ADC value
uint16_t ADC_Read(uint8_t u8ADC_channel) {
	
	ADCSRA |= (1 << ADSC); // Start ADC conversion
	while (ADCSRA & (1 << ADSC)); 
	ADCSRA |= (1 << ADIF);
	return ADC;
}





#endif /* LDR_H_ */