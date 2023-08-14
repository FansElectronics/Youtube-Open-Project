//--------------------------------------------------------------------------------
// LIBRARY
#include <ModbusRtu.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// DIFINISIKAN NILAI / PIN 
#define INTERVAL 500

// GLOBAL VARIABLE
char lcdBuff[20];
uint16_t mydata[5];
uint8_t step;
unsigned long interval;
modbus_t telegram;
int voltage, getaran;

// LIBRARY SETTING
SoftwareSerial SerialBus(3, 2);      // OUTSEAL TX = D2, OUTSEAL RX = D3
Modbus master(0, SerialBus);         // Set Master
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C 16x2
//--------------------------------------------------------------------------------
// SETUP, Sekali diekseskusi
void setup() {
  Serial.begin(57600);             // Serial ke PC
  SerialBus.begin(57600);          // Serial ke Modbus
  lcd.begin();                     // Mulai LCD
  master.start();                  // Mulai Master Modbust
  master.setTimeOut(500);          // Set Timeout jika tidak ada slave
                                   // Data Awal
  interval = millis() + INTERVAL;  // Interval pull 1000ms, atur sendiri
  step = 1;                        // Set Step = 1
}
//--------------------------------------------------------------------------------
// Looping, Perulangan permanent, sampai restart
void loop() {
  switch (step) {                                         // Jika Step dengan nilai?
    case 1:                                               // Jika NOL / 0
      if (millis() > interval) step++;                    // Tunggu interval
      break;                                              // Next Step
    case 2:                                               // Jika SATU / 1
      telegram.u8id = 1;                                  // SLAVE ID
      telegram.u8fct = 3;                                 // READ INTEGER OUTSEAL
      telegram.u16RegAdd = 0;                             // Start Array
      telegram.u16CoilsNo = 2;                            // Jumlah Array
      telegram.au16reg = mydata;                          // Data Array dari 0
      master.query(telegram);                             // Request ke Slave
      step++;                                             // Next Step
      break;                                              // Keluar Switch
    case 3:                                               // Jika DUA / 2
      master.poll();                                      // Request Ke SLAVE
      if (master.getState() == COM_IDLE) {                // Jika mendapatkan Response
        step = 1;                                         // Balik ke Step 1
        interval = millis() + INTERVAL;                   // Tunggu Interval lagi
        Serial.print(mydata[0]);                          // Print Data ke PC
        Serial.print(", ");                               // Print Data ke PC
        Serial.print(mydata[1]);                          // Print Data ke PC
        Serial.println();                                 // Print Data ke PC
        voltage = mydata[0];                              // Update Data Voltage
        getaran = mydata[1];                              // Update Data Getaran
        sprintf(lcdBuff, "VOLTASE : %03dV  ", voltage);   // Data LCD
        lcd.setCursor(0, 0);                              // Set Posisi LCD
        lcd.print(lcdBuff);                               // Print Data ke LCD
        sprintf(lcdBuff, "GETARAN : %03d%%  ", getaran);  // Data LCD
        lcd.setCursor(0, 1);                              // Set Posisi LCD
        lcd.print(lcdBuff);                               // Print Data ke LCD
      }                                                   //
      break;                                              // Keluar Switch
  }                                                       // Looping Lagi
}
//--------------------------------------------------------------------------------
