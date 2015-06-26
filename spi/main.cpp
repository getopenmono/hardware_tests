//
//  main.c
//  screen_blink
//
//  Created by Kristoffer Andersen on 12/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include <mbed.h>

#include "spi_test.h"

int main()
{
    SpiTest spi;
    
    char number = 1;
    
    while(1)
    {
        spi.send(number++);
        mbed::wait_ms(1000);
    }
    
    
    
    return 0;
}