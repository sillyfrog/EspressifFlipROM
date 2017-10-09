# Change the boot ROM/Flash Image for an Espressif build

When working with an ESP chip that has an Espressif boot loader on it, the Flash the system will boot depends on the last OTA update. This is a quick hack mostly for my testing, to always force the use of ROM 1, so an upgrade (when doing SonOTA for example) will always start at ROM 1, then upgrade ROM 2, and finally install the Arduino image.

To use, run something like the following (this is what I use):

```
esptool.py --port /dev/cu.usbserial write_flash --flash_mode dout -fs 8m 0x00000 bin/boot_v1.5.bin 0x01000 ../../../SonOTA/static/image_user1-0x01000.bin 0x81000 ../../../EspressifFlipROM/ChangeBootFlash/ChangeBootFlash.ino-0x81000.bin 0xFB000 bin/blank.bin  0xFC000 bin/esp_init_data_default.bin 0xFE000 bin/blank.bin
```

This is run from the `esp_iot_sdk` directory.

To build the binary, follow the same directions as per Espressif2Arduino.
