#include <VarSpeedServo.h>

const int numServos = 3;
VarSpeedServo servos[numServos]; 
int motor;

const int servoPins[numServos] = {3, 5, 6}; 

void setup() {
  Serial.begin(9600);
  for (










