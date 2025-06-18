# STM32F722RET6 Custom Flight Controller

This repo documents how to bring up a custom STM32F722RET6-based flight controller from a blank PCB to running either **ArduPilot** or **Betaflight**, using USB DFU bootloader flashing — no SWD needed after the first flash.

---

## Hardware Overview

| Component       | Interface | MCU Pins       |
|----------------|-----------|----------------|
| MCU            | STM32F722RET6 | —             |
| IMU (Gyro)     | SPI3      | SCK: PC10, MISO: PC11, MOSI: PC12, CS: PD2, INT: PC13 |
| Barometer      | I²C1      | SCL: PB8, SDA: PB9 |
| Radio (nRF24L01)| SPI1     | SCK: PA5, MISO: PA6, MOSI: PA7, CS: PA4, EN: PA2, IRQ: PA3 |
| Motors         | PWM       | PA0, PA1, PB5, PC8 |
| Battery Monitor| ADC       | PC2            |
| USB            | USB FS    | DM: PA11, DP: PA12 |
| LEDs           | GPIO      | PB0, PB1, PB2   |
| Crystal        | HSE       | PH0 (IN), PH1 (OUT) |

---

## Initial Setup – Flash Bootloader (First Time Only)

### 1. Put MCU in DFU Mode:
- Pull `BOOT0` high
- Tap `NRST` low
- Connect USB

### 2. Flash Bootloader (choose one):

#### ArduPilot:
```bash
sudo apt install dfu-util
dfu-util -a 0 --dfuse-address 0x08000000 –D fmuv5_bl.binfile
```

#### Betaflight:
Since All STM32 MCUs include a ROM-based DFU bootloader by default (no external bootloader required),  like we did before, we simply pull BOOT0 high and reset, and the MCU enters DFU mode using built-in firmware at 0x1FFFxxxx.
This built-in DFU mode supports flashing directly to 0x08000000 or 0x08004000.

> Unlike the bootloader we used for ArduPilot (which would not work for BF), we will need to enter DFU mode every time we flash the board, which is a minor inconvenience but not necessary since we are making a prototype.

---

## Installing ArduPilot

### 1. Clone and set up ArduPilot:
```bash
git clone https://github.com/ArduPilot/ardupilot.git
cd ardupilot
git submodule update --init --recursive
Tools/environment_install/install-prereqs-ubuntu.sh -y
. ~/.profile
```

### 2. Add your board:
Create folder: `libraries/AP_HAL_ChibiOS/hwdef/fahmyboard_f722/` and add:
- `hwdef.dat` — full hardware mapping
- `bootloader.ld` — sets firmware offset to `0x08004000`
- `default.params` — optional parameter defaults

### 3. Register board:
Edit `libraries/AP_HAL_ChibiOS/hwdef/boards.py`:
```python
"fahmyboard_f722": "hwdef/fahmyboard_f722",
```

### 4. Build firmware:
```bash
./waf configure --board fahmyboard_f722
./waf copter
```

### 5. Flash via DFU:
```bash
dfu-util -a 0 -s 0x08004000:leave -D build/fahmyboard_f722/copter.bin
```

### Done!
Connect to **Mission Planner** or **QGroundControl** via USB.

---

## Installing Betaflight

### 1. Clone and set up:
```bash
git clone https://github.com/betaflight/betaflight.git
cd betaflight
make tools_install
```

### 2. Add your target:
Place your custom files in:
```
src/main/target/fahmyboard_f722/
  ├── target.h
  └── target.c
```

### 3. Register in `boards.txt`:
```text
fahmyboard_f722  F7  STM32F7x2
```

### 4. Build:
```bash
make fahmyboard_f722:dfu
```

### 5. Flash using Betaflight Configurator:
- Load `.hex` from `obj/firmware_fahmyboard_f722.hex`
- Click **Flash Firmware**

### Done!
Set up IMU, barometer, motors, and LED strip in GUI.

---

## File Summary

| File               | Purpose                                |
|--------------------|----------------------------------------|
| `hwdef.dat`        | Defines all pin assignments for ArduPilot |
| `bootloader.ld`    | Sets start address to 0x08004000       |
| `default.params`   | Preloads useful parameters on boot     |
| `target.h`         | Pin configuration for Betaflight       |
| `target.c`         | Optional GPIO initialization for radio |

---


