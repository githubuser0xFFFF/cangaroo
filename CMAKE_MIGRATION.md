# CMake Build Migration Guide

## Overview
The cangaroo project has been migrated from qmake (`.pro`/`.pri` files) to CMake (`CMakeLists.txt` files).

## Quick Start

### Prerequisites
- Qt6 (Core, Widgets, Gui, Xml, SerialPort, Network)
- CMake 3.16 or newer
- C++17 compatible compiler

#### Platform-specific dependencies:
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

### Building
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running
The executable will be built in `build/bin/cangaroo` (or `build/bin/cangaroo.exe` on Windows).

## CMake Structure

### Main Components
- **Root CMakeLists.txt**: Project configuration, Qt6 setup, platform detection
- **src/CMakeLists.txt**: Main executable with all module dependencies
- **src/core/CMakeLists.txt**: Core backend library (Backend, CanTrace, etc.)
- **src/driver/CMakeLists.txt**: Base driver library + platform-specific drivers
- **src/parser/dbc/CMakeLists.txt**: DBC file parser
- **src/window/*/CMakeLists.txt**: Individual window modules

### Platform-Specific Drivers
Automatically enabled based on platform:
- **Windows**: CandleApiDriver, AsclCANWinServiceDriver
- **Linux**: SocketCanDriver

Optional drivers (currently disabled):
- CANBlastDriver (cross-platform)
- SLCANDriver (cross-platform)

To enable optional drivers, uncomment the relevant lines in `src/driver/CMakeLists.txt`.

## Migration Notes

### What Changed
- All `.pro` files replaced with `CMakeLists.txt`
- All `.pri` files converted to library definitions
- Platform conditionals moved to CMake syntax
- Qt5 dependencies updated to Qt6
- Build outputs organized under `build/bin` and `build/lib`

### What Stayed the Same
- Source code structure unchanged
- All existing functionality preserved
- Platform-specific compilation logic maintained
- Same external dependencies required