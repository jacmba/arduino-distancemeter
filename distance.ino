/**
 * Distance meter with light and sound warning
 * @author Jacinto Mba <jacmba@gmail.com>
 */

#include <Ultrasonic.h>

const int R = 10; // Red light pin
const int G = 9; // Green light pin
const int BEEP = 8; // Sound beeper pin

Ultrasonic us(12,11); // Initialize ultrasonic module lib
int cont = 0; // Beep frequency counter

void setup () {
  Serial.begin(9600);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(BEEP, OUTPUT);
}

void loop () {
  // Get distance in centimeters
  long dist = us.distanceRead(CM);
  Serial.println(dist);

  // Calculate green light intensity
  int green = (int)((float)dist / 200. * 255.);
  analogWrite(G, green);

  // Calculate red light intensity
  int red = (int)(200. / dist * 255.);
  analogWrite(R, red);

  // Trigger sound based on distance
  if(dist < 200 && dist > 5) { // Beep tones below 2 meters
    cont += (int)(200. / (float)dist);
    if(cont > 20) {
      digitalWrite(BEEP, HIGH);
      cont = 0;
    } else {
      digitalWrite(BEEP, LOW);
    }
  } else if(dist <= 5) { // Continuous tone below 5 centimeters
    digitalWrite(BEEP, HIGH);
  } else {
    digitalWrite(BEEP, LOW);
  }
  
  delay(100);
}