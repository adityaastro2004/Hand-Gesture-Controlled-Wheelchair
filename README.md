
# Hand Gesture Controlled Wheelchair

This repository contains the code and documentation for a hand gesture-controlled wheelchair project. The project uses a transmitter and receiver setup to detect hand gestures and control the movements of a wheelchair accordingly.

## Features

- Real-time hand gesture recognition.
- Wireless communication between transmitter and receiver.
- Control commands for wheelchair movements based on recognized gestures.
- Efficient and low-latency operation.

## Project Structure

- **Transmitter:** The transmitter code captures hand gestures and sends corresponding commands to the receiver.
- **Receiver:** The receiver code receives commands and controls the wheelchair's motors accordingly.

## Getting Started

### Prerequisites

- Arduino IDE
- Two ESP32 boards (for transmitter and receiver)
- Accelerometer sensor (e.g., MPU6050)
- Motor driver for controlling wheelchair motors

### Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/adityaastro2004/Hand-Gesture-Controlled-Wheelchair.git
    ```

2. **Open the Arduino IDE:**

    Open the Arduino IDE and navigate to the cloned repository.

3. **Upload Transmitter Code:**

    Navigate to `transmitter/` directory, open `transmitter.ino`, and upload it to the Arduino board connected to the accelerometer.

4. **Upload Receiver Code:**

    Navigate to `receiver/` directory, open `receiver.ino`, and upload it to the Arduino board connected to the motor driver and wireless communication module.

## Usage

1. **Setup the Transmitter:**

    - Connect the accelerometer sensor to the Arduino board as per the wiring diagram provided in the `transmitter/` directory.
    - Ensure the wireless communication module is connected correctly.

2. **Setup the Receiver:**

    - Connect the motor driver and motors to the Arduino board as per the wiring diagram provided in the `receiver/` directory.
    - Ensure the wireless communication module is connected correctly.

3. **Power Up:**

    - Power up both the transmitter and receiver Arduino boards.
    - The transmitter will start capturing hand gestures and send corresponding commands to the receiver.

4. **Control the Wheelchair:**

    - Use predefined hand gestures to control the movement of the wheelchair.
    - The receiver will process the commands and drive the motors accordingly.

## Transmitter Code

The transmitter code captures hand gestures using an accelerometer and sends corresponding commands to the receiver via a wireless communication module.

### Wiring Diagram

Refer to the wiring diagram provided in the `transmitter/` directory for connecting the accelerometer sensor and wireless communication module to the Arduino board.

### Code Overview

The transmitter code initializes the accelerometer sensor, reads gesture data, and sends commands based on the recognized gestures.

## Receiver Code

The receiver code receives commands from the transmitter and controls the wheelchair's motors via a motor driver.

### Wiring Diagram

Refer to the wiring diagram provided in the `receiver/` directory for connecting the motor driver and wireless communication module to the Arduino board.

### Code Overview

The receiver code initializes the wireless communication module, receives commands, and controls the motors accordingly.

## Contributing

Contributions are welcome! If you have any ideas or improvements, feel free to open an issue or submit a pull request.

### Steps to Contribute

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## License

This project is licensed under the MIT License.
