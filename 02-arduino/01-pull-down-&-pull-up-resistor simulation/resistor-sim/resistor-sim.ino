const int buttonPin1 = 7;
const int buttonPin2 = 6;
int buttonState1 = 0;
int buttonState2 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  Serial.println("Button 1 state: " + String(buttonState1) + ", Button 2 state: " + String(buttonState2));
  delay(200);
}
