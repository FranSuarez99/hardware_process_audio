# hardware_process_audio

#NOTE: WIP

This project aims to create a volume control system for a Windows PC using an Arduino microcontroller, an encoder, an OLED display, and a button. The system allows the user to control the volume of individual audio processes on their PC and display relevant information on the OLED display.

## Features

- Control the volume of individual audio processes on a Windows PC.
- Display volume levels and process names on an OLED display.
- Switch between different audio processes using a button.
- Error handling and logging for improved reliability.

## Components

- Arduino microcontroller.
- Rotary encoder for volume control.
- OLED display for visual feedback.
- Button for switching between audio processes.
- USB cable for communication with the PC.

## Requirements

- Arduino IDE installed on your computer.
- Python 3.x installed on your computer.
- Libraries: `pycaw`, `pyserial`, `pillow` (for generating icons).
- Windows operating system.

## Setup

1. Connect the Arduino to your computer using a USB cable.
2. Install the necessary Python libraries by running `pip install pycaw pyserial pillow`.
3. Upload the Arduino sketch (`arduino_audio_control.ino`) to your Arduino board using the Arduino IDE.
4. Run the Python script (`audio_control.py`) on your computer to control the audio processes and display information on the OLED display.

## Usage

1. Turn on your Windows PC.
2. Open the Arduino IDE and upload the Arduino sketch to your Arduino board.
3. Run the Python script on your computer.
4. Use the rotary encoder to adjust the volume of the selected audio process.
5. Press the button to switch between different audio processes.
6. Monitor the OLED display for volume levels and process names.

## Contributing

Contributions are welcome! If you have any ideas for improvements or new features, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
