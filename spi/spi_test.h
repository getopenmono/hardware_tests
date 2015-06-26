//
//  spi_test.h
//  spiTest
//
//  Created by Kristoffer Andersen on 23/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#ifndef __spiTest__spi_test__
#define __spiTest__spi_test__

#include <mbed.h>

class SpiTest {
    mbed::Serial serial;
    mbed::SPI spi;
public:
    
    SpiTest();
    
    bool send(char data);
    
};

#endif /* defined(__spiTest__spi_test__) */
