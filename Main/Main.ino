#define trigPin 8
#define echoPin 10

//UltraSonic
const int buzzerPin = 13;
long duration, distance;

//WaterSensor
const int WaterSensor = A0;
int WaterSensorState = 0;

//LDR With Buzzer With Button1
const int ldrPin = A5;
const int button1Pin = A2;
int ldrState = 0;
int button1State = 0;

// SMS Sending Button
const int ButtonSMS = A3;
int ButtonSMSState = 0;
int ButtonSMSCondition = 0;

//GPS
String googleMapLink;

//SMS
#include <SoftwareSerial.h>
// Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(6, 7); // SIM800L Tx & Rx is connected to Arduino #6 & #7

void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);  // Set the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Set the echoPin as an INPUT
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(WaterSensor, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(ButtonSMS, INPUT);

  mySerial.begin(9600);  // Begin serial communication with SIM800L
  Serial.println("Initializing...");
  delay(1000);

  // SIM800L initialization commands
  mySerial.println("AT"); 
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Set SMS to TEXT mode
  updateSerial();
}

void loop() {
  WaterSensorState = analogRead(WaterSensor);
  ldrState = analogRead(ldrPin);
  button1State = analogRead(button1Pin);
  ButtonSMSState = analogRead(ButtonSMS);

  // Trigger SMS if button is pressed and SMS condition flag is not set
  if (ButtonSMSState > 400 && ButtonSMSCondition == 0) {
    ButtonSMSCondition = 1; // Set flag to prevent multiple SMS per press
    googleMapLink = "https://maps.app.goo.gl/aAk3zZQoXhX5PURy6";
    Serial.println("Sending SMS with location: " + googleMapLink);
    
    // Send SMS
    mySerial.print("AT+CMGS=\"+8801700507312\"\r"); //1789333514
    delay(100);
    mySerial.print(googleMapLink); 
    delay(100);
    mySerial.write(26);  // End SMS command
    updateSerial();
    
    delay(1000); // Delay to ensure SMS is sent
  }

  // Reset SMS condition when button is released
  if (ButtonSMSState < 400) {
    ButtonSMSCondition = 0;
  }

  // Clear and trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Water Sensor with Buzzer
  if (WaterSensorState > 400) {
    digitalWrite(buzzerPin, LOW);
    delay(50);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
  } 
  // LDR with Buzzer and Button1
  else if (ldrState > 400 && button1State > 400) {
    digitalWrite(buzzerPin, LOW);
    delay(500);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
  }
  // Ultrasonic with Buzzer
  else if (distance <= 10) {
    digitalWrite(buzzerPin, LOW);
    delay(500);
  } else {
    digitalWrite(buzzerPin, HIGH);
  }

  delay(500);  // Main loop delay
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());  // Forward Serial input to Software Serial
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());  // Forward Software Serial input to Serial
  }
}
