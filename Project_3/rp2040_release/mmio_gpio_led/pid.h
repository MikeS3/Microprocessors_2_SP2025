#ifndef PID_H__
#define PID_H__

//PID Adapted from https://github.com/pms67/PID/tree/master

typedef struct {

	/* Controller gains */
	fixedpt Kp;
	fixedpt Ki;
	fixedpt Kd;

	/* Derivative low-pass filter time constant */
	fixedpt tau;

	/* Output limits */
	fixedpt limMin;
	fixedpt limMax;
	
	/* Integrator limits */
	fixedpt limMinInt;
	fixedpt limMaxInt;

	/* Sample time (in seconds) */
	fixedpt T;

	/* Controller "memory" */
	fixedpt integrator;
	fixedpt prevError;			/* Required for integrator */
	fixedpt differentiator;
	fixedpt prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	fixedpt out;

} PIDController;

void  PIDController_Init(PIDController *pid);
fixedpt PIDController_Update(PIDController *pid, fixedpt setpoint, fixedpt measurement);

#endif