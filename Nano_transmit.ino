int potentiometer=A0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  int potval = analogRead(potentiometer);
  //Serial.println(potval);
  byte potval_1 = map(potval,330,645,0,255);
  //Serial.print(potval_1);
  Serial.write(potval_1);
  delay(20);

}
