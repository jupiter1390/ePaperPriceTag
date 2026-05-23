# E-Paper Price Tag

<img width="400" height="300" alt="Photo 1" src="https://github.com/user-attachments/assets/25b041fd-4ccc-44b6-a7cb-d574d0a64218" />
<img width="400" height="300" alt="Photo 2" src="https://github.com/user-attachments/assets/961af000-4166-4e8a-bed1-3a8d61f38d70" />

This Project uses ESP32C3 Super mini and [WeAct 2.13 Inch Black-White-Red E-Paper module](https://aliexpress.com/item/1005004644515880.html).<br>
(Black-White Screen is also viable with a bit of code modifications)

# Wire Connection

<img width="362" height="313" alt="Wire guideline" src="https://github.com/user-attachments/assets/06481b63-e5fb-4bb8-b43a-dd6e38b18723" />

Wire colours are based on the wires that come along with E-Paper module.<br>
Chart Below shows corresponding port name for each connection:

| ESP32C3 | EPaper |
|---------|--------|
| GND     | GND    |
| 3.3V    | VCC    |
| 7       | SDA    |
| 6       | SCL    |
| 4       | CS     |
| 3       | BUSY   |
| 2       | RES    |
| 1       | D/C    |

# How to change Screen Data

<img width="300" height="650" alt="App Screenshot" src="https://github.com/user-attachments/assets/97b7037d-415f-4f12-8ba1-ecab99a837a4" />

[APK File](NKBLE210.apk)<br>
Built with App Inventor. Application requires Bluetooth Connection

Supply power to the ESP32 module, connect with Bluetooth using [Scan Bluetooth] Button(Will be automatically scan and connect with the module)

* [Restore Last] will restore last data; If there's no data it will be filled with preset data.
* [Random Barcode] will generate random 13-digit number for barcode data.
* [Submit] Button will send the data to ESP32 module via Bluetooth Connection.

Font(modified Gulim 12px and 18px bdf) Supports ASCII and few additional Latin Characters, Japansese(Hiragana and Katakana - not supported fully), and mainline Hangul Characters

# Required Arduino Libraries

[GxEPD2_3C](https://github.com/ZinggJM/GxEPD2/tree/master)<br>
[U8g2 for Adafruit GFX](https://github.com/olikraus/U8g2_for_Adafruit_GFX)<br>
[Arduino BLE](https://github.com/arduino-libraries/Arduinoble)

# Known Issues

* Generated Barcode has issues and will not be read as proper Code-128 A Barcode

# Todo

* English UI version APK build
* English UI version Arduino code
