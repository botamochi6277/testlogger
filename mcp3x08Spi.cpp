#include "mcp3x08Spi.hpp"

mcp3x08Spi::mcp3x08Spi(){
  this->resolution = 12;
  this->mask = ( (short)(std::pow(2,resolution) - 1) << 8 );
  std::vector<unsigned short> initial(this->NUM_CH,0);
  this->raws = initial;
}


mcp3x08Spi::mcp3x08Spi(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord, unsigned char resolution)
 : mcp3008Spi(devspi,spiMode,spiSpeed,spibitsPerWord){
  this->resolution = resolution;
  this->mask = ( (unsigned short)(std::pow(2,resolution) - 1) << 8 );
  std::vector<unsigned short> initial(this->NUM_CH,0);
  this->raws = initial;

}
/*
void mcp3x08Spi::reOpen(std::string devspi,unsigned resolution){

  this->spiClose();
  this->resolution = resolution;
  this->mask = ( (short)(std::pow(2,resolution) - 1) << 8 );
  this->spiOpen(devspi);
}
*/

/***
 * @fn mcp3x08Spi::getVal
 * get a value from the A/D converter at one selected channel
 * @param a2dChannel get data from the channel (0--7) at AD converter
 ***/
unsigned short mcp3x08Spi::getVal(unsigned char a2dChannel){
        unsigned char data[3];
        unsigned int d = (0b11 << (5 + this->resolution)); // start bit and SGL/DIFF = 1
        d |= ( ((a2dChannel & 7) << (2 + this->resolution)));
        data[0] = d >> 16;
        data[1] = d >> 8;
        data[2] = 0;
        this->spiWriteRead(data, sizeof(data));
        this->raws.at(a2dChannel) = (data[1]<< 8 & this->mask) | (data[2] & 0xff); //merge data[1] & data[2] to get result
        return(this->raws.at(a2dChannel));
}

std::vector<unsigned short> mcp3x08Spi::getVals(size_t const m ,size_t const n ){
  for (size_t ch = m; ch < n+1; ch++) {
    this->getVal(ch);
  }
  return (this->raws);
}

std::vector<unsigned short> mcp3x08Spi::readValsAll(){
  return (this->raws);
}
