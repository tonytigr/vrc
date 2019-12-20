using namespace vex;
#include "math.h"
#include <array>
extern brain Brain;

// VEXcode devices
extern motor LFMotor;
extern motor LBMotor;
extern motor RFMotor;
extern motor RBMotor;
extern gyro GyroA;
extern controller Controller1;
#define maxMotorSpeed 	127
#define numberOfMotors 	4

#define	PI	3.14159265358979
#define DEADBAND 20
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

typedef struct
{
	double radians;
	double speed;
} PolarJoystick;
