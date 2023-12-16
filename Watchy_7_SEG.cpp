#include "Watchy_7_SEG.h"

#define DARKMODE false

void Watchy7SEG::drawWatchFace() {
  display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
  display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

  // reset step counter at midnight
  if (currentTime.Hour == 00 && currentTime.Minute == 00) {
    sensor.resetStepCounter();
    //turn off radios
    WiFi.mode(WIFI_OFF);
    btStop();
  }

  //time adjustment start
  //if you don't need a time adjustment, just delete all lines between time adjustment start and end
  //my watchy runs too fast (15 seconds and 500 ms a day), this code set back time each day by 15 seconds and 500 ms

  if (currentTime.Hour == 00 && currentTime.Minute == 30) {

    RTC.read(currentTime);
    int8_t sekunde = currentTime.Second;
    int8_t minute = currentTime.Minute;
    int8_t hour = currentTime.Hour;
    int8_t day = currentTime.Day;
    int8_t month = currentTime.Month;
    int8_t year = tmYearToY2k(currentTime.Year);

    delay(15500);

    tmElements_t tm;
    tm.Month = month;
    tm.Day = day;
    tm.Year = y2kYearToTm(year);
    tm.Hour = hour;
    tm.Minute = minute;
    tm.Second = sekunde;

    RTC.set(tm);
  }
  // time adjustment end

  drawTime();
}

void Watchy7SEG::drawTime() {
  int8_t stundeA = currentTime.Hour;
  int minuteA = currentTime.Minute;
  int s1 = sensor.getCounter();
  int tagA = currentTime.Day;
  int monatA = currentTime.Month;
  int n, hour;
  int16_t xc, yc;
  uint16_t wc, hc;

  float VBAT = getBatteryVoltage();
  uint8_t Protz = min<int>(100 - ((4.16 - VBAT) * 100), 100);

  display.drawBitmap(0, 0, xcpu, 200, 200, GxEPD_BLACK);
  display.setFont(&cpu16pt7b);
  display.getTextBounds(String(stundeA), 100, 105, &xc, &yc, &wc, &hc);
  display.setCursor(78 - (wc / 2), 105);
  display.println(stundeA);

  display.getTextBounds(String(minuteA), 100, 105, &xc, &yc, &wc, &hc);
  display.setCursor(117 - (wc / 2), 105);
  display.println(minuteA);

  display.getTextBounds(String(tagA), 100, 105, &xc, &yc, &wc, &hc);
  display.setCursor(78 - (wc / 2), 140);
  display.println(tagA);

  display.getTextBounds(String(monatA), 100, 105, &xc, &yc, &wc, &hc);
  display.setCursor(117 - (wc / 2), 140);
  display.println(monatA);

  display.setFont(&cpu10pt7b);
  display.setCursor(20, 175);
  display.println(Protz);
  display.setCursor(125, 25);
  display.println(s1);
  display.setCursor(5, 65);
  String wTag = dayShortStr(currentTime.Wday);
  display.println(wTag);
}
