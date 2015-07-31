//
//  app_controller.cpp
//  wifiTest
//
//  Created by Kristoffer Andersen on 31/07/15.
//  Copyright (c) 2015 Monolit ApS. All rights reserved.
//

#include "app_controller.h"

mono::ui::ConsoleView<176, 220> AppController::uicon;


AppController::AppController() : mono::IApplication(), redpineSpi(RP_SPI_MOSI, RP_SPI_MISO, RP_SPI_CLK),modCom(redpineSpi, RP_SPI_CS, NC)
{
    
}

void AppController::monoWakeFromReset()
{
    mono::defaultSerial.printf(""); //force enumeration
    
    //    mbed::wait_ms(500);
    //
    //    uicon.Write("wake!\n\r");
    
    mono::defaultSerial.printf("Resetting module...\n\r");
    
    
    CyPins_SetPinDriveMode(RP_nRESET, CY_PINS_DM_OD_LO);
    CyPins_SetPin(RP_nRESET);
    CyPins_ClearPin(RP_nRESET);
    
    mono::defaultSerial.printf("pin cleared\n\r");
    mbed::wait_ms(500);
    
    CyPins_SetPin(RP_nRESET);
    mono::defaultSerial.printf("pin high again\n\r");
    mbed::wait_ms(500);
    
    mono::defaultSerial.printf("init module...\n\r");
    
    mono::redpine::Module::initialize(&modCom);
    
    mono::defaultSerial.printf("Setup wifi...\n\r");
    
    mono::redpine::Module::setupWifiOnly("ptype", "CAI7-huzzas");
    
    const char *domain = "trik.dk";
    mono::defaultSerial.printf("DNS Lookup %s...\n\r",domain);
    mono::redpine::DnsResolutionFrame dns(domain);
    dns.commit();
    
    if (!dns.respSuccess)
    {
        mono::defaultSerial.printf("DNS lookup failed!");
        return;
    }
    
    char ipAddr[16];
    sprintf(ipAddr, "%i.%i.%i.%i",dns.resIpAddress[0],dns.resIpAddress[1],dns.resIpAddress[2],dns.resIpAddress[3]);
    
    mono::defaultSerial.printf("Got resolved IP: %s\n\r",ipAddr);
    
    mono::defaultSerial.printf("Fetching website %s...\n\r",domain);
    mono::redpine::HttpGetFrame get(domain, ipAddr, "/");
    get.commit();
    
    mono::defaultSerial.printf("Done!\n\r");
}


void AppController::monoWillGotoSleep()
{
    
}

void AppController::monoWakeFromSleep()
{
    
}