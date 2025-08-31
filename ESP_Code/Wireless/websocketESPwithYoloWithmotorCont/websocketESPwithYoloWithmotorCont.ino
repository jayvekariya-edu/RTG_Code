
// Please update pin number before uploading the code
// Also enter your ssid and password

#include <WiFi.h>
#include <WebSocketsServer_Generic.h>

#define LED_PIN 2

const char* ssid = "Galaxy A22 5G9921";
const char* password = "password12";

const int dir1 = 3; //pin to change direction for motor M1
const int pwm1 = 5; //Pwm pin for motor M1 ---Left
const int pwm2 = 6;// Pwm pin for motor M2 ---Right
const int dir2 = 7; // pin to change direction for motor M2

// class_names = ["dislike", "fist", "one", "peace", "stop", "no_gesture"]
// actions     = [forward ,  backward, left, right,   stop,   stop]


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

    //     // Serial.printf("Pin %d set to %d\n", pin, value);
    //     // webSocket.sendTXT(num, "OK");
    //   }
    // }


    Serial.print(msg);

    if(msg.indexOf("dislike")!=-1){
    moveForward();
    }

    else if(msg.indexOf("fist")!=-1){
    moveBackward();
    }

    else if(msg.indexOf("one")!=-1){
    turnLeft();
    }

    else if(msg.indexOf("peace")!=-1){
    turnRight();
    }

    else if(msg.indexOf("stop")!=-1){
    stop();
    }

    else if(msg.indexOf("no_gesture")!=-1){
    stop();
    }

  }
}

void setup() {

  pinMode(dir1,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(dir2,OUTPUT);


  Serial.begin(115200);
  pinMode(2,OUTPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  digitalWrite(LED_PIN,HIGH);
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}

// Control Functions

void stop(){
 digitalWrite(dir1,HIGH);
 digitalWrite(dir2,HIGH); 
 analogWrite(pwm1,0); 
 analogWrite(pwm2,0); 
}

void moveForward(){
 digitalWrite(dir1,HIGH);
 digitalWrite(dir2,HIGH); 
 analogWrite(pwm1,255); 
 analogWrite(pwm2,255); 
}

void moveBackward(){
 digitalWrite(dir1,LOW);
 digitalWrite(dir2,LOW); 
 analogWrite(pwm1,255); 
 analogWrite(pwm2,255); 
}


void turnLeft(){
 digitalWrite(dir1,LOW);
 digitalWrite(dir2,HIGH); 
 analogWrite(pwm1,255); 
 analogWrite(pwm2,255); 
}

void turnRight(){
 digitalWrite(dir1,HIGH);
 digitalWrite(dir2,LOW); 
 analogWrite(pwm1,255); 
 analogWrite(pwm2,255); 
}

