using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LFMotor;
extern motor LBMotor;
extern motor RFMotor;
extern motor RBMotor;
extern controller Controller1;
extern gyro TurnGyroSmart;

#define MAX_MOTOR_SPEED 	50

#define	WHEEL_CIRCUMFERENCE	31.919

#define	PI	3.14159265358979
//Range joystick not responds
#define DEADBAND 20

//accepted distance error in degree
#define ACCEPTED_DISTANCE_ERROR 5
//slow down distance in degree
#define SLOW_DOWN_DISTANCE 120

//accepted rotation error in degree
#define ACCEPTED_ROTATION_ERROR 1
//slow down rotation in degree
#define SLOW_DOWN_ROTATION_DEGREE 25

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

double getJoyPolarRadians() ;
double getJoyPolarSpeed();
void RadianOutput(double radians, double speed, int rotation);
void moveCordinate(double x1, double y1, double speedPercent);
void moveCordinateGyro(double x1, double y1, int maxTurnPower, int minTurnPower, float kp);

void TurnWithGyro(int targetDegrees, int maxTurnPower, int minTurnPower, float kp); 