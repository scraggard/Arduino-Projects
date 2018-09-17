#include <Servo.h>
// make it better, i.e. more secure
// perhaps use two arrays to store knock values
// and intervals
// if knock values fall between threshold and
// intervals fall between threshold (normalized)
// then it unlocks?

Servo myServo;
const int piezo = A0;
const int switchPin = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int redLED = 5;
int knockVal;
int switchVal;
const int quietKnock = 10;
const int loudKnock = 100;
boolean locked = false;
boolean reset = false;
int numberOfKnocks = 0;
int knockIntervals[100];
int knockLoudness[100];
int secretIntervals[100];
int secretLoudness[100];
int startTime;
int endTime;
const int cutOff = 3000; // milliseconds

void setup() {
  myServo.attach(9);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  digitalWrite(greenLED, HIGH);
  myServo.write(0);
  Serial.println("The box is unlocked!");
}

void loop() {
  endTime = millis();
  if (reset) {
    endTime, startTime = 0;
    int knockIntervals[100];
    int knockLoudness[100];
    for (int i = 0; i <= 5; i++) {
      digitalWrite(redLED, LOW);
      delay(100);
      digitalWrite(redLED, HIGH);
      delay(100);
    }
    reset = false;
  }
  if (!locked) {
    switchVal = digitalRead(switchPin);
    if (switchVal == HIGH) {
      locked = true; 
      startTime = millis();
      endTime = millis();
      int index = 0;
      Serial.println("Starting recording of secret knocks");
      while (endTime - startTime < cutOff && index < 100) {
        knockVal = analogRead(piezo);
        endTime = millis();
        if (knockVal > 10 && index < 100) {
          secretLoudness[index] = knockVal;
          secretIntervals[index] = endTime - startTime;
          Serial.print("Knock Value: ");
          Serial.println(secretLoudness[index]);
          Serial.print("Interval: ");
          Serial.println(secretIntervals[index]);
          startTime = millis();
          index++;
        }
      }
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      myServo.write(90);
      Serial.println("The box is locked!");
      delay(1000);
    }
  }
  if (locked) {
    startTime = millis();
    endTime = millis();
    int index = 0;
    while (endTime - startTime < cutOff && index < 100) {
      knockVal = analogRead(piezo);
      endTime = millis();
      if (knockVal > 10 && index < 100) {
        knockLoudness[index] = knockVal;
        knockIntervals[index] = endTime - startTime;
        Serial.print("Knock value: ");
        Serial.println(knockLoudness[index]);
        Serial.print("Interval: ");
        Serial.println(knockIntervals[index]);
        startTime = millis();
        index++;
      }
    }
    if (checkSecrets(knockIntervals, secretIntervals, 0) && 
      checkSecrets(knockLoudness, secretLoudness, 1)) {
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      Serial.println("The box is unlocked!");
    }
    else {
      Serial.println("Knock incorrect!");
      reset = true;
    }
  }
}

boolean checkForKnock(int value){
  if (value > quietKnock && value < loudKnock) {
    digitalWrite(yellowLED, HIGH);
    delay(50);
    digitalWrite(yellowLED, LOW);
    Serial.print("Valid knock of value ");
    Serial.println(value);
    return true;
  }
  else {
    Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
}

boolean VerifyKnocks(int knockIntervals[100], 
  int knockLoudness[100]){
    boolean intervals = false;
    boolean loudness = false;
    if (checkSecrets(knockIntervals, secretIntervals, 0)) {
      intervals = true;
    }
    if (checkSecrets(knockLoudness, secretLoudness, 1)){
      loudness = true;
    }
    return (intervals && loudness);
}

boolean checkSecrets(int knock[100], 
  int secret[100], int type) {
    int threshold;
    if (type == 0) { // intervals
      threshold = 100000; // milliseconds
    }
    else {
      threshold = 100000; // loudness value
    }
    for (int i = 0; i < 100; i ++) {
      if ((knock[i] >= secret[i] + threshold) && 
        (knock[i] <= secret[i] - threshold)) {
          continue;
        }
      else {
        return false;
      }
    }
    return true;
}
