/******************************
 * @file mcp3x08Spi.hpp
*******************************/

#ifndef MCP3X08SPI_H
    #define MCP3X08SPI_H

#include "mcp3008Spi.h"
#include <string>
#include <vector>
#include <cmath>     // pow

/***
 * @brief wrapper to communicate with microchip AD converters
 * @param  resolution resolution of AD converter; 8-bit, 10-bit, 12-bit
 ***/
class mcp3x08Spi : public mcp3008Spi {
private:

unsigned short const NUM_CH = 8;
unsigned char resolution;
unsigned short mask;
std::vector<unsigned short> raws;

public:
mcp3x08Spi();
mcp3x08Spi(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord, unsigned char resolution);
// void reOpen(std::string devspi,unsigned resolution);
/***
 * @fn mcp3x08Spi::getVal
 * get a value from the A/D converter at one selected channel
 * @param a2dChannel get data from the channel (0--7) at AD converter
 ***/
unsigned short getVal(unsigned char a2dChannel);
std::vector<unsigned short> getVals(size_t const m,size_t const n);
std::vector<unsigned short> readValsAll();

};
#endif
