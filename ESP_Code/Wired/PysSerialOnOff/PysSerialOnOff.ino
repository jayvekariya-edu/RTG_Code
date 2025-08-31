void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200); // Initialize serial communication
  Serial.println("ESP32 ready to receive data.");
}

void loop() {
  String receivedData;
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n'); // Read until newline
    Serial.print("You sent: ");
    Serial.println(receivedData);

    if(receivedData.indexOf("Rock")!=-1){
    digitalWrite(2,HIGH);
    }

    else if(receivedData.indexOf("Paper")!=-1){
    digitalWrite(2,LOW);
    }

    else if(receivedData.indexOf("Scissor")!=-1){
    digitalWrite(2,LOW);
    }
  }
}