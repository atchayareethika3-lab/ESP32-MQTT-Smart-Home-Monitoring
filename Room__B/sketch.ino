
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* broker = "test.mosquitto.org";

// Must exactly match Room A's topic.
const char* topic = "smart-home/demo123/roomA/status";

const int LED_PIN = 2;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

void callback(char* receivedTopic, byte* payload,
              unsigned int length) {
  String message;

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("MESSAGE RECEIVED: ");
  Serial.println(message);

  if (message == "HIGH_TEMP") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("ROOM B LED: ON");
  } else if (message == "NORMAL_TEMP") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("ROOM B LED: OFF");
  }

  Serial.println("--------------------");
}

void connectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Connecting to MQTT...");

    if (mqtt.connect("RoomB-demo123")) {
      Serial.println("connected");
      mqtt.subscribe(topic);
      Serial.println("Subscribed to Room A status");
    } else {
      Serial.println("retrying in 2 seconds");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nRoom B Wi-Fi connected");

  mqtt.setServer(broker, 1883);
  mqtt.setCallback(callback);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    connectMQTT();
  }
  mqtt.loop();
}
