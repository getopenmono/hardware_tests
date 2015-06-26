//
//  i2c_power_test.h
//  i2c_power_test
//
//  Created by Kristoffer Andersen on 16/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#ifndef __i2c_power_test__i2c_power_test__
#define __i2c_power_test__i2c_power_test__

#include <project.h>

static const char i2c_power_test_pwrAddr;

/**
 * Setup and init I2C comm
 */
void i2c_power_test_init_i2c();


char i2c_power_test_read_register();


#endif /* defined(__i2c_power_test__i2c_power_test__) */
