// Library https://github.com/UIPEthernet/UIPEthernet

#include <UIPEthernet.h>

byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };
IPAddress ip(192, 168, 1, 110);
EthernetClient client;

char* host = "absensi-mahasiswa.online"; // IP Adres (or name) of server to dump data to
int interval = 5000; // Wait between dumps

void setup() {

  Serial.begin(9600);
  Ethernet.begin(mac, ip);

  Serial.print("IP Address : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.print("HOST : ");
  Serial.println(host);
}

void loop() {
  String response = "";
  bool parsing = false;
  // if you get a connection, report back via serial:
  if (client.connect("absensi-mahasiswa.online", 80)) {
    Serial.println("KONEK HOST");
    // Make a HTTP request:
    client.println("GET /api.php HTTP/1.1");
    client.println("Host: absensi-mahasiswa.online");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    while (client.connected() || client.available()) {
      if (client.available()) {
        char c = client.read();
        if (parsing) {
          response += c;
          if (c == '\n') {
            break;
          }
        }
        if (c == '@') {
          parsing = true;
        }
      }
    }
    client.stop();
    Serial.println(response);
  }
  else {
    // you didn’t get a connection to the server:
    Serial.println("Gagal Konek ke server");
    client.stop();
  }

  delay(interval);
}
