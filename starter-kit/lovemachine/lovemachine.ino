const int anInNum = A0;
const float baseTemp = 20.0;
void setup() {
  Serial.begin(9600);
  for(int pin = 3; pin < 6; pin++){
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void loop() {
  int senVal = analogRead(anInNum);
  Serial.print("Sensor value: ");
  Serial.print(senVal);
  float voltage = (senVal/1024.0)*5.0;
  Serial.print(" , Volts: ");
  Serial.print(voltage);
  float temp = (voltage - 0.5) * 100;
  Serial.print(" , degrees C: ");
  Serial.println(temp);
  if (temp < baseTemp){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else if (temp >= baseTemp + 2 && temp < baseTemp + 4){
    digitalWrite(3, HIGH); 
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else if (temp >= baseTemp + 4 && temp < baseTemp + 6){
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  else {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
  delay(1);
 }
