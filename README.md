# PostureShirt
This repository contains the Arduino programs required to run the Posture Shirt. 

This shirt will detect one's posture and alert a user when they are not sitting straight. 
The code makes use of the SimbleeForMobile API and the iOS Simblee mobile application. 

The flex sensor and a sewn in voltage divider resistor circuit are used to find the angle of the user's spine. If this goes beyond a certain position, a haptic vibration motor sewn into the base of the shirt close to the spine using conductive thread will vibrate to alert the user to correct their posture. The main Simblee board is sewn into the shirt using nonconductive thread. 

![image](https://user-images.githubusercontent.com/12382926/30192928-0047996e-9410-11e7-96a5-52cb58851f48.png)
