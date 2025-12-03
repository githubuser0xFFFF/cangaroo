# cangaroo

An open source can bus analyzer with support for transmit/receive of standard and FD frames and DBC decoding of incoming frames

## Supported interfaces

* Candlelight interfaces on Windows
* Asclepion CAN Windows Service interfaces on Windows
* Socketcan interfaces on Linux

![demo1](https://user-images.githubusercontent.com/2422337/179544017-0deb66ab-e81d-4e6c-9d99-4059a14921c0.gif)

## Building

### Prerequisites

* Qt6 (Core, Widgets, Gui, Xml, SerialPort, Network)
* CMake 3.16 or newer
* C++17 compatible compiler

#### Platform-specific dependencies

**Linux/Unix:**
```bash
# Ubuntu/Debian
sudo apt-get install libnl-3-dev libnl-route-3-dev

# RHEL/CentOS/Fedora
sudo yum install libnl3-devel
```

**Windows:**
- Visual Studio 2019 or newer
- Windows SDK (for SetupApi, Ole32, winusb)

### Building with CMake

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Running

The executable will be built in `build/bin/cangaroo` (or `build/bin/cangaroo.exe` on Windows).

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

