# Smart-Mars-Rover-INO
Smart Mars Rover (SMR) is a 4-Wheel robot which is controlled by Arduino (Microcontroller), and Motor shield to control 4 motor to control direction of the Robot. SMR will have 3 modes for user to choose. 
●	Manual
●	Automatic
●	Collision avoider (system)
Manual: This mode will let the user to control the Robot by using Bluetooth. User can control the robot by Phone, Computer or any other Bluetooth devices.
Automatic: The robot will follow Dark color line on light surface. And to other process depending on the dark lines.
Collision avoider: This mode make the Robot avoid anything front of it. If robot detect it path is blocked it will change its direction.
Background:
We decided to make SMR because we wanted to demonstrate the knowledge of programming an Arduino, and also App to control Robot via computer. First process is to decide how we will control motors, the easiest way was to use Motor control shield which is built to control motor such like and use IR sensor to make Robot follow dark line. We will use Bluetooth module (HC-06) to control robot through phone or computer. The ultrasonic sensor will detect any object front of it and will give signal to Arduino. This will make the Robot do its job!
Project Description
SMR will have 4- wheels, Motor controller, IR sensors, Bluetooth module, and Ultrasonic sensor. Motor Controller has maximum 4 motor connection which is perfect for our application, 4 motor will reduce speed, reverse, and forward depending on the Arduino program. The motor controller has the capability to slow down, Reverse and forward, because it has two 743d chip which is H-Bridge. 
IR Sensors will give signal to Arduino based on color it detects on the floor, this will make the Arduino to decide which motor to turn and slow for controlling its direction. For user who will give signal to Arduino when to switch modes so the SMR will do its job. User will give command to SMR to turn when in manual mode. In Automatic mode the User will see the process on the console, like which motor is on at a speed and what it is doing when SMR detect two IR detects signal to do some process. In Collision mode SMR will neglect the IR sensor so it can read value from Ultrasonic Sensor to detect is the path its going is clear or blocked depending on the ultrasonic or program it will do its job. 
