//---------------------------------------------------
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define NUM_RELAY   4   // Jumlah Relay
//---------------------------------------------------
const char ssid[]       = "-- Wifi Kalian-- ";
const char password[]   = "-- Password Kalian-- ";
const char web_host[]   = "192.168.1.2";
//-----------------------------
int RLY[] = {D1, D2, D3, D4};

StaticJsonDocument<100> doc;
WiFiClient client;
//WiFiClientSecure client; // Kalau HTTPS, sesuaikan

//---------------------------------------------------
void setup() {
  delay(1000);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("> WIFI TERHUBUNG!");

  for (int i = 0; i < NUM_RELAY; i++) {
    pinMode(RLY[i], OUTPUT);
  }
}

//---------------------------------------------------
void loop() {
  //client.setInsecure();               // Kalau pakek HTTPS, seseuaikan
  String payload = "";
  bool parse_json = false;
  String data[NUM_RELAY + 1];
  if (client.connect(web_host, 80)) {   // kalau HTTPS 443
    Serial.println("> CONNECT SERVER");
    String url = "Youtube-Open-Project/Project-PHP-Bootstrap-IoT-ESP8266/Web-Code/api.php"; // sesuaikan foldernya
   //String url = "api.php";            // Kalau menggunakan Domain pribadi, bukan repo ini
    client.print(String("GET /") + url + " HTTP/1.1\r\n" +
                 "Host: " + web_host + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
    while (client.connected() || client.available()) {
      if (client.available()) {
        char c = client.read();
        if (c == '[') {
          parse_json = true;
        }
        if (parse_json) {
          payload += c;
        }
      }
    }
    client.stop();
  } else {
    client.stop();
  }
  if (payload != "") {
    Serial.println(payload);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      doc.clear();
      Serial.println("> ERROR JSON");
    } else {
      for (int i = 0; i < NUM_RELAY; i++) {
        int logika = doc[i];
        int urutan = i + 1;
        digitalWrite(RLY[i], logika);
        Serial.println("> DATA RELAY " + String(urutan) + " = " + String(logika));
      }
    }
    doc.clear();
  }
  delay(2000);
}
//---------------------------------------------------
