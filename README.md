# PowerMeter Project (oh9vd)

Welcome to the oh9vd PowerMeter project! This repository contains comprehensive resources for both the hardware and software components of a power meter. The hardware design is managed using KiCad, while the software development is conducted using PlatformIO with support for Arduino on the ATmega328P microcontroller.

## Table of Contents

- [PowerMeter Project (oh9vd)](#powermeter-project-oh9vd)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Hardware](#hardware)
    - [Files](#files)
  - [Software](#software)
    - [Files](#files-1)
  - [Getting Started](#getting-started)
  - [Installation](#installation)
    - [Hardware](#hardware-1)
    - [Software](#software-1)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)

## Overview

The PowerMeter project aims to create open-source HF Power and SWR (Standing Wave Ratio) measuring device. It includes detailed instructions and files for both hardware and software components. Tough, please **Note** that the hard ware part is only for reference and not intended to implement as is.

## Hardware

The hardware aspect is designed using **KiCad**, a powerful suite for electronic design automation. All relevant design files are stored in the `hardware` directory.

### Files

- `hardware/`: Contains all KiCad files including schematics, PCB layout, and custom libraries required for constructing the power meter reference implementation.

## Software

For software development, **PlatformIO** is used alongside Arduino to program the ATmega328P microcontroller. The source code and necessary configurations are provided in the `software/firmware` directory.

### Files

- `software/firmware/`: Houses the main firmware code and configuration files for PlatformIO.
- `libraries/`: External libraries required for firmware development.

## Getting Started

To get started with the project, clone this repository and ensure all dependencies are installed as per the guidelines in the [Installation](#installation) section.

```bash
git clone https://github.com/oh9vd/powermeter.git
cd powermeter
```

## Installation

### Hardware

1. Install **KiCad** from its [official website](https://www.kicad.org/).
2. Open the KiCad project files located in the `hardware/` folder to examine or modify the design.

### Software

1. Install **PlatformIO** via your preferred IDE extension or from the [PlatformIO website](https://platformio.org/).
2. Navigate to the `software/firmware` directory and open it in your PlatformIO-compatible IDE to access the firmware project.

## Usage

1. Create your own design of the power meter hardware (you can use the files in this repository as starting point if you wish).
2. Compile and upload the firmware to the ATmega328P using PlatformIO.
3. Connect the assembled device to a power source, and begin monitoring power consumption.

## Contributing

Contributions to enhance this project are welcome! Please read our [CONTRIBUTING.md](CONTRIBUTING.md) document for details on our contributing process.

## License

This project is licensed under the MIT License. For more information, see the [LICENSE](LICENSE) file.