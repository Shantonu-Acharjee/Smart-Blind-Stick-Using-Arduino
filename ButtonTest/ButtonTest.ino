const int Button1 = A5;
int ButtonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Button1, INPUT);
}

void loop(){

  ButtonState = analogRead(Button1);
  Serial.println(ButtonState);

}