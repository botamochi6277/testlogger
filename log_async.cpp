/******************************
 * log_async.cpp
 * Program to get data from mcp3x08 chips and write the data to a text file
 *******************************/

#include "mcp3x08Spi.hpp"
#include <cmath>     // pow
#include <fstream>   // ifstream, ofstream
#include <ctime>     // for time (day)
#include <iostream>
#include <vector>
#include <iomanip>   // to conver time class to ascii text
#include <chrono> //for wait
#include <thread> //for wait
#include <future>


unsigned long const TIME_RUN = 1e3; // [ms]

/***
 * @fn wait
 * @brief cross platform wait function based on chrono
 * @a2dChannel     get data from the channel (0--7) at AD converter
 ***/
bool wait( const std::string& typ, const std::chrono::system_clock::time_point& strt, const unsigned int& t ){
        if( typ == "nano" ) std::this_thread::sleep_until( strt + std::chrono::nanoseconds( t ) );
        else if( typ == "micro" ) std::this_thread::sleep_until( strt + std::chrono::microseconds( t ) );
        else if( typ == "milli" ) std::this_thread::sleep_until( strt + std::chrono::milliseconds( t ) );
        else if( typ == "sec" ) std::this_thread::sleep_until( strt + std::chrono::seconds( t ) );
        else if( typ == "min" ) std::this_thread::sleep_until( strt + std::chrono::minutes( t ) );
        else if( typ == "hour" ) std::this_thread::sleep_until( strt + std::chrono::hours( t ) );
        else return false;

        return true;
}


// 本当はいちいちofstreamを作りたくないが，asyncは参照渡しができない一方で，ofstreamは参照渡ししかできないための苦肉の策
/***
 * @fn logging
 * @brief write data in txt file
 * @filename     filename
 * @data vactor of written data
 ***/
void logging(std::string filename, std::vector<unsigned short> data){
  std::ofstream writing_file;
  writing_file.open(filename, std::ios::app);
  for (size_t i = 0; i < data.size(); i++) {
    writing_file << data.at(i)<< "\t" ;
  }
  writing_file << std::endl;
}

void control(){
  std::cout << "Execute " << __PRETTY_FUNCTION__ << std::endl;
  mcp3x08Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8, 12);

  char cfilename[64];
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  std::strftime(cfilename, 64, "log/%Y%m%d-%H%M%S.txt", std::localtime(&start_time));
  std::string filename = cfilename;
  std::cout << "create log file: " << filename << std::endl;
  std::ofstream writing_file;
  writing_file.open(filename, std::ios::out);

  // Write header
  writing_file << "time";
  for (size_t i = 0; i < 8; i++) {
    writing_file << "\t" << "val" <<i ;
  }
  writing_file << std::endl;
  writing_file.close();

  // Main loop
  auto tPrev = std::chrono::system_clock::now();
  for(;;) {
    auto tNow = std::chrono::system_clock::now();
    unsigned long tMilli = std::chrono::duration_cast<std::chrono::milliseconds>(tNow - start).count();
    if (tMilli > TIME_RUN) {
      break;
    }
    std::vector<unsigned short> vals = a2d.getVals(0,7); // ch 0--7
    vals.insert(vals.begin(),tMilli);
    /** display
    std::cout << "vals: ";
    for (auto i = vals.begin(); i != vals.end(); ++i){
      std::cout << *i << ' ';
    }
    std::cout << std::endl;
    */
    std::future<void> f1 = std::async(std::launch::async,logging,filename,vals); // async write
    tPrev = tNow;
    wait("milli", tNow, 1.0);
  }
  std::cout << __PRETTY_FUNCTION__ << " closed" <<std::endl;
}

int main(void)
{

        std::cout << "Hello, My Source is " << __FILE__ << std::endl; // this filename
        std::cout << "My Source is saved at " << __TIMESTAMP__ << std::endl; // last saved date
        std::cout << "I was compiled " << __DATE__ << ", " << __TIME__ <<std::endl; // compiled time

        control();

        std::cout << "Finish" << std::endl;
        return 0;
}
