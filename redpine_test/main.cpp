
#include <project.h>
#include "redpine_test.h"
#include <SPI.h>


int main()
{
    mbed::SPI spi(SPI_MOSI, SPI_MISO, SPI_CLK);
    
    RedpineTest redpine(spi);
    
    
    while(1);
	
	return 0;
}