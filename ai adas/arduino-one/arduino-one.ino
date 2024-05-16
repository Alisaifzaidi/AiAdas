// Motors pins
#include <NewPing.h> 
char sleep_status = 0;
const int rmfPin = 2;
const int lmfPin = 4 ;
const int rmbPin = 3;
const int lmbPin = 5;
const int motorSpeedPin=6;
const int bzrPin=7;
const int led_Pin = 12;
// Auto-braking pins
int triggerPin = 10;
int echoPin = 11; 
// Pathhole pins
int triggerpath = 8;
int echopath = 9;
const int leftIRPin = A0;
const int rightIRPin = A1;
int MAX_DISTANCE =400;
const int threshold=20;
const int whiteThreshold = 500;
long duration;
long cm;
// Pathhole
int pathholeThreshold = 70; // Adjust this threshold as needed
long distance;
long inch;
NewPing sonar(triggerPin, echoPin, MAX_DISTANCE);
void Spinforward(); 
void Turnleft();
void Turnright();
void Stopmotor();

void setup() {
  Serial.begin(9600);
  pinMode(motorSpeedPin,OUTPUT);
  pinMode(bzrPin, OUTPUT);
  pinMode(led_Pin, OUTPUT);

  pinMode(rmfPin, OUTPUT);
  pinMode(lmfPin, OUTPUT);
  pinMode(rmbPin, OUTPUT);
  pinMode(lmbPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);
  
  pinMode(triggerpath, OUTPUT);
  pinMode(echopath, INPUT);
  
  digitalWrite(led_Pin, LOW);
  Spinforward(); // Start by moving forward
}

void loop() {
  // Trigger the ultrasonic sensor for obstacle detection
    
      

  


  // Trigger the ultrasonic sensor for pathhole detection
  digitalWrite(triggerpath, LOW);
  delayMicroseconds(0);
  digitalWrite(triggerpath, HIGH);
  delayMicroseconds(0);
  digitalWrite(triggerpath, LOW);
  distance = pulseIn(echopath, HIGH);

  // Calculate the distance in centimeters
  inch = (distance * 0.0343) / 2;

  Serial.print("Pathhole: ");
  Serial.println(inch);

   
  


 
      digitalWrite(triggerPin, LOW);
      //delayMicroseconds(0);
      digitalWrite(triggerPin, HIGH);
      //delayMicroseconds(0);
      digitalWrite(triggerPin, LOW);

      // Measure the duration of the echo pulse
      duration = pulseIn(echoPin, HIGH);

      // Calculate the distance in centimeters
      cm = (duration * 0.0343) / 2;

      Serial.print("Distance break: ");
      Serial.println(cm);

      //line();
             int leftIRValue = analogRead(leftIRPin);
      int rightIRValue = analogRead(rightIRPin);
      Serial.print("Left IR: ");
      Serial.println(leftIRValue);
      Serial.print("Right IR: ");
      Serial.println(rightIRValue);
      




  // Handle commands received from Serial Monitor
  while (Serial.available() > 0) {
    sleep_status = Serial.read();
    if (sleep_status == 'a') {

               if (leftIRValue <= 500 && rightIRValue <= 500 ) {
        Stopmotor();
      }
       else if (leftIRValue <= 500) {
       
        Turnright();
        //delay(200);
      } else if (rightIRValue <= 500) {
        
       Turnleft();
      }
      //ultra soinc
      else if (cm > 31){
        Spinforward();
      }
      else if(cm>=10 && cm<30){
        Stopmotor();
      }
      else if(cm>=0 && cm<10){
        BAck();
      }
 
      else if (inch < pathholeThreshold) {
      // Pathhole detected, slow down the motor
      analogWrite(motorSpeedPin, 100);
      //Spinforward(); // Adjust the delay time for slower speed
     
      }
      else{
        Spinforward();
      }


      //pathhole
      
    } else if (sleep_status == 'b') {
      digitalWrite(bzrPin, LOW);
      digitalWrite(led_Pin, LOW);
      Spinforward();
    } else {
      // Do Nothing
    }
  }
}





void Stopmotor() {
  digitalWrite(lmfPin, LOW);
  digitalWrite(rmfPin, LOW);
  digitalWrite(lmbPin,LOW);
  digitalWrite(rmbPin,LOW);
  //Serial.println("myfunction");
  //delay(delay_time);
}

void Spinforward() {
  digitalWrite(lmfPin, HIGH);
  digitalWrite(rmfPin, HIGH);
  digitalWrite(lmbPin,LOW);
  digitalWrite(rmbPin,LOW);
 
}

void Turnleft() {
  digitalWrite(lmfPin, LOW);
  digitalWrite(rmfPin, HIGH);
  digitalWrite(lmbPin,HIGH);
  digitalWrite(rmbPin,LOW);
  //delay(delay_time);
}

void Turnright() {
  digitalWrite(lmfPin, HIGH);
  digitalWrite(rmfPin, LOW);
  digitalWrite(lmbPin,LOW);
  digitalWrite(rmbPin,HIGH);
  //delay(delay_time);
}

void BAck() {
  digitalWrite(lmfPin, LOW);
  digitalWrite(rmfPin, LOW);
  digitalWrite(lmbPin,HIGH);
  digitalWrite(rmbPin,HIGH);
  //delay(delay_time);
}


