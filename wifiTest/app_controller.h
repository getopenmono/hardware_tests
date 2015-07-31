//
//  app_controller.h
//  wifiTest
//
//  Created by Kristoffer Andersen on 31/07/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#ifndef __wifiTest__app_controller__
#define __wifiTest__app_controller__

#include <stdio.h>
#include <mono.h>
#include <redpine_module.h>
#include <mbed.h>

class AppController : public mono::IApplication {
    
public:
    
    static mono::ui::ConsoleView<176, 220> uicon;
    mbed::SPI redpineSpi;
    mono::redpine::ModuleSPICommunication modCom;
    
    AppController();
    
    void monoWakeFromReset();
    
    void monoWakeFromSleep();
    
    void monoWillGotoSleep();
};


#endif /* defined(__wifiTest__app_controller__) */
