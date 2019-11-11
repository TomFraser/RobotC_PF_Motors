#include "PF_Motors.h"

#define MSS currentMotorSpeeds.t_motorControl_s // Shorthand for internal use
#define MSA currentMotorSpeeds.t_motorControl_a // Shorthand for internal use
#define MIS motorIn.t_motorControl_s // Shorthand for internal use
#define MIA motorIn.t_motorControl_a // Shorthand for internal use

void initPFMotors() {
    MSS.A = 0;
    MSS.B = 0;
    MSS.C = 0;
    MSS.D = 0;

    MIS.A = 0;
    MIS.B = 0;
    MIS.C = 0;
    MIS.D = 0;

    initFlag = 1;
}

int getPFMotorSpeed(int motor) {
    return MSA[motor];
}

task updateMotors() {
    for(int i = 0; i < MAX_MOTORS; i++) {
        // For each motor, update speed if a change is detected
		if(abs(MIA[i] - MSA[i]) > 1) {
			//Different speed, update.
			motor[mArray[i]] = MSA[i];
			MSA[i] = MIA[i];
			} else {
            // Update motor speeds
			if(pulsed[i]) {
                // We are pulsed, go to requested speed
				motor[mArray[i]] = MSA[0];
				} else {
				motor[mArray[i]] = MSA[0] - 1;
			}
            pulsed[i] = !pulsed[i];
		}
    }
}

void startMotorTask() {
    if(initFlag < 1) {
        printf("Hey! Init the motor library! \n");
    } else {
        startTask(updateMotors);
    }
}

void exampleSetSpeedFunction() {
    // Set MotorA speed to 100:
    motorIn.t_motorControl_s.A = 100;   // <--
    // Or                               Both these functions set the same address in memory, they are just different ways of addressing it.
    motorIn.t_motorControl_a[0] = 100;  // <--

    // Set MotorB speed to -50:
    motorIn.t_motorControl_s.B = -50;   // <--
    // Or                               Both these functions set the same address in memory, they are just different ways of addressing it.
    motorIn.t_motorControl_a[1] = -50;  // <--
}