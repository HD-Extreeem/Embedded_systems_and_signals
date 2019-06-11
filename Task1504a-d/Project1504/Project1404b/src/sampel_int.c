/*
 * sampel_int.c
 *
 * Created: 2013-12-10 12:32:30
 *  Author: Tommy
 *  Modified by: Hadi & Leonard
 */ 

#include <asf.h>
#include "sampel_int.h"

#define M 4
#define N 4


//void TCO_Handler(void);

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	static float xbuff[M+1] = {0};
	static float b[M+1]={
			0.01488697472657, -0.02695899404537,  0.03705935223574, -0.02695899404537,
			0.01488697472657
			};
	/*static float b[M+1]=
	{

		0.01080096024942, 0.009150882313605, 0.007511904549456,0.0005792030769843,

		-0.01127376170725, -0.02515190942132, -0.03590095692545, -0.03739762488425,

		-0.02453046490484,  0.00471963858602,  0.04788555515624,  0.09797523269544,

		0.1449637668957,   0.1784338566514,   0.1905580972352,   0.1784338566514,

		0.1449637668957,  0.09797523269544,  0.04788555515624,  0.00471963858602,

		-0.02453046490484, -0.03739762488425, -0.03590095692545, -0.02515190942132,

		-0.01127376170725,0.0005792030769843, 0.007511904549456, 0.009150882313605,

		0.01080096024942
	};*/

	static float ybuff[N+1]= {0};
	static float a[N+1]= {
			-1,   3.338693232847,    -4.401916486793,   2.691625646031,
			-0.6428936122854

			};
		
	volatile uint32_t ul_dummy;
	uint32_t invalue, outvalue;
	float summa=0;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	ioport_set_pin_level(CHECK_PIN,HIGH);		//put test pin HIGH 
	
	adc_start(ADC); 
	while((adc_get_status(ADC) & 0x1<<24)==0);  //Wait until DRDY get high

	invalue=adc_get_latest_value(ADC);			//get input value
	
	
	//---------------FIR-filter koden här--------------------
	//for (uint32_t k=M+1;k>0;k--)
	for (uint32_t k=M;k>=1;k--)
	{
		xbuff[k]=xbuff[k-1];
	}
	
	xbuff[0]=(float)invalue;
	
	for (uint32_t x=0;x<M+1;x++)
	{
		summa+=b[x] * xbuff[x];
	}
	
	//outvalue = (uint32_t)(value);
	//--------------------------------------------------------
	
	
	//---------------IIR-filter koden här--------------------
	
	
	
	for (uint32_t x=1;x<N+1;x++)
	{
		summa+= a[x] * ybuff[x-1];
	}
	
	for (uint32_t k=N-1;k>=1;k--)
	{
		ybuff[k]=ybuff[k-1];
	}
	ybuff[0]=summa;
	
	
	outvalue = (uint32_t)(summa);
	
	//--------------------------------------------------------
	
	//************ Lab2
	// Here should signal processing code be placed
	//static uint16_t buffer[10000]={0};
	//static uint32_t k=0;
	//buffer[k]=invalue;
	//k++;
	//if (k==10000)
	//{
		//k=0;
	//}
	//outvalue=buffer[k]+invalue;
	//*********** lab2
		
	dacc_write_conversion_data(DACC,outvalue);	//send output value to DAC
	
	ioport_set_pin_level(CHECK_PIN,LOW);		//put test pin LOW
	
}

