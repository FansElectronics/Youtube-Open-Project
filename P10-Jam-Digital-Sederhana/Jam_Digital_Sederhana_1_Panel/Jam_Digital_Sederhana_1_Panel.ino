//-----------------------------------------
#include <DMD.h>
#include <TimerOne.h>
#include <RTClib.h>

#include <fonts/Number6x12.h>
#include <fonts/System4x7.h>
#include <fonts/System6x7.h>

#define DMD_WIDTH     32
#define DMD_HEIGHT    16

int textSpeed = 100; // Kecepatan Text

//------------------------
String namaBulan[] = {"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI",
                        "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "DESEMBER"
                       };
char namaHari[7][12] = {"MINGGU", "SENIN", "SELASA", "RABU", "KAMIS", "JUMAT", "SABTU"};

unsigned long old, hold;
boolean BigDot  = false;
boolean TinyDot = false;

RTC_DS3231 rtc;
DMD dmd(1, 1);

//-----------------------------------------
void setup() {
  Timer1.initialize(2000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);
  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

//-----------------------------------------
void loop() {
  DateTime now = rtc.now();
  hold = millis();
  while ((millis() - hold) < 10000) {
    BigTime(now.hour(), now.minute(), 1);
  }
  dmd.clearScreen(true);
  String date = String(namaHari[now.dayOfTheWeek()]) + ", " + duaDigit(now.day()) + " " + namaBulan[now.month() - 1] + " " + String(now.year());
  RunText(date);
  dmd.clearScreen(true);
}

//-----------------------------------------
void ScanDMD() {
  dmd.scanDisplayBySPI();
  if ((millis() > (old + 500))) {
    if (BigDot) {
      dmd.drawFilledBox(15, 4, 16, 5, GRAPHICS_OR);
      dmd.drawFilledBox(15, 10, 16, 11, GRAPHICS_OR);
    } else if (TinyDot) {
      dmd.drawChar( 15, 0, ':', GRAPHICS_OR );
    }
  }
  if (( millis() < (old + 1000)) && (millis() > (old + 500))) {
    if (BigDot) {
      dmd.drawFilledBox( 15, 4, 16, 5, GRAPHICS_NOR );
      dmd.drawFilledBox( 15, 10, 16, 11, GRAPHICS_NOR );
    } else if (TinyDot) {
      dmd.drawChar( 15, 0, ':', GRAPHICS_NOR );
    }
  }
  if (millis() > (old + 1000) ) {
    old = millis();
  }
}
