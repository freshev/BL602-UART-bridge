# BL602 UART bridge

Based on HiFlying HF-LPX70 [SDK](http://ftp.hi-flying.com:9000/HF-LPX70_Compile/SDK/).

The main purpose is to bypass BL602 chip in HiFlying Elfin EG41B device. 
This makes Air780e direct access via UART1 to main EG41B RS232/RS485 out port. 


## Build

### Windows
1. Clone this repo:
```bash
git clone https://github.com/freshev/BL602-UART-bridge
```

2. Install [MSYS2](https://www.msys2.org/)

3. Add MSYS2 \usr\bin to PATH environment variable like `C:\msys64\usr\bin`

4. Run one of the following `makeXXX.bat`
```bash
make_9600_7E1.bat
make_9600_8N1.bat
make_115200_7E1.bat
make_115200_8N1.bat
```
I.e. `make_9600_7E1.bat` makes a binary firmware for UART 0 to 1 bridge with baudrate 9600, 7-Even-1, etc.
   
## Burn firmware

### Windows
Burn with `SimpleFlasher`: 
1) Execute `BLDevCube\BLDevCube.exe` 
* Select `Partition table` to `.\chips\bl602\partition\partition_cfg_HF_2M_V2.0.01.toml` 
* Select `Boot2 Bin` to `.\chips\bl602\bootloader_HF_2M_V3.0.12.bin` 
* Select `Firmware Bin` to `..\out\lpt570_full_9600_8N1.bin` 

2) Connect Elfin EG41B to PC via USB/RS232/RS485 converter. Wires from USB/RS232/RS485 converter to EG41B board MUST be short (not more then 5cm).
Otherwise, you will get errors/unstables when reading/writing flash. 

3) Connect GPIO8 via a 5-10kOhm resistor to 3.3V (copper pads on the back of the EG41B board). 
4) Turn power (off and) on to EG41B board. 
5) Start burn, pressing `Create and Download` button. 
6) Break GPIO8 connection to 3.3v. 
7) Turn power off and on. 

## Test
To test bridge:
1) Connect to Air780e (USB-C jack at EG41B board) 
2) Open terminal on appeared new third (or second) COM port. 
3) in [Air780e micropython](https://github.com/freshev/micropython/tree/master/ports/air780) mode use following script: 
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
4) Symbols from BL602 UART0 (main EG41B input) should be printed in micropython and returned back to UART0. 


##  Notes
* The new designed `BLEDebug` application can show debug output from BLE602 chip (Debug over Bluetooth). See BLEDebug folder. 
* Default lib `LPBX7Kernel` was rewritten to redirect chip debug log to Bluetooth. Also changes made in some project `.mk` files. 
* To make sure the firmware is working - compile and burn the firmware with `hfdbg_set_level(1)` at src/app_main.c.
In this case you should see `[UART]` (with garbage) message at EG41B main port (PC USB/RS232/RS485 converter configured with 115200, 8N1). 
* To completely disable debug log compile and burn the firmware with `hfdbg_set_level(0)` at src/app_main.c 
* BL602 GPIO21 connected to Air780 power.
* BL602 GPIO12 connected to Air780 reset.
* BL602 GPIO16 connected to internal EG41B UART/RS485 converter (DE/!RE pin).

## Copyrights
* FreeRTOS Kernel V10.2.1 Copyright (C) 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved. 
* HiFlying HF-LPX70 SDK Copyright (C) 2017 ShangHai High-flying Electronics Technology Co.,Ltd.

## Misc

* BLEDebug screenshot
<p align="center">
  <img src="https://github.com/BL602-UART-bridge/blob/master/docs/BLEDebug.jpg"/>
</p>
* EG41B Disassemble
<p align="center">
  <img src="https://github.com/BL602-UART-bridge/blob/master/docs/EG41B_Disassemble.jpg"/>
</p>
* EG41B board front
<p align="center">
  <img src="https://github.com/BL602-UART-bridge/blob/master/docs/EG41B_front.jpg"/>
</p>
* EG41B board back
<p align="center">
  <img src="https://github.com/BL602-UART-bridge/blob/master/docs/EG41B_back.jpg"/>
</p>
* EG41B BL602 boot pins
<p align="center">
  <img src="https://github.com/BL602-UART-bridge/blob/master/docs/BL602_boot.jpg"/>
</p>
* EG41B Air780e boot pins
<p align="center">
  <img src="https://github.com/BL602-UART-bridge/blob/master/docs/Air780e_boot.jpg"/>
</p>
