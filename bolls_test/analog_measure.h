//
//  analog_measure.h
//  bollsTest
//
//  Created by Kristoffer Andersen on 15/12/2015.
//  Copyright © 2015 your name. All rights reserved.
//

#ifndef analog_measure_h
#define analog_measure_h

#include <mono.h>
#include <mbed.h>

class AnalogMeasure {
    
    mono::Timer sampler;
    mbed::FunctionPointer valueChangedHandler;
    
    uint16_t value;
    
public:
    
    AnalogMeasure();
    
    void Start();
    void Stop();
    
    
    
    uint16_t sample();
    
    void sampleTrigger();
    
    uint16_t Value() const;
    
    template <typename Owner>
    void setValueChangedCallback(Owner *obj, void(Owner::*memPtr)(void))
    {
        this->valueChangedHandler.attach(obj, memPtr);
    }
};


#endif /* analog_measure_h */
