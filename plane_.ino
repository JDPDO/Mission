#include<limits.h>
#include<Servo.h>
#include <stdio.h>

// ### Basic Structures ###

typedef struct Vector {
  float x, y, z;
} VECTOR;

typedef struct Controller {
  struct pin {
    int x, y, sw;
  } PIN;
} CONTROLLER;

typedef struct {
  struct pin {
    int pulse; // pulse pin
  } PIN;
  struct pulse {
    int min, max; // for 0 to 180 deg; -1 for
  } PULSE;
  bool isRotor; // rotating servo
  // Direction of force relative to plane.
  // For non rotating servos direction is middle position  
  VECTOR forceDirection;
  // Position of force to custom zero point
  VECTOR forcePosition;
} SERVO;


// ### Plane attributes ###

// Local controllers
const CONTROLLER CONTROLLERS[] = {
  {{7, 6, 13}},
};

// Available servos
const SERVO SERVOS[] = {
  // {{pin}, {min, max}, isRotor, {forceDirection}, {forcePosition}
  {{10}, {0, 20}, true, {0, 1, 0}, {0, 0, 0}}, // Propeller
  {{11}, {0, 20}, true, {0, 0, 1}, {7, -8, 0}}, // Rotor left
  {{12}, {0, 20}, true, {0, 0, 1}, {-7, -8, 0}}, // Rotor right
  {{8}, {-1, -1}, false, {INT_MIN, 1, 0}, {0, -20, 2}}, // Elevator
  {{9}, {-1, -1}, false, {0, 1, INT_MIN}, {0, -20, 3}}, // Rudder
};

VECTOR barycenter = {0, -10, 1}; // Position of center of mass.

Servo servos[5]; // With all servos of plane!


// ### Init and Setup plane ###

VECTOR destination; // Calculated destination vector 

void setup() {
  Serial.begin(9600);
  
  // Setup rotors
  SERVO ro;
  // `SERVOS` and `servos` need to have same length.
  for(int i = 0; i < sizeof(servos); i++) {
    ro = SERVOS[i];
    pinMode(ro.PIN.pulse, INPUT);
    servos[i].attach(
      ro.PIN.pulse,
      ro.PULSE.min == -1 ? NULL : ro.PULSE.min,
      ro.PULSE.max == -1 ? NULL : ro.PULSE.max
    );
  }

  // Setup local controllers
  int controllers = sizeof(CONTROLLERS);
  switch(controllers) {
    case 0:
      Serial.println("No local controller configured.");
      break;
    default:
      Serial.println(controllers + " local controllers.");
      Serial.println("So many controllers are not supported yet. Only set up two.");
    case 2:
      Serial.println("Using two local controllers.");
      
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
