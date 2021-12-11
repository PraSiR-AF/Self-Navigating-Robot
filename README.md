# Self-Navigating-Robot
This project entails developing a robot capable of autonomously navigating a maze using only body mounted sensors. 

Contributors :
1)	Pratul Singh Raghava 
2)	Matan Cohen 
3)	Amanda Walpitage 
4)	Aagrath Yadav 

INTRODUCTION

The project entailed developing a robot capable of autonomously navigating a maze using only body mounted sensors. In order to optimise the development process, the project was divided into two main parts: 1) the design and development of a virtual robot with photovoltaic sensors and servo-mounted wheels controlled by an Arduino, and 2) the development of a maze navigating algorithm in C capable of being integrated with the physical robot. 

The culmination of these two sections is a robot with photovoltaic sensors that detect proximity to a wall, and relay signals to wheels to rotate and propel the robot as necessary to avoid collisions while traversing a maze. The robot also does not require any prior programming of maze routes, nor does it need repeated runs through a maze to learn routes. 

SOFTWARE IMPLEMENTATION

The code uses a right-hand rule maze solving algorithm, which essentially finds a wall in the maze, moves so the right sensors of the robot are tracking that wall, and follows it until it reaches the exit.

We implemented a function that uses a different movement ‘code’ for each possible scenario, eg. a wall in front of and to the left of the robot: move right (code = 4). Due to the numerous scenarios, which need to account for all 4 sensors placed on the robot and all their possible combinations, the Movement Function contains many conditional statements. These statements are sequenced specifically, to ensure that no robot movements propel it into a collision. One of our key strategies when testing new movement codes was to add logic for all of the sensors, even if they were not strictly needed, to account for all possible scenarios, and to minimise the eventuality of incorrect movements being called. For example, we initially assumed that only checking the front left sensor would suffice to ensure that there were no walls in the front of the robot, but we found that this conditional statement conflicted with another scenario, in which the robot is angled leftwards towards a wall. 

Due to limitations in the underlying software used, we were unable to use while-loops in our algorithms. Using static variables in the main.c program, we checked if the most recent movement code is the same as the previous one, and tracked how many times this movement code has been executed consecutively. If the movement code counter exceeds 5, a new function is called, which nudges the robot upwards, which hopefully moves it to a new position from which it can execute a different movement code, and resume its navigation. This code is outlined below:

Main Function:

    Set previous movement value to 0
    Set move counter to 0
    
    If Movement function value is equal to previous movement value:
      Increment move counter by 1
    
    If move counter is greater than 5
      Call the nudge function
    
    Else: 
      Set move counter to 0
      Set previous movement value to Movement function value

Nudge Function:


    Set robot direction to up
    
    If robot currentSpeed is greater than 4:
      Decrement currentSpeed by 1

The Movement function uses many conditional statements that check sensor inputs to ascertain the correct direction for movement. It also uses a boolean variable to act as a break statement, to ensure that only one movement action is activated per cycle. These statements all follow approximately the same pattern:

Movement Function Snippet :

    If flag, and both front sensors and left sensor are greater than 0, and right sensor equals 0:
      Set robot direction to right
      Set flag to false
      Return 4
      
    Else if flag, and both front sensors and right sensor greater than 0, and left sensor equals 0:
      Set robot direction to left
      Set flag to false
      Return 5

FEATURES AND PROPERTIES

The robot features algorithms for breaking infinite repeating loops, which are especially prevalent on start-up, when the robot may be positioned such that none of its sensors detect any walls, and it would begin to spin. We developed an algorithm that tracks if the most recent movement function call is the same as the one preceding it, and interrupts these repeating movements to move the robot away from the position it was in. This algorithm has also been implemented in a manner which does not interfere with regular functioning, despite the fact that it is common for movement function calls to repeat. 

We needed to create virtual sensors which would accurately move alongside, and retain their orientation and length accordingly. We tested a sample algorithm for x and y coordinates, and collaboratively found how it works, and adapted it for use in sideways facing sensors. The algorithm first uses a rounded coordinate of the robot’s centre to use as a reference, and then adds an offset by multiplying the robot’s width by a trigonometric function of the robot’s angle. This ensures the coordinate is placed exactly on the same part of the robot regardless of its angle. The algorithm then adds a value relating to the length of the sensor, also using a trigonometric function to ensure the orientation of the sensor remains consistent relative to the robot’s angle. 

HARDWARE DESIGN

The robot achieved its final state with incremental improvements in ideas and features. This stage-wise improvement was documented in detail on CMap Tools, a concept-mapping software that helped us to develop and implement our ideas from scratch.

If a physical model of the robot were to be built, the components that would be used include:

-	Light Sensor : VT90N1 Photoresistor,  a Photoconductive Cell in ceramic device. It has a wide dynamic range with low noise and distortion. It is responsive to both very low and very high light levels. This is particularly helpful to our model, since we require it to sense the proximity of walls effectively, without crashing into them.
Mini Photocell - SEN-09088, VT90N1. - Excelitas Tech - LDR, 200K OHM, 80mW

-	Microcontroller : Arduino Uno R3 
Arduino Uno Rev3 — Arduino Official Store

-	Servo motor : SF-ROB-09065 
Servo - Generic (Sub-Micro Size) (SparkFun ROB-09065) | Little Bird

-	Breadboard : Solderless Breadboard [ZY-60] 
Solderless Breadboard - 300 Tie Points (ZY-60) Australia

-	Resistors : 1k Ohm MCF 0.25W https://au.element14.com/multicomp/mcf-0-25w-1k/resistor-carbon-film-1k-0-25w-5/dp/9339051


FUTURE SCOPE

For effective sensing and to expand the sensor range HCSRO4 Ultrasonic Sensor can be used instead of light sensors. An alternative method to traverse the maze would be to mount a HCSRO4 Ultrasonic sensor on a ServoMotor placed facing front of the robot body and to change Servo angle and see if the distance to a particular direction is greater than a certain threshold value identified as the colliding distance and move in that direction. 

BIBLOGRAPHY

Turner, Grant, "Simplification of Robotics Through Autonomous Navigation" (2021). Mahurin Honors College Capstone Experience/Thesis Projects. Paper 915.
https://digitalcommons.wku.edu/stu_hon_theses/915

DETAILED MOVEMENT FUNCTION PSEUDOCODE

    Start infinite loop
    Flag = True

    If current speed < 3
      Speed up

    Else if front is clear and wall on right
      Flag = False

    Else if flag is True and front blocked and wall on left
      Turn left
      Flag = False

    Else if flag is True and front clear and wall on right
      Turn right
      Flag = False

    Else if flag is True and front clear and walls are clear
      Turn right
      Flag = False

    Else if flag is True and front blocked and angled right
      Turn left
      Flag = False

    Else if flag is True and front blocked and wall on right
      Turn left
      Flag = False

    Else if flag is True and front blocked and wall on left
      Turn right
      Flag = False

    Else if flag is True and front blocked and walls on both sides
      Speed down
      Flag = False

    Else if flag is True and angled left and walls on right
      Flag = False

    Else if flag is True and angled left and walls on right
      Turn left
      Flag = False

    Else if flag is True and wall on front and angled front
      Turn right
      Flag = False

