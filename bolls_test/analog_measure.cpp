//
//  analog_measure.cpp
//  bollsTest
//
//  Created by Kristoffer Andersen on 15/12/2015.
//  Copyright © 2015 your name. All rights reserved.
//

#include "analog_measure.h"


AnalogMeasure::AnalogMeasure() : sampler(300)
{
    value = 0x1234;
    sampler.setCallback<AnalogMeasure>(this, &AnalogMeasure::sampleTrigger);
    
    CyPins_SetPinDriveMode(ARD_D10_JC_RING1, CY_PINS_DM_ALG_HIZ);
}

void AnalogMeasure::Start()
{
    sampler.Start();
}

void AnalogMeasure::Stop()
{
    sampler.Stop();
}


uint16_t AnalogMeasure::sample()
{
    CY_SET_REG8(CYREG_PRT0_AMUX, 0x04);
    
    wait_us(100);
    uint32_t result = 0;
    
    for (int i=0; i<1024; i++) {
        
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        
        result += ADC_SAR_1_GetResult16();
    }
    
    CY_SET_REG8(CYREG_PRT0_AMUX, 0x00);
    
    return result / 1024;
}

void AnalogMeasure::sampleTrigger()
{
    uint16_t newVal = sample();
    
    if (newVal != value)
    {
        value = newVal;
        valueChangedHandler.call();
    }
}

uint16_t AnalogMeasure::Value() const
{
    return value;
}