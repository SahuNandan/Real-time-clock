#include <Wire.h>
#include <RTClib.h>
#include <TM1637Display.h>

#define CLK 2  // Clock pin for TM1637
#define DIO 3  // Data pin for TM1637

RTC_DS1307 rtc;  // Create an RTC object
TM1637Display display(CLK, DIO);  // Create a display object

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  display.setBrightness(0x0f);  // Set display brightness (0x00 to 0x0f)

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);  // Halt if RTC is not found
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();  // Get the current date and time

  // Convert to 12-hour format
  int hour = now.hour();
  int minute = now.minute();

  if (hour == 0) {
    hour = 12;  // Midnight case
  } else if (hour > 12) {
    hour -= 12;  // Convert to 12-hour format
  }

  // Create a 4-digit number (HHMM) for display
  int displayTime = hour * 100 + minute;  // Format: HHMM

  display.showNumberDecEx(displayTime, 0b01000000, true);  // Display time with colon
  // 0b01000000 lights up the colon (dots) between hours and minutes

  delay(1000);  // Update every second
}
