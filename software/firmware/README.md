
# Powermeter firmware

## Overview

This project is built using PlatformIO, an open-source ecosystem for IoT development. It supports multiple boards and frameworks.

## Project Structure

```dir
powermeter-firmware/
├── include/                 # Header files
├── lib/                     # Libraries
├── src/                     # Source files
│   ├── main.cpp             # Main application code
├── test/                    # Unit tests
├── platformio.ini           # Project configuration file
```

## Prerequisites

- **PlatformIO Core**: Make sure you have PlatformIO Core installed. You can install it from the [official website](https://platformio.org/install).
- **IDE**: While not mandatory, using an IDE like VSCode with PlatformIO extension can ease development.

## Configuration

PlatformIO projects are configured using the `platformio.ini` file. Here is the configuration:

```ini
[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino

upload_protocol = arduino
upload_speed = 57600
upload_port=$UPLOAD_PORT
monitor_port=COM7 # change this to your platform configuration
monitor_speed = 57600

lib_deps =
  ltc230x
  encoder @^1.4.0
  freqcount@^1.0.0
  adafruit/Adafruit GFX Library@^1.10.13
  adafruit/Adafruit SSD1306@^2.5.0
  ArduinoJson@^6.21.5
```

## Getting Started

### Build and Upload

To build and upload the project to your board, run the following command in the project directory:

```bash
pio run --target upload
```

### Monitor Serial Output

To monitor the serial output from your device, use:

```bash
pio device monitor
```

## Libraries

- **ltc230x**: For Analog to Digital Converter control
- **encoder @^1.4.0**: For Rotary encoder handling
- **freqcount@^1.0.0**: For frequency Counter functionality
- **adafruit/Adafruit GFX Library@^1.10.13**: For core graphics for display
- **adafruit/Adafruit SSD1306@^2.5.0**: For Monochrome OLEDs based on SSD1306 drivers
- **ArduinoJson@^6.21.5**: For sending the measured data as JSON format

## Testing

To run tests, use:

```bash
pio test
```

**Note**: There is currently no test available

## Troubleshooting

Include common issues and solutions:

- **Compilation Errors**: Ensure all libraries are properly declared in `platformio.ini`.
- **Upload Failures**: Verify connection and correct port settings.

## Contribution

To contribute to this project:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/my-feature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/my-feature`).
5. Open a Pull Request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

- **GitHub**: [My GitHub Profile](https://github.com/oh9vd)

## Acknowledgments

Our project makes use of several third-party libraries. We would like to acknowledge the authors and contributors of these libraries for their valuable work:

- **ltc230x**
  - A library for interfacing with LTC230x ADCs.

- **encoder @^1.4.0**
  - Used for managing rotary encoders.

- **freqcount@^1.0.0**
  - A library for counting frequency from digital inputs.

- **Adafruit GFX Library @^1.10.13**
  - A display graphics library by Adafruit Industries.

- **Adafruit SSD1306 @^2.5.0**
  - A driver library for the Adafruit SSD1306 OLED displays.

- **ArduinoJson @^6.21.5**
  - A JSON library for Arduino and embedded C++.

Each library mentioned above is subject to its own licensing terms. Please refer to their respective documentation and source code for more information on usage and licenses.

## Disclaimer

This project is not affiliated with any company or organization. It is a personal project and does not represent any official or endorsement of any company or organization.
