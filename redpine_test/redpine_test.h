//
//  redpine_test.h
//  redpineTest
//
//  Created by Kristoffer Andersen on 23/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#ifndef __redpineTest__redpine_test__
#define __redpineTest__redpine_test__

extern "C" {
#include <project.h>
}
#include <redpine_module.h>
#include <SPI.h>
#include <mbed.h>
#include <consoles.h>

class RedpineTest {
    
    mono::redpine::ModuleSPICommunication comm;
    
public:
    
    RedpineTest(mbed::SPI &spi);
    
    bool test();
    
};

#endif /* defined(__redpineTest__redpine_test__) */
