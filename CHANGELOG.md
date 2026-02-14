# Changelog

All notable changes to cangaroo will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.5.1] - 2026-02-14

### Fixed

- fixed AsclCANWinServiceDriver to avoid receive function blocking send function


## [0.5.0] - 2026-01-06

### Added

- Restoring last workspace on startup
- Support for showing TX messages in trace view
- Added icons for main menu items and trace view toolbar buttons
- Added Start and Stop measurement buttons to trace view toolbar

## [0.3.0] - 2025-12-03

### Added

- CMake build system support
- Qt6 compatibility

### Changed

- Migrated from qmake (.pro/.pri files) to CMake build system
- Updated Qt5 dependencies to Qt6
- Modernized C++17 code patterns
- Support for MSVC2022 build environment

### Removed

- qmake build files (.pro and .pri files)
- Qt5 compatibility

## [0.2.4] - Unreleased

### Added

- Initial support for CAN FD
- Support for SLCAN interfaces on Windows and Linux (CANable, CANable 2.0) including FD support
- Support for [CANblaster](https://github.com/normaldotcom/canblaster) socketCAN over UDP server with auto-discovery
- Live filtering of CAN messages in trace view

## [0.2.1] - 2016

### Added

- Improved logging system

### Changed

- Easier logging implementation
- Scroll trace view per pixel, not per item (always show last message when autoscroll is on)

### Fixed

- Various refactorings and improvements

## [0.2.0] - 2016-01-24

### Added

- Docking windows system instead of MDI interface
- Windows build support
- Windows PCAN-basic driver
- CAN status window
- Timestamps, log level display in log window

### Changed

- Handle muxed signals in backend and trace window
- Do not try to extract signals from messages when DLC too short

### Fixed

- Bugfixes in setup dialog

## [0.1.3] - 2016-01-16

### Added

- New CAN interface configuration GUI (missing a suid binary to actually set the config)
- Use libnl-route-3 for socketcan device config read
- Query socketcan interfaces for supported config options
- New logging subsystem, do not use QDebug any more

### Changed

- Performance improvements when receiving lots of messages

### Fixed

- Bugfix with time-delta view: timestamps not shown when no previous message available

## [0.1.2] - 2016-01-12

### Added

- Implement big endian signals

### Fixed

- Fix device re-scan ("could not bind" console message)
- Fix some DBC parsing issues (signed signals, etc.)

## [0.1.1] - 2016-01-11

### Added

- Debian packaging information

### Changed

- Change source structure to better fit debian packaging

## [0.1.0] - 2016-01-10

### Added

- Initial release 🎉
- Basic CAN bus analysis functionality
- DBC decoding support
- Multi-platform support (Windows/Linux)