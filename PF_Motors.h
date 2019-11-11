#ifndef PF_Motors_h_
#define PF_Motors_h_

#define MAX_MOTORS 4

typedef union motorControl_u {
    typedef struct motorControl_s {
        int A, B, C, D;
    } t_motorControl_s;
    int t_motorControl_a[3];
} t_motorControl;

t_motorControl motorIn; // Set motor speeds for all motors
t_motorControl currentMotorSpeeds; // Holds the current motor speeds

bool pulsed[4] = {false};

bool initFlag = false;

t_motor mArray[4] = {motorA, motorB, motorC, motorD};

void initPFMotors(); // Init PF motors

int getPFMotorSpeed(int motor); // Get speed of each motor

void updateMotors(); // Pulse speeds

void startMotorsTask();

#endif