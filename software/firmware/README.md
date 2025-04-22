# PowerMeter Firmware Documentation

## Overview
This project is the firmware for the PowerMeter device. It is built using the PlatformIO ecosystem and targets the Arduino Nano ATmega328 board. The firmware includes features for data logging, frequency measurement, RSSI monitoring, and display management.

## Project Structure
- **LICENSE**: Licensing information for the project.
- **platformio.ini**: Configuration file for PlatformIO.
- **README.md**: General project information.
- **include/**: Header files for various modules.
  - `adc.h`: ADC-related functionality.
  - `calc.h`: Calculation utilities.
  - `datalogger.h`: Data logging functionality.
  - `debug.h`: Debugging utilities.
  - `display.h`: Display management.
  - `enc.h`: Encoder handling.
  - `freq.h`: Frequency measurement.
  - `global.h`: Global definitions and constants.
  - `model.h`: Data models.
  - `rssi.h`: RSSI monitoring.
  - `screen.h`: Screen management.
  - `time.h`: Time-related utilities.
- **lib/**: External libraries.
- **src/**: Source code for the firmware.
  - `main.cpp`: Main entry point of the firmware.
- **test/**: Test-related files.

## Dependencies
The project uses the following libraries:
- `ltc230x`
- `encoder` (version 1.4.0 or higher)
- `freqcount` (version 1.0.0 or higher)
- `Adafruit GFX Library` (version 1.10.13 or higher)
- `Adafruit SSD1306` (version 2.5.0 or higher)
- `ArduinoJson` (version 6.21.5 or higher)

## Configuration
The `platformio.ini` file contains the configuration for the project. Key settings include:
- **Platform**: `atmelavr`
- **Board**: `nanoatmega328`
- **Framework**: `arduino`
- **Upload Protocol**: `arduino`
- **Upload Speed**: `57600`
- **Monitor Port**: `COM7`
- **Monitor Speed**: `57600`

## Getting Started
1. Install [PlatformIO](https://platformio.org/).
2. Clone the repository.
3. Open the project in your preferred IDE.
4. Connect the Arduino Nano to your computer.
5. Update the `upload_port` in `platformio.ini` to match your device's port.
6. Build and upload the firmware using PlatformIO.

## Additional Resources
- [PlatformIO Documentation](https://docs.platformio.org/)
- [Arduino Nano Documentation](https://store.arduino.cc/products/arduino-nano)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)
- [ArduinoJson Library](https://arduinojson.org/)

## Contributing
Contributions are welcome! Please follow the guidelines outlined in the `CONTRIBUTING.md` file (if available).

## License
This project is licensed under the terms specified in the `LICENSE` file.
