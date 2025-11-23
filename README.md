# BL602 UART bridge

Based on HiFlying HF-LPX70 [SDK](http://ftp.hi-flying.com:9000/HF-LPX70_Compile/SDK/).

The main purpose is to bypass BL602 chip in HiFlying Elfin EG41B device. 
This makes Air780e direct access via UART1 to RS232/RS485 out port. 


## Build

### Windows
1. Clone this repo:
   ```bash
   git clone https://github.com/freshev/BL602-UART-bridge
   ```

2. Install [MSYS2](https://www.msys2.org/)

3. Add MSYS2 \usr\bin to PATH environment variable 
   like C:\msys64\usr\bin 

4. Run on of the following make
   ```bash
   make9600_7.bat
   make9600_8.bat
   make115200_7.bat
   make115200_8.bat
   ```
   I.e. `make9600_7.bat` makes a binary for UART 0 to 1 bridge with baudrate 9600, 7N1, etc.
   



