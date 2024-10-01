#define trigPin 8
#define echoPin 10
#define buzzerP A2
#define buzzerN A5
#define waterSensor A0
const int buzzerPin = 13;
long duration, distance;

void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);  // Set the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Set the echoPin as an INPUT
  pinMode(buzzerPin, OUTPUT);

  pinMode(buzzerP, OUTPUT);
  pinMode(buzzerN, OUTPUT);
  pinMode(waterSensor, INPUT);
}

void loop() {
  int waterState = analogRead(waterSensor);

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
  Serial.print("Distance: ");
  Serial.print(distance);  // Print the calculated distance
  Serial.print(" cm, Water State: ");
  Serial.println(waterState);  // Print the water state
  delay(300);  // Wait for 300 milliseconds before the next reading

  // Ultrasonic with Buzzer
  if (distance <= 20) {
    digitalWrite(buzzerP, 1);
    digitalWrite(buzzerN, 0);
    delay(500);
  }
  else if (waterState > 100) {
    digitalWrite(buzzerP, 1);
    digitalWrite(buzzerN, 0);
    delay(100);
    digitalWrite(buzzerP, 0);
    digitalWrite(buzzerN, 0);
  }
  else {
    digitalWrite(buzzerP, 0);
    digitalWrite(buzzerN, 0);  // Fixed the else block
  }
}
