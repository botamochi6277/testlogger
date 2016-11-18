# testLogger


The mcp3x08Spi class is wrapper of  [halherta's mcp3008Spi class](https://github.com/halherta/RaspberryPi-mcp3008Spi),
[halherta's blog](http://www.hertaville.com/interfacing-an-spi-adc-mcp3008-chip-to-the-raspberry-pi-using-c.html)

You can easily get analog values from mcp3008, mcp3208, etc.

For more information please visit :
[my blog (Japanese)](http://www.hertaville.com/interfacing-an-spi-adc-mcp3008-chip-to-the-raspberry-pi-using-c.html)


To build example binary natively on the Raspberry Pi:

```
g++ -std=c++11 -lpthread -fpermissive -Wall log_async.cpp mcp3008Spi.cpp mcp3x08Spi.cpp -o outBin
```
or

```
cmake .
make
```
