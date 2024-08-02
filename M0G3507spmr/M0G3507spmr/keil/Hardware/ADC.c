#include "ADC.h"
#include <ti/driverlib/dl_adc12.h>

bool adcFlag;
uint16_t adcValue;

void ADC_Init(void)
{
	NVIC_EnableIRQ(ADC0_INT_IRQn);
	//NVIC_EnableIRQ(ADC1_INT_IRQn);
	adcFlag = false;
}

void ADC_GetValue(void)
{
	adcFlag = false;
	DL_ADC12_startConversion(ADC0);//开始转换
	while(adcFlag == false);
	adcValue = DL_ADC12_getMemResult(ADC0,DL_ADC12_MEM_IDX_0);
	DL_ADC12_enableConversions(ADC0); //使能转换
}

void ADC0_IRQHandler (void)
{
	switch(DL_ADC12_getPendingInterrupt(ADC0))
	{
		case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
		{
				adcFlag = true;
		}
		break;
		
		default:
			break;
	}
}

