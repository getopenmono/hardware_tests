//
//  i2c_power_test.c
//  i2c_power_test
//
//  Created by Kristoffer Andersen on 16/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "i2c_power_test.h"

const char i2c_power_test_pwrAddr = 0x5A;

void i2c_power_test_init_i2c()
{
    I2C_Start();
}

char i2c_power_test_read_register(char regAddr)
{
    int success = I2C_MasterWriteBuf(i2c_power_test_pwrAddr, &regAddr, 1, I2C_MODE_COMPLETE_XFER);
    
    if (success != I2C_MSTR_NO_ERROR)
    {
        
    }
}
