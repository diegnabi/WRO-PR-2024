Engineering materials
====

This repository contains engineering materials of a self-driven vehicle model participating in the WRO Future Engineers competition in the 2024 Open Regionals hosted in Puerto Rico.

## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Introduction

Hello, we are part of Puerto Rico's team for the 2024 Open Regionals WRO Future Engineer category. The participants in this team are Diego Alejandro and Victor Gonzalez. Our robot was named Chappie from the movie Chappie.

Our ideas have changed over the last year since we went to Panama in 2023 to compete globally. We have also lost some of our team members to the difficult project. Luckily the team still stays together to keep competing and reaching new heights. 

Here we present our documentation for the upcoming Open Regional which includes every detail from 2024 onward.

* Part Choice

- Chasis

The chassis of Chappie has gone through many different generations. Starting from 2023 when we competed with a Lego Spike we realised if we wanted to be taken seriously we had to completely renovate Chappie. Quickly we turned to using 3D printing since we could create any part and it could be recreated by anyone with access to a 3D printer. First, we set out to find some type of "case" for our components to mount them more easily to the yet-to-be-designed chassis. 

This proved useful but not time-efficient so when designing the first chassis we thought about putting together a breadboard to connect everything. We made holes in the first chassis which was a big box that at the top hosted the breadboard and the Arduino Mega. This didn't work out since adding the sensors and the wheels it would be too bulky. Then we noticed that the breadboard could be held upside down and saved space. So the "zero gravity base" was created, it was a hole where a breadboard could be placed upside down and hold all of its components in place and the Arduino and battery could be placed at the top. This idea was taken to nationals and proved inefficient since the distance sensors would slip out of their contact and give us wrong codes.

This is where our new design came into play, we kept it simple and used all the space available to accommodate all of the pieces.

- Hardware

Our first idea was to look for more open-source hardware that could yield more precise measurements. We decided on an Arduino Uno since we had the materials to work with it and our coach could teach us. Quickly we realised that an Uno did not have enough computing power so the idea of using the Arduino Mega or Raspberry Pi was asked. Since we had to get a 2024 national contender, we decided to stick with Arduino. The reason was that we already learned how to code in C++, and learning Python would take too long.

The HC-SR04 Ultrasonic sensors (distance sensors) were perfect since they gave precise measurements and had a ton of library support and guides on how to utilize them.

The MPU6050 accelerometer had a built-in gyroscope that we could use to keep the robot straight and turn exactly 90 degrees to the left or right. Again easy to work with for beginners with precise data output.

For our motor driver, we decided to use the L298N for the same reasons, at first we thought it was not necessary, but being able to go backward in tight spots proved to be useful, especially in the national competition.

Our driving motor is a TT DC Gearbox Motor which is very common and can be found anywhere. This also proved good with spending our resources since they were cheap.

The SG90 servo motor is a small and again easy-to-use servo with enough power to turn the wheels quickly and precisely. Again with good support.

We decided to eliminate the breadboard since its only real purpose was holding the distance sensors and gyroscope in place, and connecting everything through the power rails. We could connect everything through solder, which would hold everything together forever and not fall out. The other connection were straight from the Arduino to the corresponding sensor through a male-to-female jumper wire.

We used a switch to indicate whether the robot was going left or right and a push button to initiate the run attempt.


* Robot Base Improvements 

The new base of the robot (Chappie) is a simplified version of our national’s 2024 contender. We re-packaged everything into 2 floors, eliminated unnecessary components, and kept things simple for better performance and reliability. 

Chappie’s driving system’s only change was the axle but its steering system was completely re-designed to account for some major flaws such as being unable to steer away from the wall when it was too close. A TT DC Gearbox Motor powers the back wheels with a gear ratio of 1:48 which has an output shaft on each side. The driving motor will be controlled by the L298N motor driver. A small 9g servo motor has been placed at the front for the Ackerman steering system.

Our light sensor started to have some issues during the long times of the competition, sometimes it went higher than expected and activated the turn function, and other times it would be too low to trigger it at all. For this reason, we have decided to lower the robot as close as possible to the ground without scraping any parts. The sensor is placed in a hole which holds it in place. 

In our previous design, the battery placement was “terrible but needed” as it was a desperate measure to use the new battery. We have placed it at the bottom to lower its center of gravity. The base’s center has been widened to accommodate the size of the battery, also been elongated to fit the light sensor.

Chappie’s second floor consists of the L298N motor driver and Chappie’s brain, the Arduino Mega 2560 by Eleegoo.  The distance (ultrasonic) sensors will be connected looking left and right, glued onto the second floor. The gyroscope will be connected in a fixed position to get the most accurate readings possible. For our convenience, we have placed a buzzer to let us know when the robot is doing certain actions. 


* Problems we encountered with the new design

- Battery placement

The battery size has caused an increase of problems for us, we struggled a lot trying to find the most optimal space for it. Fortunately, through more testing of our design, we were finally able to put it in a spot we believe is the best possible.

We also thought to keep it as it was before on top of the robot, but we did that with our previous model and regretted it hugely since it would unbalance Chappie greatly and make him difficult to carry around. 

Our best option seems to be to increase the width of the first floor between the wheels since the battery is just about the same width. This idea would also prove useful since it gave the front wheels space to turn freely.

- Steering System

The driving motor did not cause many problems but the steering motor did, especially because of our terrible steering system. Before we used to steer Chappie with 2 beams connecting each independent wheel, this would work and prove very efficient for tight turning with a wide amount of space available but whenever we had to turn quickly and away from the walls is where the problem arose. The steering system would hit the wall before it could get away from it, thus costing us many points. As well as having both motors under Chappie would make him very tall and our light sensor would be inconsistent.

Now the motors have been placed inside to reduce Chappie’s height, better handle it in the corners, get better consistent reading from the light sensors, and make it easier to carry around.

The steering system has now been changed to an Ackerman steering system so our wheels can remain in place and steer Chappie in tight places. This is in addition to changing our steering motor to a smaller servo, we found out that we do not need a strong beefy servo to steer Chappie. Now we have chosen the common 9g servo motor that can be commonly found.
