#include <IRremote.h>//has to be IR library by Ken S. 2.0 not 3.0

const int POTENTIOMETER_PIN = A0; // Arduino pin connected to Potentiometer pin
const int Speaker        = 6; // Arduino pin connected to Buzzer's pin
const int trigPin = 9;
const int echoPin = 10;
const int RedLed  = 13;
const int BlueLed = 12;  
//const int IR      = 3;
long duration;
int distanceCm, distanceInch;
int val = 0;         // variable to store the read value

// Create IR Send Object
IRsend irsend;

void setup() {
  //Baud rate
  Serial.begin (9600);
   //sets the pin as input
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(echoPin, INPUT);
  // sets the pin as output
  pinMode(Speaker, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(RedLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  //pinMode(IR, OUTPUT);
  
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  val = analogRead(POTENTIOMETER_PIN);  // read the input pin to engage
  distanceCm = duration * 0.034 / 2;
  Serial.println(distanceCm);
  
  
  // If close by send power code command
   if (distanceCm > 15 && distanceCm < 55) {
   irsend.sendNEC(0x61A0F00F, 32); // TV Power code
   //irsend.sendNEC(0x61A00AF5, 32); // TV channelcode code
  // digitalWrite(3, HIGH);
    digitalWrite(RedLed,LOW);
    digitalWrite(BlueLed,LOW);
    analogWrite(Speaker, LOW); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    delay(2000); //debounce
  }
  else if(distanceCm > 2 && distanceCm < 15)
  {
    analogWrite(Speaker, val/4); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    digitalWrite(3, LOW);
    digitalWrite(RedLed,HIGH);
    digitalWrite(BlueLed,LOW);
    delay(500);
    digitalWrite(RedLed,LOW);
    digitalWrite(BlueLed,HIGH);
    Serial.println("Too close..... Warning!!");
  
    }

  else if(distanceCm >150)
  {
   //irsend.sendNEC(0x61A0F00F, 32); // TV Power code
   //irsend.sendNEC(0x61A00AF5, 32); // TV channelcode code
  // digitalWrite(3, HIGH);
    digitalWrite(RedLed,LOW);
    digitalWrite(BlueLed,LOW);
    analogWrite(Speaker, LOW); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    delay(2000); //debounce
    Serial.println("Out of Range");
    
    }
    // Add a small debounce delay before repeating 
   delay(200);
}
