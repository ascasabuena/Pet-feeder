#include <DS3231.h>
#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;

int servoPin = 5;
Servo Servo1;

DS3231  rtc(SDA, SCL);
Time t;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  rtc.begin();

  //rtc.setDOW(SUNDAY);
  //rtc.setTime(15,38,0);
  //rtc.setDate(9, 1, 2019);

  Servo1.attach(servoPin);
}

void run_servo() {
  for (int i = 0; i < 6; i++) {
    Servo1.write(180);
    delay(1000);
    Servo1.write(0);
    delay(1000);
  }
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("    ");

  t = rtc.getTime();
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  Serial.print(" ");

  Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");
  Serial.print(t.sec, DEC);
  Serial.println();

  //  delay(1000);

  //setting time to 7:00:00 am
  if ((t.hour == 2 && t.min == 9 && t.sec == 0 ) && (distance <= 15)) {
    run_servo();
  }

  //setting time to 12:00:00 pm
  if ((t.hour == 2 && t.min == 9 && t.sec == 30 ) && (distance <= 15)) {
    run_servo();
  }

  //setting time to 7:00:00 pm
  if ((t.hour == 2 && t.min == 7 && t.sec == 0 ) && (distance <= 15)) {
    run_servo();
  }
}
