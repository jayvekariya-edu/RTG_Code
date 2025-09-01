
#define LED_PIN 2

// Please update pin number before uploading the code
const int dir1 = 14; //pin to change direction for motor M1
const int pwm1 = 26; //Pwm pin for motor M1 ---Left
const int pwm2 = 18;// Pwm pin for motor M2 ---Right
const int dir2 = 5; // pin to change direction for motor M2

// class_names = ["dislike", "fist", "one", "peace", "stop", "no_gesture"]
// actions     = [forward ,  backward, left, right,   stop,   stop]



void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(dir2,OUTPUT);

  Serial.begin(115200); // Initialize serial communication
  Serial.println("ESP32 ready to receive data.");
}

void loop() {
  String receivedData;
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n'); // Read until newline
    Serial.print("You sent: ");
    Serial.println(receivedData);

    if(receivedData.indexOf("dislike")!=-1){
    moveForward();
    }

    else if(receivedData.indexOf("fist")!=-1){
      digitalWrite(LED_PIN,LOW);
    moveBackward();
    }

    else if(receivedData.indexOf("one")!=-1){
      digitalWrite(LED_PIN,LOW);

    turnLeft();
    }

    else if(receivedData.indexOf("peace")!=-1){
      digitalWrite(LED_PIN,LOW);
    turnRight();
    }

    else if(receivedData.indexOf("stop")!=-1){
      digitalWrite(LED_PIN,HIGH);
    stop();
    }

    else if(receivedData.indexOf("no_gesture")!=-1){
      digitalWrite(LED_PIN,HIGH);
    stop();
    }

  }
}


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
