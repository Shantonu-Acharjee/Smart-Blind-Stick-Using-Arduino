const int buzzerPin = 13; 


void setup() {
  
  pinMode(buzzerPin, OUTPUT); 
  digitalWrite(buzzerPin, HIGH);  
  
}



void loop(){
  
  digitalWrite(buzzerPin, HIGH); 
  delay(1000);
  digitalWrite(buzzerPin, LOW); 
  delay(1000);
  
}