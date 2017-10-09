#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

extern "C" uint8_t system_upgrade_userbin_check();
extern "C" void system_upgrade_flag_set(uint8 flag);
extern "C" void system_upgrade_reboot (void);

#define UPGRADE_FLAG_START 0x01
#define UPGRADE_FLAG_FINISH 0x02

byte _blink = 0;

enum FlashMode
{
  MODE_UNKNOWN,
  MODE_FLASH_ROM1,
  MODE_FLASH_ROM2
};


//USER EDITABLE VARABLES HERE
#define DELAY 100        //ms to blink/delay for
#define STATUS_GPIO 13  //gpio to toggle as status indicator
#define RETRY 3         //number of times to retry

void setup()
{
  Serial.begin(115200);
  Serial.print("\nInitalizing...");
  if(STATUS_GPIO)
  {
    pinMode(STATUS_GPIO, OUTPUT);
  }

  //blink our status LED while we wait for serial to come up
  for(int i=0;i<100;i++)
  {
    blink(); 
    delay(DELAY);
  }
  digitalWrite(STATUS_GPIO, HIGH);
  Serial.println("Done Waiting");

  Serial.printf("Current rom: ");
  uint8_t rom = system_upgrade_userbin_check() + 1;
  Serial.printf("%d\n", rom);

  Serial.println("Pretend start upgrade");
  system_upgrade_flag_set(UPGRADE_FLAG_START);
  delay(50);
  Serial.println("Pretend finish upgrade");
  system_upgrade_flag_set(UPGRADE_FLAG_FINISH);
  delay(50);
  Serial.println("Flipping boot ROM and rebooting...");
  system_upgrade_reboot();
  Serial.println("Done, delay...");
  delay(1000);
  Serial.println("Trying another reboot anyway...");
  ESP.restart();
}

void blink()
{
  if(STATUS_GPIO)
  {
     if(_blink)
      digitalWrite(STATUS_GPIO, LOW);
    else
      digitalWrite(STATUS_GPIO, HIGH);
      
      _blink ^= 0xFF;
  }
  Serial.print(".");
  yield(); // reset watchdog
}

void loop()
{
  delay(100);
}


