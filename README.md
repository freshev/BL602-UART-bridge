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
   
## Burn

### Windows
   Burn with `SimpleFlasher`
   1) Run `BLDevCube\BLDevCube.exe`
   Select Partition table to `.\chips\bl602\partition\partition_cfg_HF_2M_V2.0.01.toml`
   Select Boot2 Bin to `.\chips\bl602\bootloader_HF_2M_V3.0.12.bin `
   Select Firmware Bin to `..\out\lpt570_full_9600_7.bin`

   2) Connect Elfin EG41B via USB/RS232/RS485 converter to PC. Wires from USB/RS232/RS485 converter to EG41B board MUST be short (not more then 5cm).
   Otherwise, you will get errors/unstables when reading/writing flash. 

   3) Connect GPIO8 via resistor 5-10kOhm to 3.3v (copper pads on the EG41B board backplate). 
   4) Turn power (off and) on to EG41B board. 
   5) Start burn, pressing `Create and Download` button. 
   6) Break GPIO8 connection to 3.3v. 
   7) Turn power off and on. 

## Test
   To test bridge:
   1) Connect to Air780e (USB-C jack at EG41B board)
   2) Open terminal to second (or third) COM port appered.
   3) In AT mode use followinf commands:
      TODO
   4) in (Air780e micropython)[https://github.com/freshev/micropython/tree/master/ports/air780] mode use following script:
   ```python
	from machine import UART
	import time
	u = UART(1, 9600)
	while(True):
    	if u.any() > 0:
        	r = u.read()
	        if r is not None and len(r) > 0:
    	        print(r.decode(), end = '')
        	    u.write(r)
	    time.sleep_ms(10)
   ```
   5) Symbols from BL602 UART0 (main EG41B input) should be printed in micropython and returned back to UART0. 


##  Notes
   There is no default debug output to EG41B board. 
   To make sure the firmware is working - burn the firmware with `hfdbg_set_level(1)` at src/app_main.c 
   In this case you should see `[UART]` message at EG41B output port (converter configured with 115200, 8N1). 


    