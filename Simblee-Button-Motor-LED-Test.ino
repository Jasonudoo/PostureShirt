#include <SimbleeForMobile.h>

const int motorPin = 3;


const int led = 13; // The Simblee BOB (WRL-13632) has an LED on pin 2.
int ledState = LOW;

const int flexpin = 0; 
int angle; 


uint8_t btnID;
uint8_t switchID;

void setup() 
{
  pinMode(led, OUTPUT);
  pinMode(3, OUTPUT); 
  digitalWrite(led, ledState);

  SimbleeForMobile.advertisementData = "Blink";
  SimbleeForMobile.deviceName = "WRL-13632";

  // txPowerLevel can be any multiple of 4 between -20 and +4, inclusive. The
  // default value is +4; at -20 range is only a few feet.
  
  SimbleeForMobile.txPowerLevel = -4;

  SimbleeForMobile.begin();
}

void loop() 
{

  SimbleeForMobile.process();
}

void ui()
{

  color_t darkgray = rgb(85,85,85);

  //scale elements to correct screen size
  uint16_t wid = SimbleeForMobile.screenWidth;
  uint16_t hgt = SimbleeForMobile.screenHeight;

  SimbleeForMobile.beginScreen(darkgray);
  //SimbleeForMobile.drawText("HELLO");

  //Create button
  btnID = SimbleeForMobile.drawButton(
                              (wid/2) - 75,          // x location
                              (hgt/2) - 22,          // y location
                              150,                   // width of button
                              "TURN LED ON",         // text shown on button
                              WHITE,                 // color of button
                              BOX_TYPE);             // type of button
  
  SimbleeForMobile.setEvents(btnID, EVENT_PRESS | EVENT_RELEASE);

  
  /*switchID = SimbleeForMobile.drawSwitch(
                              (wid/2) - 25,          // x location
                              (hgt/2)+22,            // y location
                              BLUE);                 // color (optional)
  */
  
  SimbleeForMobile.endScreen();
  
}


void ui_event(event_t &event)

{
  if (event.id == btnID)
  {
    if (event.type == EVENT_PRESS)
    {
      digitalWrite(3, HIGH); //Turn the motor on
      if (ledState == HIGH) digitalWrite(led, LOW);
      else digitalWrite(led, HIGH);
    }    
    if (event.type == EVENT_RELEASE)
    {
      digitalWrite(3, LOW); 
      if (ledState == HIGH) digitalWrite(led, HIGH);
      else digitalWrite(led, LOW);
    }
  }

/*
  if (event.id == switchID)
  {
    if (ledState == HIGH) ledState = LOW; //toggle LED state variable
    else ledState = HIGH;
    digitalWrite(led, ledState);
  }
  */

}
