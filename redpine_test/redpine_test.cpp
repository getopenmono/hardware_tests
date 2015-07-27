//
//  redpine_test.cpp
//  redpineTest
//
//  Created by Kristoffer Andersen on 23/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "redpine_test.h"
#include <PinNames.h>
#include <Serial.h>
#include <consoles.h>

RedpineTest::RedpineTest(mbed::SPI &spi) : comm(spi, NC)
{
    mono::Debug << "Resetting module...";
    CyPins_ClearPin(CYREG_PRT5_PC0); // set module into reset
    mbed::wait_ms(500);
    CyPins_SetPin(CYREG_PRT5_PC0); // take out of reset
    mbed::wait_ms(100);
    mono::Debug << "Done, initializing...";
    mono::redpine::Module::initialize(&comm);
    mono::Debug << "Done";
}

bool RedpineTest::test()
{
    return true;
}