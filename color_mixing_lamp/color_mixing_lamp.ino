const int gLEDPin = 9;
const int bLEDPin = 10;
const int rLEDPin = 11;

const int rSensorPin = A0;
const int gSensorPin = A1;
const int bSensorPin = A2;

int rVal = 0;
int gVal = 0;
int bVal = 0;

int rSensorVal = 0;
int gSensorVal = 0;
int bSensorVal = 0;

void setup() {
  Serial.begin(9600);

  pinMode(gLEDPin, OUTPUT);
  pinMode(rLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);
}

void loop() {
  rSensorVal = analogRead(rSensorPin);
  delay(5);
  gSensorVal = analogRead(gSensorPin);
  delay(5);
  bSensorVal = analogRead(bSensorPin);
  Serial.print("Raw sensor values \t Red: ");
  Serial.print(rSensorVal);
  Serial.print("\t Green: ");
  Serial.print(gSensorVal);
  Serial.print("\t Blue: ");
  Serial.println(bSensorVal);

  rVal = rSensorVal/4;
  gVal = gSensorVal/4;
  bVal = bSensorVal/4;

  Serial.print("Mapped Sensor Values \t Red: ");
  Serial.print(rVal);
  Serial.print("\t Green: ");
  Serial.print(gVal);
  Serial.print("\t Blue: ");
  Serial.print(bVal);
  analogWrite(rLEDPin, rVal);
  analogWrite(gLEDPin, gVal);
  analogWrite(bLEDPin, bVal);
}
