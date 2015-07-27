
#include <project.h>
#include "redpine_test.h"
#include <SPI.h>
#include <Serial.h>
#include <consoles.h>

int main()
{
    mono::defaultSerial.printf("Redpine test start!\n");
    
    mbed::SPI spi(SPI_MOSI, SPI_MISO, SPI_CLK);
    
    
    RedpineTest redpine(spi);
    
    
    while(1);
	
	return 0;
}