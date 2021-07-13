
int val;
void setup() {
  // put your setup code here, to run once:

  pinMode(9,OUTPUT);
  pinMode(7,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  val=digitalRead(7);
  if(digitalRead(7)==LOW)
  {
    digitalWrite(9, HIGH); // sets the digital pin 13 on
    delay(100);            // waits for a second
    digitalWrite(9, LOW);  // sets the digital pin 13 off
    delay(100);            // waits for a second
  }

}
