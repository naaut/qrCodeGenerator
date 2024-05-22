# QR Code Generator

A flexible QR Code generator written in C++ and QML. This project aims to provide a user-friendly interface for creating various types of QR codes, with support for history managemen and customization.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Features

- Generate QR codes for different types of data, including URLs, WiFi credentials, contact information, and more.
- History management to keep track of generated QR codes.
- Customization options for QR code appearance.
- Print QR codes directly from the application.
- User-friendly interface built with QML.

## Installation

### Prerequisites

- C++17 or higher
- CMake 3.10 or higher
- Qt 5.15 or higher

### Steps

1. **Clone the repository**
   ```sh
   git clone https://github.com/yourusername/qrCodeGenerator.git
   cd qrCodeGenerator
   ```

2. **Create build directory and run CMake**
   ```sh
   mkdir build
   cd build
   cmake ..
   ```

3. **Build the project**
   ```sh
   make
   ```

4. **Run the application**
   ```sh
   ./qrCodeGenerator
   ```

## Usage

Once the application is running, you can generate QR codes by entering the desired data and selecting the type of QR code you want to create. The application also allows you to view previously generated QR codes in the history section.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
