/***************************************************
 Summer Internship Project  
 ****************************************************/
#include <string.h>
#include <ESP8266WiFi.h>
int i = 0;
int water_count = 0;
int Echo = 5;
int Trig = 4;
int Duration;
float Distance;
int Led = 0;
int Relay = 2;
int Buzzer = 12;    

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  delay(1000);
 
  //Ultrasonic Sensor
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);

  //LED
  pinMode(Led,OUTPUT);

  //relay
  pinMode(Relay, OUTPUT);

  //piezo speaker
  pinMode(Buzzer, OUTPUT); 
}

void loop() {
  
  //Check soil humidity once a minute.
  if(i == 1){
    checkWater();
    checkMoisture();
  }

  delay(10000);//10sec
  i++;
  
  if(i >= 6){
    i = 0;
  }

  checkWater();
}


//Ultrasonic Sensor
void checkWater(){
  digitalWrite(Trig,LOW);
  delayMicroseconds(1);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(11);
  digitalWrite(Trig,LOW);
  Duration = pulseIn(Echo,HIGH);
  
  if (Duration>0) {
    Distance = Duration/2;
    Distance = Distance*340*100/1000000; 
    Serial.print(Distance);
    Serial.println(" cm");
    
    if(Distance > 12){
      digitalWrite(Led, HIGH);
    }else{
      digitalWrite(Led, LOW);
    }
    
  }
}

//moisture sensor
void checkMoisture(){
  //Measure soil humidity
  int moisture = analogRead(A0);
  Serial.print("Moisture Sensor Value:");
  Serial.println(moisture);
  Serial.println(0, 1);
  Serial.println("Moisture: " + String(moisture) + "   ");
  
  if(moisture <= 300){
    water_count++;
    if(water_count == 5){//To wait for the water to go through the pot.
      watering();
      water_count = 0;
    }
  }
}


//Watering
void watering(){
  digitalWrite(Relay, HIGH);
  delay(2000);
  digitalWrite(Relay, LOW);
  delay(8000);
  completeWatering();
  i++; 
}


//piezo speaker
void completeWatering(){        
   tone(Buzzer, 2000)  ;     
   delay(1000);                
   noTone(Buzzer)      ;    
   delay(1000);         
  i++;
  checkMoisture();
  int moisture = analogRead(A0);
  Serial.println("Moisture: " + String(moisture) + "   ");
}
