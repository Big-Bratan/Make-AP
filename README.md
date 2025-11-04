<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/Group%20145%20(1).png" width="132">

# Make-AP

A simple ESP32 firmware, written for M5StickC Plus2 and M5Core2, allowing the creation of access point.

On M5Core2, the firmware supports serving files<sup>[ⓘ](#usage)</sup> from the SD card.

<sub>Some of the code and design were inspired by [M5Launcher](https://github.com/bmorcelli/M5Stick-Launcher).</sub>

## Table of Contents

- [Setup](#setup)
- [Usage](#usage)
  - [M5StickC Plus2](#m5stickc-plus2)
  - [M5Core2](#m5core2)
- [Compile & flash](#compile--flash)
- [Links](#links)

## Setup

This project was compiled using the Arduino IDE, you'll find a `.bin` in [/bins](https://github.com/Big-Bratan/Make-AP/blob/main/bins/MakeAP-2.0.0.bin).

#### Libraries

```
Arduino.h
Wifi.h
M5Unified.h
esp_system.h
pgmspace.h
DNSServer.h
WebServer.h
SD.h
```

## Usage

Create an access point either using default SSID/password or with your own.

On M5Core2, serve web content from the SD card (place files in `/sites` directory). Supported file types: **HTML**, **CSS**, **JavaScript**, **JSON**, **PNG**, **JPG**, **GIF**, **ICO**, **SVG**.

## Controls

### M5StickC Plus2

#### `List view` :

<div style="padding-bottom: 20px;">
    <img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/ListView.png" alt="M5StickC Plus2 - List view" width="210">
</div>

- Press Button `B` to navigate between list items.
- Press Button `A` to select current item.

#### `Keyboard view` :

<div style="padding-bottom: 20px;">
<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/KeyboardView.png" alt="M5StickC Plus2 - Keyboard view" width="210">
</div>

- Press Button `B` to move horizontally.
- Hold 2s Button `B` to move back.
- Press Button `POWER` to move vertically.
- Hold 2s Button `POWER` to move to the top keys `OK, CAP, DEL, SPACE`.
- Press Button `A` to select current key.

#### `AP view` :

<div style="padding-bottom: 20px;">
<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/APView.png" alt="M5StickC Plus2 - AP view" width="210">
</div>

- Press Button `POWER` to reboot.

Hold Button `POWER` to shut down.

### M5Core2

#### `SSID selection view` :

<div style="padding-bottom: 20px;">
<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/SsidViewM5core.png" alt="M5Core2 - List view" width="320">
</div>

- Navigate with M5Core2 buttons `UP`, `SELECT`, `DOWN`.

#### `Keyboard view` :

<div style="padding-bottom: 20px;">
<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/KeyboardViewM5core.png" alt="M5Core2 - Keyboard view" width="320">
</div>

- Use touch screen.

#### `AP view` :

<div style="padding-bottom: 20px;">
<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/ApViewM5core.png" alt="M5Core2 - AP view" width="320">
</div>

- Left button `RESTART` to reboot.
- Right button `SERVE` to select and serve files<sup>[ⓘ](#usage)</sup> from SD card.

#### `File selection view` <sub>(SD card required):</sub>

<div style="padding-bottom: 20px;">
<img src="https://raw.githubusercontent.com/Big-Bratan/Make-AP/main/img/SdDataViewM5core.png" alt="M5Core2 - File browsing view" width="320">
</div>

- Navigate with M5Core2 buttons `UP`, `SELECT`, `DOWN`.

## Compile & flash

If you want to compile and make a flashable .bin yourself:

1. From the Arduino IDE, go to `Sketch` -> `Export Compiled Binary`
2. Merge the compiled binaries using [esptool](https://docs.espressif.com/projects/esptool/en/latest/esp32/):

```
esptool.py --chip ESP32 merge_bin -o <BINARY_NAME>.bin --flash_mode dio --flash_size 4MB 0x1000 <PATH_TO_MakeAP.ino.bootloader.bin> 0x8000 <PATH_TO_MakeAP.ino.partitions.bin> 0x10000 <PATH_TO_MakeAP.ino.bin>
```

3. Flash the binary to the board

```
esptool.py --chip ESP32 --port <CONNECTED_BOARD_PORT> write_flash 0x0 <BINARY_NAME>.bin
```

## Links

- [Drawing pixel art](https://www.pixilart.com/)
- [Image to data](https://lang-ship.com/tools/image2data/)
- [m5-docs/api](https://github.com/m5stack/m5-docs/tree/master/docs/en/api)
- [M5Unified](https://github.com/m5stack/M5Unified/tree/master)
