#include <WiFi.h>

const char SSID[] = "aterm-ecce1b-g";
const char PASSWORD[] = "753bf0b3391c9";

WiFiServer server(80);

void setup() {
  Serial.begin(57600);
  while (!Serial);

  WiFi.begin(SSID, PASSWORD);
  Serial.print("WiFi connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println(" connected");

  server.begin();

  Serial.print("HTTP Server: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    client.println("Hello World!");
    client.stop();
  }
}
