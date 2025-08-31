
// Please update pin number before uploading the code
// Also enter your ssid and password

#include <WiFi.h>
#include <WebSocketsServer_Generic.h>

const char* ssid = "Galaxy A22 5G9921";
const char* password = "password12";

// WebSocket server runs on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

int freq = 5000;
int resolution = 8;
int channelCounter = 0;

// Map pin → channel
struct PinChannel {
  int pin;
  int channel;
};
PinChannel pinChannels[16];
int pinCount = 0;

int getChannelForPin(int pin) {
  // check if already exists
  for (int i = 0; i < pinCount; i++) {
    if (pinChannels[i].pin == pin) return pinChannels[i].channel;
  }
  // assign new channel
  int ch = channelCounter++;
  // ledcSetup(ch, freq, resolution);
  // ledcAttachPin(pin, ch);
  ledcAttachChannel(pin, freq, resolution, ch);
  pinChannels[pinCount++] = {pin, ch};
  return ch;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String msg = String((char*)payload);
    Serial.print(msg);

    // Expected format: GESTURE:<Value>
    // if (msg.startsWith("GESTURE:")) {
    //     int firstColon = msg.indexOf(':', 8);
    //     if (firstColon > 0) {
    //     String value = msg.substring(8, firstColon);
        
    // }


    // Expected format: PIN:<pin>:<value>
    // if (msg.startsWith("PIN:")) {
    //   int firstColon = msg.indexOf(':', 4);
    //   if (firstColon > 0) {
    //     int pin = msg.substring(4, firstColon).toInt();
    //     int value = msg.substring(firstColon + 1).toInt();
    //     if (value < 0) value = 0;
    //     if (value > 255) value = 255;

    //     int ch = getChannelForPin(pin);
    //     analogWrite(pin, value);

    //     Serial.printf("Pin %d set to %d\n", pin, value);
    //     // webSocket.sendTXT(num, "OK");
    //   }
    // }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}
