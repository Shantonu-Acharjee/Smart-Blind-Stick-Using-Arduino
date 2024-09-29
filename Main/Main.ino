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
}

void loop() {


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



  //WaterSenosr---------------------------------------------------------
  WaterSensorState = analogRead(WaterSensor);
  Serial.println(WaterSensorState);


  //LDR With Buzzer With Button1

  ldrState = analogRead(ldrPin);
  button1State = analogRead(button1Pin);














  //Ultrosonic with Buzzer
  if(distance <= 20){
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  //WaterSensorWithBaser
  if(WaterSensorState > 400){
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
  }

  //LDR With Buzzer With Button1
  if(ldrState > 400 && button1State > 400){
    digitalWrite(buzzerPin, LOW);
  }

  else{
    digitalWrite(buzzerPin, HIGH);
  }





}//END loop







