/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <mono.h>
#include <redpine_module.h>
#include <mbed.h>


int main()
{
    mono::defaultSerial.printf("wake!\n\r");
    mbed::wait_ms(500);
    
    mono::defaultSerial.printf("Resetting module...\n\r");
    CyPins_SetPinDriveMode(RP_nRESET, CY_PINS_DM_OD_LO);
    CyPins_SetPin(RP_nRESET);
    CyPins_ClearPin(RP_nRESET);
    mono::defaultSerial.printf("pin cleared\n\r");
    mbed::wait_ms(500);
    CyPins_SetPin(RP_nRESET);
    mono::defaultSerial.printf("pin high again\n\r");
    mbed::wait_ms(500);
    
    
    mono::defaultSerial.printf("Setup wifi...\n\r");
    
    mono::redpine::Module::setupWifiOnly("ptype", "CAI7-huzzas");
    
    const char *domain = "trik.dk";
    mono::Debug << "DNS Lookup" << domain << "...";
    
    mono::redpine::DnsResolutionFrame dns(domain);
    dns.commit();
    
    if (!dns.respSuccess)
    {
        mono::Debug << "DNS lookup failed!";
        return 1;
    }
    
    char ipAddr[16];
    sprintf(ipAddr, "%i.%i.%i.%i",dns.resIpAddress[0],dns.resIpAddress[1],dns.resIpAddress[2],dns.resIpAddress[3]);
    
    mono::Debug << "Got resolved IP:" << ipAddr;
    
    mono::Debug << "Fetching website" << domain << "...";
    mono::redpine::HttpGetFrame get(domain, ipAddr, "/");
    get.commit();
    
    mono::Debug << "Done!";
    
	
	return 0;
}

/* [] END OF FILE */
