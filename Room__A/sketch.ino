
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* broker = "test.mosquitto.org";

// Use the SAME unique topic in both projects.
// Change "demo123" to your own random identifier.
const char* topic = "smart-home/demo123/roomA/status";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
DHTesp dht;

void connectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Connecting to MQTT...");

    if (mqtt.connect("RoomA-demo123")) {
      Serial.println("connected");
    } else {
      Serial.println("retrying in 2 seconds");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.setup(15, DHTesp::DHT22);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nRoom A Wi-Fi connected");

  mqtt.setServer(broker, 1883);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    connectMQTT();
  }
  mqtt.loop();

  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature)) {
    Serial.println("DHT22 reading error");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.println(" C");

  const char* message =
      data.temperature > 30.0 ? "HIGH_TEMP" : "NORMAL_TEMP";

  if (mqtt.publish(topic, message)) {
    Serial.print("MESSAGE SENT: ");
    Serial.println(message);
  } else {
    Serial.println("Message publish failed");
  }

  delay(2000);
}
