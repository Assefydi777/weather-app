 #define BLYNK_TEMPLATE_ID "TMPLZEWNeklT"
#define BLYNK_DEVICE_NAME "Ydidiya Assefa"
#define BLYNK_AUTH_TOKEN "nqye29rGnziTgFbDjPrLnkIpYtyj_Zju"
#define BLYNK_PRINT Serial
#define tempPin A0 
#define waterPin A1
#define LED_WARN 1
#define THRESHOLD 300

#define BLYNK_PRINT SerialUSB 
#include <ArduinoMqttClient.h> 
#include <SPI.h> 
#include <WiFi101.h> 
#include <BlynkSimpleWiFiShield101.h> 
#include "secret.h" 


WiFiClient wifiClient; 
MqttClient mqttClient(wifiClient); 
 
const char broker[] = "test.mosquitto.org";  //your broker here is mosquitto  
int port= 1883;  //channel of the broker 
//topics, you can change the name 
const char topic[]  = "Primary"; 
const char topic2[]  = "Secondary"; 
 
//set interval for sending messages (milliseconds) 
const long interval = 8000; 
unsigned long previousMillis = 0; 
 
int count = 0; 

 
// Your WiFi credentials. 
// Set password to "" for open networks. 
char ssid[] = SECRET_SSID; 
char pass[] = SECRET_PASS; 
char auth[] = BLYNK_AUTH_TOKEN; 
 
void setup() { 
  // Debug console 
  SerialUSB.begin(115200);  
  Blynk.begin(auth, ssid, pass); //start blynk 
  // You can also specify server: 
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); 
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080); 

    //Initialize serial and wait for port to open: 
 while (!Serial) { 
    ; // wait for serial port to connect. Needed for native USB port only 
  } 
 
  // attempt to connect to Wifi network: 
  Serial.print("Attempting to connect to WPA SSID: "); 
  Serial.println(ssid); 
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) { 
    // failed, retry 
    Serial.print("."); 
    delay(5000); 
  } 
 
  Serial.println("You're connected to the network"); 
  Serial.println(); 
 
//connection to the broker 
  Serial.print("Attempting to connect to the MQTT broker: "); 
  Serial.println(broker); 
 
//connection to the broker failed 
  if (!mqttClient.connect(broker, port)) { 
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError()); 
    while (1); 
  } 
  Serial.println("You're connected to the MQTT broker!"); 
  Serial.println(); 
} 
 
void loop() { 
  Blynk.run(); 
  sensor(); 
  sensor2();

  // call poll() regularly to allow the library to send MQTT keep alive which 
  // avoids being disconnected by the broker 
  mqttClient.poll(); 
 
  unsigned long currentMillis = millis(); 
 
  if (currentMillis - previousMillis >= interval) { 
    // save the last time a message was sent 
    previousMillis = currentMillis; 
 
    //record sensor valuse 
    float heat = analogRead(tempPin) ; 
    float v = heat * (3300/1024); 
    
    float realHeat =(v - 500 ) / 10; 
    float realLight = analogRead(waterPin); 

 
//Register the temperature by the topic 
    Serial.print("Sending message to topic: "); 
    Serial.println(topic); 
    Serial.println(realHeat);
    Serial.println(realLight);

//Register the light sensor by the topic2     
    Serial.print("Sending message to topic: "); 
    Serial.println(topic2); 
    Serial.println(realLight); 
 
    // send message, the Print interface can be used to set the message contents 
  
//sending the message 
    mqttClient.beginMessage(topic); 
    mqttClient.println(realHeat);
    mqttClient.println(realLight);  
    mqttClient.endMessage(); 
 
   mqttClient.beginMessage(topic2); 
    mqttClient.print(realLight); 
    mqttClient.endMessage(); 
 
    Serial.println(); 
  }
} 
 
//sensor code  
void sensor() { 
   //delay(10000); 
   float heat = analogRead(tempPin) ; 
   float v = heat * (3300/1024); 
    
   float realHeat =(v - 500 ) / 10; 

   if (realHeat>25)
   {
    Serial.println("Turn on AC too hot at the moment.");
    }
    else if(realHeat<14)
    {
      Serial.println("Turn on Heater too cold at the moment.");
      }
      else
      {
   Serial.print("Temperature at the moment is: "); 
   Serial.print(realHeat); 
   Serial.print(" C \n"); 
        }
    
   Blynk.virtualWrite(V5, realHeat); /*V5 the pin is connected to the heat 
value , it is the number that you choose on your phone*/ 
   delay (1000); 
} 

void sensor2() { 
   //delay(10000); 
   float light = analogRead(waterPin) ; 

 
    if (light>THRESHOLD)
    {
      Serial.println("Water level to high....Warning!!");
      digitalWrite(LED_WARN,HIGH);
      delay(5000);
      }
      else
      {
       Serial.print("Water Level : "); 
       Serial.print(light); 
       Serial.print(" water level\n");
       digitalWrite(LED_WARN,LOW);
        }
    
   Blynk.virtualWrite(V1, light); /*V1 the pin is connected to the heat 
value , it is the number that you choose on your phone*/ 
   delay (200); 
} 
