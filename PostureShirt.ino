#include <SimbleeForMobile.h>

const int motorPin = 15;
const int led = 13;

int ledState = LOW;

const int flexpin = 6;
int flexposition;
int angle;
int initialUpperLimit; //Not bended
int initialLowerLimit; //Bended

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(led, ledState);

  SimbleeForMobile.advertisementData = "STEM";
  SimbleeForMobile.deviceName = "Posture Shirt";

  // txPowerLevel can be any multiple of 4 between -20 and +4, inclusive. The
  // default value is +4; at -20 range is only a few feet.

  SimbleeForMobile.txPowerLevel = 4;

  SimbleeForMobile.begin();
  Serial.begin(9600);
  initialUpperLimit = analogRead(flexpin); //initial not bended raw val (0,1023)
  initialLowerLimit = (initialUpperLimit - 110); //when it is bended the raw val will be less than the unbended raw val by 110
}

uint8_t text;
uint8_t backgroundRect;

void ui()
{
  SimbleeForMobile.beginScreen();

  //scale elements to correct screen size
  uint16_t wid = SimbleeForMobile.screenWidth;
  uint16_t hgt = SimbleeForMobile.screenHeight;

  backgroundRect = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth, SimbleeForMobile.screenHeight, GREEN);
  text = SimbleeForMobile.drawText(40, 240, "Good Posture", BLACK, 48);

  SimbleeForMobile.endScreen();
}

unsigned long lastUpdated = 0;
unsigned long updateRate = 500; // half a second



void loop()

{
  uint16_t wid = SimbleeForMobile.screenWidth;
  uint16_t hgt = SimbleeForMobile.screenHeight;

  SimbleeForMobile.process();
  unsigned long loopTime = millis(); //datatype

  flexposition = analogRead(flexpin);
  Serial.println(flexposition);

  angle = map(flexposition, initialUpperLimit, initialLowerLimit, 0, 90);  
  Serial.println("Bend: " + String(angle) + " degrees");


  if (abs(angle) > 20)
  {
    Serial.println("Bad posture");
    digitalWrite(motorPin, HIGH); //Run the motor on if the posture is bad
    digitalWrite(led, HIGH);

    if (SimbleeForMobile.updatable && updateRate < (loopTime - lastUpdated))
    {
      lastUpdated = loopTime;

      SimbleeForMobile.updateColor(backgroundRect, RED);
      SimbleeForMobile.updateText(text, "Bad posture");
    }
  }

  else
  {
    Serial.println("Good Posture");
    digitalWrite(motorPin, LOW);
    digitalWrite(led, LOW);

    if (SimbleeForMobile.updatable && updateRate < (loopTime - lastUpdated))
    {
      lastUpdated = loopTime;

      SimbleeForMobile.updateColor(backgroundRect, GREEN);
      SimbleeForMobile.updateText(text, "Good posture");
    }
  }

  SimbleeForMobile.process();
}
