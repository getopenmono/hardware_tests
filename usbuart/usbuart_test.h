//
//  usbuart_test.h
//  usbtest
//
//  Created by Kristoffer Andersen on 22/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#ifndef __usbtest__usbuart_test__
#define __usbtest__usbuart_test__

#include <project.h>


/** Setup the USB device and enable global interrupts */
void usbuart_test_init();

/** Write a string to the UART */
void usbuart_test_write(const char *str);


#endif /* defined(__usbtest__usbuart_test__) */
