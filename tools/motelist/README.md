# motelist.py: A mote detection script for Contiki-NG

The motelist.py tool aims to automatically detect and output a list of
sensor/IoT devices connected to a computer.

Unless stated otherwise within individual files, motelist sources are
distributed under the terms of the [3-clause BSD license](LICENSE.md).
This license gives everyone the right to use and distribute the code,
either in binary or source code format, as long as the copyright license
is retained in the source code.

Some parts of motelist.py (especially the Linux backend), are based on
original work done by Janis Judvaitis and Atis Elsts.

## Usage
```bash
$ python motelist.py -h
usage: motelist.py [-c] [-o] [-b] [-h] [-v]

Automatically detect and print out a list of motes connected to this computer

optional arguments:
  -c, --csv          Print list in CSV format
  -o, --omit-header  Omit header row
  -b, --brief        Only print serial port paths
  -h, --help         Show this message and exit
  -v, --version      Prints software version

```

Standard output:
```bash
$ python motelist.py 
Port          Serial              VID     PID     Product                              Vendor           
------------  ------------------  ------  ------  -----------------------------------  -----------------
/dev/ttyACM0  L200015Z            0x0451  0xBEF3  XDS110 (02.02.05.01) with CMSIS-DAP  Texas Instruments
/dev/ttyACM1  L200015Z            0x0451  0xBEF3  XDS110 (02.02.05.01) with CMSIS-DAP  Texas Instruments
/dev/ttyUSB0  ZOL-B001-A20000777  0x10C4  0xEA60  Zolertia Firefly platform            Silicon Labs     
```

You can get the output in CSV format:
```bash
$ python motelist.py -c
Port;Serial;VID;PID;Product;Vendor
/dev/ttyUSB0;ZOL-B001-A20000777;0x10C4;0xEA60;Zolertia Firefly platform;Silicon Labs
/dev/ttyACM0;L200015Z;0x0451;0xBEF3;XDS110 (02.02.05.01) with CMSIS-DAP;Texas Instruments
/dev/ttyACM1;L200015Z;0x0451;0xBEF3;XDS110 (02.02.05.01) with CMSIS-DAP;Texas Instruments

```

You can ommit the header row with `-o`. You can also ommit all columns
except the first one with `-b`. You can also combine the `-cob` options:
```bash  
$ python motelist.py -ob
/dev/ttyUSB0
/dev/ttyACM0
/dev/ttyACM1
```

## Links
GitHub repository: https://github.com/contiki-ng/motelist
