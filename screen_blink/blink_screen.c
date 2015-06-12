//
//  blink_screen.c
//  screen_blink
//
//  Created by Kristoffer Andersen on 12/06/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "blink_screen.h"


void blinkScreenTest()
{
    for (int i=0; i<4; i++) {
        TFT_LED_PWR_Write(1);
        CyDelay(100);
        
        TFT_LED_PWR_Write(0);
        CyDelay(400);
    }
}