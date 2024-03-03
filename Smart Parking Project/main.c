#include <avr/io.h>
#define  F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c_master.h"
#include "utility.h"
#include <stdio.h>
#include "OLED.h"
#include "HCSRO4.h"
#include "Servo.h"
#include "LDR.h"





int main(void) {
	DDRC |= (1 << PORTC2);
	 ADC_Init();
	initservo();
	initHC();
	initOLE();
   
   

	while (1) {
 uint16_t adcValue = ADC_Read(0); // Read ADC value from the LDR connected to PortF0
 volatile int u32Range;
 char rangeStr[20] = {'0'};

 SET_BIT(PORTE, TRIG_PIN);
 _delay_ms(15);
 CLEAR_BIT(PORTE, TRIG_PIN);
 

 u32Range = (int)(0.017 * gCounter);
 sprintf(rangeStr,"%dcm   ", u32Range);
 u8x8_DrawString_at(1, 1, "City Parking");
 

if (u32Range < 10)
{

	OCR1A = ICR1 - 500; // 90 degree
	 u8x8_DrawString_at(1, 2, "Gate Open");
	
	
}
else
{
	OCR1A = ICR1 - 1500; // 0 degree
	u8x8_DrawString_at(1, 2, "Gate Closed");
	
	
}
if (adcValue < 500) {
	PORTC |= (1 << PC2); // Turn on LED when it's dark
	} else {
	PORTC &= ~(1 << PC2); // Turn off LED when it's light
	
}
 if (!(PINB & (1 << TOUCH_SENSOR_PIN))) {
	 // Touch sensor is being touched
	 OCR1B = ICR1 - 1500; // 90 degree
	u8x8_DrawString_at(1, 3, "E Gate closed");
	 
 }
 else {
	 // let the servo go back and forth from 2ms to 1ms
	 
	 OCR1B = ICR1 - 500; // 0 degree, Timer 1
	  u8x8_DrawString_at(1, 3, "E Gate Open");
	  _delay_ms(3000);
	 
	 
	 
	 
	 
 }
      


}
	
}
