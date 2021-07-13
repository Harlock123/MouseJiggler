// Simple Mouse Jiggler

// Modified by Lonnie Watson May 2020
// better address mouse sensativity on MAC (screensavers still acting on single pixel movements)

#include <Mouse.h>
unsigned int LowerCycleTime = 10000; //Minimum Time in milli-seconds between each mouse action  Default: 10000 (10 Seconds), Max 65535ms
unsigned int UpperCycleTime = 20000; //Maximum Time in milli-seconds between each mouse action  Default: 30000 (30 Seconds), Max 65535ms
//Random Function will randomly execute a mouse move between these two values
void setup() {
  
  pinMode(1, OUTPUT);
  Mouse.begin();
 
  
}
void loop() {
//Moves mouse 1 pixel in a direction (up/down/left/right) in a square
  Mouse.move(2,0);
  delay(100);
  Mouse.move(-2,0);
  delay(100);
  Mouse.move(0,2);
  delay(100);
  Mouse.move(0,-2);
  delay(10000);
  

}
