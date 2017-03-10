const int flexpin = 0; 
int angle; 

void setup() 
{ 
  // Use the serial monitor window to help debug our sketch:

  Serial.begin(9600);
} 


void loop() 
{ 
  int flexposition;    // Input value from the analog pin.


  flexposition = analogRead(flexpin);

  angle = map(flexposition, 480, 320, 0, 90);

  
  Serial.println("Bend: " + String(angle) + " degrees");

  if (abs(angle) > 30) 
  {
    Serial.println("Bad posture");
  }

  else 
  {
    Serial.println("Good Posture");
  }
  Serial.println();

  delay(500);

} 


