#include <mono.h>
#include <mbed.h>
#include <redpine_module.h>

class AppCtrl : public mono::IApplication {
    
    mbed::SPI rpSpi;
    mono::redpine::ModuleSPICommunication comm;
    
public:
    
    AppCtrl() : mono::IApplication(), rpSpi(RP_SPI_MOSI, RP_SPI_MISO, RP_SPI_CLK), comm(rpSpi, RP_SPI_CS,NC)
    {
        
    }
    
    void monoWakeFromReset()
    {
        
        
        int num = 0;
        while (1) {
            mono::defaultSerial.printf("hej med dig %i\n\r",num++);
            
            mbed::wait_ms(100);
        }
    }
    void monoWillGotoSleep()
    {
    }
    void monoWakeFromSleep()
    {}
};

int main()
{
    
    AppCtrl app;
    
    mono::IApplicationContext::Instance->setMonoApplication(&app);
    
	
	return 0;
}