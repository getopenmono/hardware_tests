//
//  spi_test.cpp
//  spiTest
//
//  Created by Kristoffer Andersen on 23/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "spi_test.h"

SpiTest::SpiTest() : serial(USBRX,USBTX), spi(SPI_MOSI, SPI_MISO, SPI_CLK)
{
    serial.printf("SPI Test Initializing...\n");
    
}

bool SpiTest::send(char data)
{
    serial.printf("Sending byte to SPI bus: %x\n",data);
    
    int returnVal = spi.write(data);
    
    serial.printf("response value was: %x\n",returnVal);
    
    return true;
}
