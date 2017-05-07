#include <AFMotor.h> // motor shield lib  
#include <SoftwareSerial.h> // import the serial lib
//ulraSonic define pins
#define trigPin 21 //read ulrasonic wave from this pin
#define echoPin 20 // send echo send


AF_DCMotor motor2(2,MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor1(1,MOTOR12_64KHZ);// create motor #1, 64KHz pwm
AF_DCMotor motor3(3,MOTOR34_64KHZ);// create motor #3, 64KHz pwm
AF_DCMotor motor4(4,MOTOR34_64KHZ);// create motor #4, 64KHz pwm
int LeftS=A8; // left IR sensor
int RightS=A9; // Right IR Sensor

int LS = 0; // left IR sensor variable to 0
int RS = 0; // right IR sensor variable to 0

int counter = 0; //counter to check did the both sensor came across straight line

int red = 52; // red led
int blue = 48; // blue led
int green = 50; // green led

char incomingByte; // declare incoming byt variable
char Mode; // declare mode selection variable

 int distance; // declare distance var
  int counter1 ; // counter1 var
void setup() {

Serial.begin(9600); // serial monitor for Blutooth chip 


pinMode(LeftS,INPUT); // left sensor as input
pinMode(RightS,INPUT); // right sensor as input

pinMode(red,OUTPUT); //red light as output
pinMode(blue,OUTPUT); // and so on ...
pinMode(green,OUTPUT);

   motor4.setSpeed(150);  // set the speed of motor
   motor3.setSpeed(150);  // speed to 200 pwn
  motor2.setSpeed(150); 
  motor1.setSpeed(150); // set the speed to 200/255
  // Check motor and outher output connected 
  Check_System() ; 
  // check complete
Serial.println("Motor Check Complete");
Serial.write("Motor Check Complete!");
Serial.println();
Serial.println("Checking Mode");
Serial.write("Checking Mode");
 Serial.println();
 Serial.println("StandBy Mode");
  Serial.write("StandBy Mode");

  pinMode(trigPin, OUTPUT); // define pin
  pinMode(echoPin, INPUT); //...
}

void loop() {
  if (Serial.available() ) // check if serial has any bit coming through
  {
    incomingByte = Serial.read(); // put the value in varaible because the serial comes in ascii change it into integer
    Serial.println(incomingByte); Serial.write(incomingByte); // print the feedback to serial comunication!
    if (incomingByte == 'A') // if Serial or bluetooth recieves A then put that in Mode var
    {
      Mode = 'A'; // Assign 'A' to Mode
    }
    else if (incomingByte == 'M') // Same thing M as Manual
    {
      Mode = 'M'; // so on ...
    }
    else if (incomingByte == 'C')
    {
      Mode = 'C';
    }
    else if (incomingByte == 'S')
    {
      Mode = 'S';
    }
  //  Serial.println(incomingByte); // debug
  }
LS = digitalRead(LeftS); // read the value from sensor as 0 and 1s
RS = digitalRead(RightS); // put them in assigned variable
//Serial.println(LS); // print left sensor value for troubleshooting

if (Mode == 'A') // if Mode var is A then go Automatic
{
  digitalWrite(blue,LOW);// send the feed back to leds to show user that Robot is going in Automatic Mode
  digitalWrite(red,LOW);
digitalWrite(green,HIGH);

  if (counter1 == 0) // counter for making sure this print only apear once 
  {
  Serial.println("AutoMatic Mode activated"); //Show user that Byte is recieved and process to go in Automatic mode
   Serial.write("AutoMatic Mode activated");
  counter1++; // counter1 var ++ increase it by one
  }
  AutoMovement(); // then call Automatic Funcition
  delay (50); // delay of 50 just in case 
}
else if (Mode == 'M') // if Mode is M then go manuel
{
  digitalWrite(blue,HIGH); // show the feed back with LED
  delay(100);
  digitalWrite(blue,LOW);
  digitalWrite(red,LOW);
digitalWrite(green,LOW);
   if (counter1 == 0) // make sure this feedback print once
  {
  Serial.println("Manual Mode activated"); // show it on the terminal for debug and let user know that Robot went in Manuel Mode
  counter1++;
  }
 
  if (incomingByte == 'F') // if user command it F then move Forward
  {
     Serial.println("Moving Forward"); // give feedback
    Forward(); // move it Forward
    delay(100); // delay of 100 ms
    
  }
   if (incomingByte == 'R') // if condition for turning right
  {
     Serial.println("Turning Right"); // show feed back
     
    Right();
     delay(100);
    
  }
  if (incomingByte == 'L') //if condition for turning left
  {
      Serial.println("Turning Left");
    Left();
     delay(100);
   
  }
   if (incomingByte == 'B') //if condition for turning back
  {
      Serial.println("Moving Backward");
   Backward();
    delay(100);
  
   
  }
  if (incomingByte == 'K') // tell the robot to stop!
  {
    Serial.println("Stop!");
 motor4.run(RELEASE);      
  motor3.run(RELEASE);
motor2.run(RELEASE);      
 motor1.run(RELEASE);
  delay (100);
 
  }
   incomingByte = 9;
}
else if (Mode == 'C')
{
 distance = Collision_system();
  if (distance > 15)
  {
    Forward();
  }
  else if(distance < 15)
  {
    Backward();
    delay ( 600);
    int random_value = random(1,2);
   if (random_value == 1)
   {
    Right();
    delay(500);
    random_value = 0;
   }
   else if (random_value==2)
   {
    Left();
    delay(500);
    random_value = 0;
   }
   else if (distance < 8)
   {
    Serial.println("Stop!");
 motor4.run(RELEASE);      
  motor3.run(RELEASE);
motor2.run(RELEASE);      
 motor1.run(RELEASE);
   }
   
  } 
}
else if (Mode == 'S')
{
  counter1 = 0;
  counter = 0;
   motor4.run(RELEASE);      
  motor3.run(RELEASE);
motor2.run(RELEASE);      
 motor1.run(RELEASE);
}


 
}


// Motion functions >>
int Forward()
{

    motor4.run(FORWARD);      // turn it on going forward
  motor3.run(FORWARD);
motor2.run(FORWARD);      // turn it on going forward
 motor1.run(FORWARD);
 
  incomingByte = 9;
}
int Right()
{
   motor4.run(BACKWARD);      // turn it on going forward
  motor3.run(FORWARD);
motor2.run(FORWARD);      // turn it on going forward
 motor1.run(BACKWARD);
  
  incomingByte = 9;
}

int Left ()
{
   motor4.run(FORWARD);      // turn it on going forward
  motor3.run(BACKWARD); // turn it on going backward
motor2.run(BACKWARD);      // turn it on going forward
 motor1.run(FORWARD);
 
  incomingByte = 9;
}

int Backward()
{
    motor4.run(BACKWARD);      // turn it on going forward
  motor3.run(BACKWARD); // turn it on going backward
motor2.run(BACKWARD);      // turn it on going forward
 motor1.run(BACKWARD);
 
  incomingByte = 9;
}
int Stop()
{
  motor4.run(RELEASE);      
  motor3.run(RELEASE);
motor2.run(RELEASE);      
 motor1.run(RELEASE);
 incomingByte = 9;
}

// automode movement and algrothems
int AutoMovement ()
{
  LS = digitalRead(LeftS); // read the value from sensor as 0 and 1s
RS = digitalRead(RightS); // put them in assigned variable
Serial.println(LS); // print left sensor value for troubleshooting


if ( LS == 0  && RS == 0) //if both sensor read no black line then keep going straight
{
     motor4.run(FORWARD);      // turn it on going forward
  motor3.run(FORWARD);
motor2.run(FORWARD);      // turn it on going forward
 motor1.run(FORWARD);
}
if (LS == 1 && RS == 0) // if the left sensor detects line the turn left
{
   motor4.run(FORWARD);      // turn it on going forward
  motor3.run(BACKWARD); // turn it on going backward
motor2.run(BACKWARD);      // turn it on going forward
 motor1.run(FORWARD);
}

if (LS == 0 && RS == 1) // if right sensor detects line the turn right
{
   motor4.run(BACKWARD);      // turn it on going forward
  motor3.run(FORWARD);
motor2.run(FORWARD);      // turn it on going forward
 motor1.run(BACKWARD);
}
if (LS == 1 && RS == 1) // if both sensor detects line then counter ++
{
  counter++;
  delay (100);
}
if (counter == 1) //if counter is one then stop the motors and turn on the red light to show that robot has detected straight line
{
  motor4.run(RELEASE);      // turn it on going forward
  motor3.run(RELEASE);
motor2.run(RELEASE);      // turn it on going forward
 motor1.run(RELEASE);

digitalWrite(red,HIGH);
 
 delay (1000);
  motor4.run(FORWARD);      // turn it on going forward
  motor3.run(FORWARD);
motor2.run(FORWARD);      // turn it on going forward
 motor1.run(FORWARD);
 delay(100);
 
 digitalWrite(red,LOW);
 counter++;
}

if (counter > 4) // if sensor detects straight line 4 times then stop the robot and show that it has came to the end
{
  motor4.run(RELEASE);      // turn it on going forward
  motor3.run(RELEASE);
motor2.run(RELEASE);      // turn it on going forward
 motor1.run(RELEASE);
for (int x = 0; x < 20 ; x++)
{
digitalWrite(red,HIGH);
 delay ( 100);
 digitalWrite(red,LOW);
 delay ( 100);
}
 
}
 // refresh the program every 1 ms

}
 // collision system functions
 
int Collision_system()
{
   long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
  }
  
} 

int Check_System()
{
  Right();
   digitalWrite(blue,LOW);
  digitalWrite(red,HIGH);
digitalWrite(green,LOW);
  delay (400);
  Left(); 
  digitalWrite(blue,LOW);
  digitalWrite(red,LOW);
digitalWrite(green,HIGH);
delay (100);
 digitalWrite(blue,LOW);
  digitalWrite(red,HIGH);
digitalWrite(green,LOW);
delay (100);
 digitalWrite(blue,HIGH);
  digitalWrite(red,LOW);
digitalWrite(green,LOW);
  delay (200);
  Stop();
 digitalWrite(blue,LOW);
  digitalWrite(red,LOW);
digitalWrite(green,LOW);

}

