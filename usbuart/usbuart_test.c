//
//  usbuart_test.cpp
//  usbtest
//
//  Created by Kristoffer Andersen on 22/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "usbuart_test.h"

void usbuart_test_init()
{
    
}

void usbuart_test_write(const char *str)
{
    USBUART_PutString(str);
}