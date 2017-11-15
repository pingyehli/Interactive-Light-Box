/*
 * Arduino Code for:
 * Interactive Light Box using Ultrasonic sensor, relay module, and 12V LED strip.   
 * By Ping-Yeh Li. 2017. 
 * 
  HC-SR04 Ping distance sensor Connection:
  VCC to Arduino 5v
  GND to Arduino GND
  Echo to Arduino pin 12 
  Trig to Arduino pin 11
  More info at: https://www.hackster.io/ammaratef45/detecting-obstacles-and-warning-arduino-and-ultrasonic-13e5ea

  Relay Module Connection:
  VCC to Arduino 5v
  GND to Arduino GND
  Relay DAT Pin to Arduino pin 10
*/

#define trigPin 11
#define echoPin 12
#define relayPin 10

int sum_distance = 0;
int average_distance = 0;
int count = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
}


void loop() {
  float duration, distance;

  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  //Serial.print("DATA,");
  //Serial.print(time);
  //Serial.print(",");
  //Serial.println(distance);

  distance = constrain(distance, 0, 300);
  //Serial.println(distance);

  // add the distance up, until got the count nunber
  sum_distance = sum_distance + distance;
  count = count + 1;  // 0 --> 1 --> 2 --> 3 -->

  if (count >= 5) {
    average_distance = sum_distance / count;
    //Serial.println(average_distance);
    count = 0;
    sum_distance = 0;
  }

  delay(10);

  if (average_distance <= 220) {
    digitalWrite(13, HIGH);
    digitalWrite(relayPin, HIGH);
    delay(30);
  } else {
    digitalWrite(13, LOW);
    digitalWrite(relayPin, LOW);
    delay(30);
  }
}
