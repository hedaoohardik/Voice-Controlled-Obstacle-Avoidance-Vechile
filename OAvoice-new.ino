#include <NewPing.h>

#include <SoftwareSerial.h>





SoftwareSerial BT(0, 1); //TX, RX respetively
String readvoice;
int trigPin = 10;      // trig pin of HC-SR04
int echoPin = 12;     // Echo pin of HC-SR04
#define MAX_DISTANCE 200

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
long duration, distance;

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(4, OUTPUT);// back right
  pinMode(5, OUTPUT);//front right
  pinMode(6, OUTPUT);//back left
  pinMode(7, OUTPUT);//front left
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves
  

}
//-----------------------------------------------------------------------//  
void loop() {
  while (BT.available())
  {  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = BT.read(); //Conduct a serial read
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readvoice.length() > 0) {
    Serial.println(readvoice); 
  
delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  pinMode(echoPin,OUTPUT);

digitalWrite(echoPin,LOW);

pinMode(echoPin,INPUT);
  Serial.print("Ping: ");
  distance=sonar.convert_cm(uS);
  Serial.print(distance); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");

 
  
  if (distance >= 5 )
  {
  if(readvoice == "forward") 
  {
    digitalWrite(5, HIGH);
    digitalWrite (7, HIGH);
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
    delay(100);
  } 
  
  else if(readvoice == "backward") 
  {
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(6,HIGH);
    delay(100);
  }
  
  else if (readvoice == "right")
  {
    digitalWrite (5,HIGH);
    digitalWrite (7,LOW);
    digitalWrite (4,LOW);
    digitalWrite (6,LOW);
    delay (100);
    
  }
  
 else if ( readvoice == "left")
 {
   digitalWrite (5, LOW);
   digitalWrite (7, HIGH);
   digitalWrite (4, LOW);
   digitalWrite (6, LOW);
   delay (100);
 }
  
 
 else if (readvoice == "stop")
 {
   digitalWrite (5, LOW);
   digitalWrite (7, LOW);
   digitalWrite (4, LOW);
   digitalWrite (6, LOW);
   delay (100);
 }

 
 else if (distance < 5)
{       
Serial.println ("Close Obstacle detected!" );
Serial.println ("Obstacle Details:");
Serial.print ("Distance From Robot is " );
Serial.print ( distance);
Serial.print ( " CM!");// print out the distance in centimeters.

    digitalWrite(5, LOW);  //Stop                
    digitalWrite(4,LOW);
    digitalWrite(7, LOW);                                
    digitalWrite(6, LOW);
    delay(500);
    digitalWrite(5, LOW);      //movebackword         
    digitalWrite(4,HIGH);
    digitalWrite(7, LOW);                                
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(5, LOW);  //Stop                
    digitalWrite(4,LOW);
    digitalWrite(7, LOW);                                
    digitalWrite(6, LOW);  
    delay(100); 
    Serial.println("Give another command!");
}

readvoice=""; //Reset the variable
     
}
  
  else if (distance < 5)
{       
   Serial.println ("Close Obstacle detected!" );
Serial.println ("Obstacle Details:");
Serial.print ("Distance From Robot is " );
Serial.print ( distance);
Serial.print ( " CM!");// print out the distance in centimeters.

   digitalWrite (5, LOW);
   digitalWrite (7, LOW);
   digitalWrite (4, LOW);
   digitalWrite (6, LOW);
   delay (100);
   Serial.println("Give another command!");
}
  
 
   

readvoice="";}} //Reset the variable
