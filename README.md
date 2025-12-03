# cangaroo

An open source can bus analyzer with support for transmit/receive of standard and FD frames and DBC decoding of incoming frames

**Supported interfaces:**

* [CANable](http://canable.io) SLCAN interfaces on Windows and Linux
* [CANable 2](http://canable.io) SLCAN interfaces on Windows and Linux with FD support
* Candlelight interfaces on Windows
* Socketcan interfaces on Linux
* [CANblaster](https://github.com/normaldotcom/canblaster) socketCAN over UDP server with auto-discovery

![demo1](https://user-images.githubusercontent.com/2422337/179544017-0deb66ab-e81d-4e6c-9d99-4059a14921c0.gif)


## Building on Windows

* Qt Creator (Community Version is okay) brings everything you need
* except for the PCAN libraries. 
  * Get them from http://www.peak-system.com/fileadmin/media/files/pcan-basic.zip
  * Extract to .zip to src/driver/PeakCanDriver/pcan-basic-api
  * Make sure PCANBasic.dll (the one from pcan-basic-api/Win32 on a "normal" 32bit Windows build)
    is found when running cangaroo, e.g. by putting it in the same folder as the .exe file.
* if you don't want Peak support, you can just disable the driver:
  remove the line "win32:include($$PWD/driver/PeakCanDriver/PeakCanDriver.pri)"
  from src/src.pro
* if you want to deploy the cangaroo app, make sure to also include the needed Qt Libraries.
  for a normal release build, these are: Qt5Core.dll Qt5Gui.dll Qt5Widgets.dll Qt5Xml.dll

## Building with CMake

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

For detailed changes and version history, see [CHANGELOG.md](CHANGELOG.md).

## TODO

### backend

* support non-message frames in traces (e.g. markers)
* implement plugin API
* embed python for scripting

### can drivers

* allow socketcan interface config through suid binary
* socketcan: use hardware timestamps (SIOCSHWTSTAMP) if possible
* cannelloni support
* windows vector driver

### import / export

* export to other file formats (e.g. Vector ASC, BLF, MDF)
* import CAN-Traces

### general ui

* give some style to dock windows
* load/save docks from/to config

### log window

* filter log messages by level

### can status window

* display #warnings, #passive, #busoff, #restarts of socketcan devices

### trace window

* assign colors to can interfaces / messages
* limit displayed number of messages
* show error frames and other non-message frames
* sort signals by startbit, name or position in candb

### CanDB based generator

* generate can messages from candbs
* set signals according to value tables etc.
* provide generator functions for signal values
* allow scripting of signal values

### replay window

* replay can traces
* map interfaces in traces to available networks

### graph window

* test QCustomPlot
* allow for graphing of interface stats, message stats and signals

### packaging / deployment

* provide clean debian package
* gentoo ebuild script
* provide static linked binary
* add windows installer

