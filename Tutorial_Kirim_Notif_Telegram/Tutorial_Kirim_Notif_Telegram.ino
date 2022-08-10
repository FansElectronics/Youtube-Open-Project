#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const String wifi_ssid            = "FansElectronics";
const String wifi_pass            = "#";
const String bot_token            = "";
const String chat_id              = "";
IPAddress WIFI_IP;
WiFiClientSecure client;

//-------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println(F("MULAI"));
  WiFi.begin(wifi_ssid, wifi_pass);
  digitalWrite(LED_BUILTIN, HIGH);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, LOW);
  WIFI_IP = WiFi.localIP();
  Serial.println("WIFI IP: " + WIFI_IP.toString());
}
//-------------------------------------------------------------------------------------------
void loop() {
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    Serial.print(F("MSG: "));
    Serial.println(msg);
    kirimTelegram(msg);
  }
}

//-------------------------------------------------------------------------------------------
bool kirimTelegram(String pesan) {
  client.setInsecure();
  if (client.connect("api.telegram.org", 443)) {     // Jika konek ke Telegram
    String url = "bot" + bot_token + "/sendMessage?text=" + pesan + "&chat_id=" + chat_id;
    client.print("GET /" + url + " HTTP/1.1\r\n" +
                 "Host: api.telegram.org\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
    client.stop();
    return 1;
  } else {
    client.stop();
    return 0;
  }
}
