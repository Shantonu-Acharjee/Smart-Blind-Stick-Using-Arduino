const int WaterSensor = A0;
int WaterSensorState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(WaterSensor, INPUT);
}


void loop() {
  WaterSensorState = analogRead(WaterSensor);
  Serial.println(WaterSensorState);

}