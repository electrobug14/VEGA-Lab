#include "stdlib.h"
#include "spi.h"
#include "at25512.h"

/**
 @brief AT25512 eeprom demo.
 @details Read and write  AT25512 eeprom.
 @param[in] No input parameter. 
 @param[Out] No output parameter. 
*/
void main()
{
	static char writeData[256], readData[256];

	printf("+------[ AT25512  Demo ]------+\n");
	printf("|                               |\n");
	printf("|     AT25512  ----> SPI0     |\n");
	printf("|                               |\n");
	printf("+-------------------------------+\n\n");

	at25512Begin(MDP_SPI_0);

	at25512ReadEeprom(readData, 128, 0x0); // read first 512 bytes of data.
	printf("\n AT25512 read data before writing:");
	for (int i = 0; i < 128; i++)
	{
		if (i % 32 == 0)
			printf("\n");
		printf("%02x ", readData[i]);
	}
	printf("\n");
	// generating data.
	for (int i = 0; i < 128; i++)
	{
		writeData[i] = i;
	}
	at25512WriteEeprom(writeData, 128, 0x0);	 // writing data in page 1. Max length for write is 128 bytes (page size).
	//at25sf161WriteEeprom(writeData, 127, 0x100); // writing data in page 2.

	at25512ReadEeprom(readData, 128, 0x0); // read first 128 bytes of data.
	printf("\n AT25512 read data after writing:");
	for (int i = 0; i < 128; i++)
	{
		if (i % 32 == 0)
			printf("\n");
		printf("%02x ", readData[i]);
	}
	printf("\n");


	while (1)
		;
}
