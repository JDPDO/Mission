#include<Servo.h>

typedef struct Vector {
  
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
  VECTOR forceDirection; // direction of force relative to plane
} SERVO;

const CONTROLLER CONTROLLERS[] = {
  {{ 7, 6, 13}},
};

const SERVO SERVOS[] = {
  {{10}, {0, 20}, true, }, // Propeller
  {{11}, {0, 20}, true}, // Rotor left
  {{12}, {0, 20}, true}, // Rotor right
  {{8}, {-1, -1}, false},
  {{9}, {-1, -1}, false},
};

Servo servos[3];

void setup() {
  Serial.begin(9600);
  
  // Setup rotors
  SERVO ro;  
  for(int i = 0; i < sizeof(servos); i++) {
    ro = SERVOS[i];
    pinMode(ro.PIN.pulse, INPUT);
    servos[i].attach(ro.PIN.pulse, ro.PULSE.min, ro.PULSE.max);
  }

  // Setup controllers
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
