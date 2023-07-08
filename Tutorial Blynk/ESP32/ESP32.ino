/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL63AHq2c8Y"
#define BLYNK_TEMPLATE_NAME "ESP32 Tutorial"
#define BLYNK_AUTH_TOKEN "EuU8XcKx6d1mWbJmMaCa2n_pAdy1mxFF"
#define LED_BUILTIN 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
char ssid[] = "Las#";
char pass[] = "TukangSolder#";

char lcdBuff[20];
int counting;
unsigned long interval;

WidgetLCD lcd(V0);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Blynk.virtualWrite(V3, 50);
}

void loop() {

  sprintf(lcdBuff, "NILAI:%03i", counting);
  lcd.print(0, 0, "COUNTING");
  lcd.print(0, 1, lcdBuff);

  if (millis() - interval > 1000) {
    counting++;
    if (counting >= 1000) counting = 0;
    interval = millis();
  }

  Blynk.run();
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.print(F("LED: "));
    Serial.println(digitalRead(LED_BUILTIN));
  }
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(LED_BUILTIN, LOW);  // ON
  } else {
    digitalWrite(LED_BUILTIN, HIGH);  // OFF
  }
  Serial.print(F("LED: "));
  Serial.println(digitalRead(LED_BUILTIN));
}
BLYNK_WRITE(V3) {
  int value = param.asInt();
  Serial.print(F("SLIDER: "));
  Serial.println(value);
}
