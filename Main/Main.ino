#define trigPin 9
#define echoPin 10

const int buzzerPin = 13;
long duration, distance;

const int vcc = 8;  
const int gnd = 11;  


void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud rate
  pinMode(trigPin, OUTPUT);  // Set the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Set the echoPin as an INPUT
  pinMode(buzzerPin, OUTPUT);

  // Create versual VCC AND GND
  pinMode(vcc, OUTPUT);  
  pinMode(gnd, OUTPUT); 
  digitalWrite(vcc, HIGH);  
  digitalWrite(gnd, LOW);
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
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);  // Wait for 500 milliseconds before the next reading


}






void obstacleDetect(){
  
}
