# IRRepeater

IRRepeater is a small electronic device designed to replay arbitrary IR control signals in different patterns.
This repository contains the firmware for the device.

## Building and flashing

This project is based on the PlatformIO platform. Building and flashing instruction can be found on the [PlatformIO website](https://platformio.org/).

**NOTE:** current `platformio.ini` is created for the old bootloader; for the new bootloader, line 11 should be replaced with `[env:nanoatmega328new]`

## Required hardware

**Circuit diagram**

![Circuit diagram](https://raw.githubusercontent.com/highwayradar/IRRepeater/master/svg/diagram.svg)

**Components**
- Arduino Nano
- SSD1306 128x64 monochrome I2C display
- 940nm IR emitter
- IR receiver (VS1838B)
- General-purpose transistor (e.g., 2N2222)
- 1KΩ resistor
- SE-020401 remote control unit

## Usage

The device is supposed to be powered from its USB port. Use an SE-020401 RC unit to control the device. Buttons mapping is displayed below.

![Remote buttons](https://raw.githubusercontent.com/highwayradar/IRRepeater/master/svg/remote.svg)

The main menu consists of 4 main screens. Use the `Prev menu` and `Next menu` buttons to navigate between them.
- **Learn IR**
  - From this screen, new IR signals can be learned. This device supports up to 4 signals stored, which are referenced by letters from A to D.
  - Learning new signal
    - To learn a new signal, select a slot using `Prev/next menu item` or one of the `Number input` buttons, and press `Enter`.
    - After this, point to the remote control you want to copy and press the button on it.
    - Upon successful learning process, you'll be returned to the **Learn IR** menu.
  - You can test that the signal was indeed learned by pressing the `Special action` button - this will make the device replay the signal, so you can test if it actually works.
  - If you're unable to make the command work, you might need to adjust the carrier frequency.
- **Program**
  - This screen configures the program (script) to be replayed.
  - The program consists of up to 4 commands, which are referenced by numbers from 1 to 4.
  - Each command consists of the following items:
    - Enabled/disabled (if disabled, it will be skipped).
    - The IR signal to be replayed (referenced by a letter from A to D).
    - Command duration in seconds - total time that should be spent on the current command.
      - For example, if the command duration is 0.7s, and it takes 0.37s to send the IR signal, the program will wait for additional 0.33s after the IR signal is transmitted.
    - Number of repetitions when replaying (from 1 to 5) - the signal may be sent several times to assure it is received.
  - To modify the command, select it using `Prev/next menu item` or one of the `Number input` buttons, and press `Enter`.
    - Use `prev/next menu item` to select an entry to change.
    - Use `Modify current value` or `Number input` buttons to change the currently selected value.
    - Press the `Back` button when done editing the program command.
  - After the command is set, you can test it by pressing the `Special action` button - this will make the device replay the command, so you can test if it actually works. Note that the delay, in the end, won't be replayed - only the signal with the specified number of repetitions.
- **Settings**
  - This screen configures global system settings.
  - Use `prev/next menu item` to select an entry to change.
  - Use `Modify current value` or `Number input` buttons to change the currently selected value.
  - **IR carrier** defines the carrier frequency which should be used when transmitting the IR signal. Current hardware isn't able to detect it automatically, so it needs to be configured manually. Most devices can work with any carrier frequency; however, if you have issues with reception, try the following carriers: 30 kHz, 33 kHz, 36 kHz, 38 kHz, 40 kHz, 56 kHz.
  - **IR min gap** defines the gap between two signal transmissions when using multiple repetitions during replay.
- **Actions**
  - Use `prev/next menu item` to select an action
  - Press `Enter` to activate the action
  - **Start program** starts executing the program in an infinite loop.
    - Press the `Special action` or `Back` button to stop executing the program
  - **Reset everything** clears the device memory and returns it to a fresh state
    - There is also another method to return the device to a fresh state in case it doesn't boot up
      - Once it is powered, it lights the internal LED for one second
      - Press the reset button on the Arduino board or disconnect the power during that second
      - On the next boot, the led will start blinking
      - Wait for 30 seconds, and the device will clean its memory and restart
      - To cancel resetting the device, disconnect the power or press the "Reset" button during that 30 seconds again
