//
//  redpine_test.cpp
//  redpineTest
//
//  Created by Kristoffer Andersen on 23/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "redpine_test.h"
#include <PinNames.h>

RedpineTest::RedpineTest(mbed::SPI &spi) : comm(spi, NC)
{
    mono::redpine::Module::initialize(&comm);
    
}

bool RedpineTest::test()
{
    return true;
}