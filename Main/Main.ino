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
//sms sent
#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(6, 7); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);  // Set the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Set the echoPin as an INPUT
  pinMode(buzzerPin, OUTPUT);

  //Doing Buzzer trunOff at first
  pinMode(buzzerPin, OUTPUT);
  pinMode(WaterSensor, INPUT);

  //LDR With Buzzer With Button1
  pinMode(ldrPin, INPUT);
  pinMode(button1Pin, INPUT);


  //digitalWrite(buzzerPin, HIGH);

  
  pinMode(ButtonSMS, INPUT);


  //SMS
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+8801789333514\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();

}

void loop() {


  



  //WaterSenosr---------------------------------------------------------
  WaterSensorState = analogRead(WaterSensor);
  //Serial.println(WaterSensorState);


  //LDR With Buzzer With Button1

  ldrState = analogRead(ldrPin);
  button1State = analogRead(button1Pin);


  //SMS BUTTON
  ButtonSMSState = analogRead(ButtonSMS);
  //Serial.println(ButtonSMSState);



  








// Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  distance = duration * 0.034 / 2;


  // Print the distance on the Serial Monitor
  //Serial.println(distance);
  delay(500);  // Wait for 500 milliseconds before the next reading
  //Serial.println(distance);

  //SENT SMS BUTTON
  if(ButtonSMSState > 400 &&  ButtonSMSCondition == 0){
    ButtonSMSCondition = 1;
    //googleMapLink = "https://www.google.com/maps/search/?api=1&query=22.929950,90.851372";
    googleMapLink = "https://maps.app.goo.gl/aAk3zZQoXhX5PURy6";
    Serial.println(googleMapLink);

    mySerial.print(googleMapLink); //text content
    updateSerial();
    mySerial.write(26);
    
  }//main-if


  if(ButtonSMSState < 400){
    ButtonSMSCondition = 0;
  }




//WaterSensorWithBaser
  if(WaterSensorState > 400){
    digitalWrite(buzzerPin, LOW);
    delay(50);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
  }

  //LDR With Buzzer With Button1
  else if(ldrState > 400 && button1State > 400){
    digitalWrite(buzzerPin, LOW);
    delay(500);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
  }



  //Ultrosonic with Buzzer
  else if(distance <= 10){
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  else{
    digitalWrite(buzzerPin, HIGH);
  }
  

}//END loop








void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}




