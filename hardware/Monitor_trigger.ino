#include <IRremote.h>

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;

// Create IR Send Object
IRsend irsend;

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  Serial.println(distanceCm);
  Serial.print("Duration: ");
  Serial.println(duration);
  delay(1000);
  
  // If close by send power code command
   if (distanceCm < 50) {
   irsend.sendNEC(0x61A0F00F, 32); // TV power code
  }
  else
  {
    irsend.sendNEC(0x61A0F00F, 32); // TV power code
    }
   
    // Add a small delay before repeating
    delay(200);
 
} 
