#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "A73";
const char* password = "axeo6876";
const char* mqtt_server = "hairdresser.cloudmqtt.com";
const char* mqtt_user = "esp";
const char* mqtt_password = "esp";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Wire.begin();
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi connection...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, 18974);
  
  reconnect();
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    if (client.connect("", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT server");
      client.setCallback(callback);
      //subscribe to topic
      client.subscribe("key");
      client.subscribe("code");
      ///
      pinMode(2, OUTPUT);
      digitalWrite(2, LOW);
      delay(1000);
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(2, LOW);
      delay(1000);
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(2, LOW);
      delay(1000);
      digitalWrite(2, HIGH);
      ///
    } 
    else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Eli lava");
  if (strcmp(topic, "key") == 0) {
    String message = "";
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }
    Open(topic, message);
  }
  else if(strcmp(topic, "code") == 0) {
    Serial.println(topic);
    String message = "";
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }
    Open(topic, message);
  }
}

void Open(String topic,String message) {
  String stringArray[] = {topic, message};
  Serial.println(message);
  Wire.beginTransmission(8);

  for (int i = 0; i < sizeof(stringArray) / sizeof(stringArray[0]); i++) {
    String currentString = stringArray[i];
    Wire.write(currentString.c_str(), currentString.length()); 
    Wire.write('\n');
  }

  Serial.println("the key/code has been sent");

  Wire.endTransmission();  
}
