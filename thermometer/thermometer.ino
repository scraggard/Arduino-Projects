#include <Servo.h>
Servo myServo;
const int tempPin = A0;
const int servoPin = 9;
int angle;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int tempVal = analogRead(tempPin);
  Serial.print("Sensor Value: ");s
  Serial.println(tempVal);
  float voltage = (tempVal/1024.0)*5.0;
  Serial.print("Voltage Value: ");
  Serial.println(voltage);
  float temperature = (voltage - .5)*100;
  Serial.print("Degrees C: ");
  Serial.println(temperature);
  angle = map(tempVal, 122.88, 174.08, 0, 179);
  Serial.print("Angle: ");
  Serial.println(angle);
  myServo.write(angle);
  delay(1000);
}
