using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LFMotor;
extern motor LBMotor;
extern motor RFMotor;
extern motor RBMotor;
extern controller Controller1;
extern gyro TurnGyroSmart;

#define maxMotorSpeed 	50
#define numberOfMotors 	4

#define	WHEELS_WIDTH	46
#define	WHEEL_CIRCUMFERENCE	31.919

#define	PI	3.14159265358979
#define DEADBAND 20
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
void moveCordinateWithPIDandGyro(double x1, double y1, int maxTurnPower, int minTurnPower, float kp);

void TurnWithGyro(int targetDegrees, int maxTurnPower, int minTurnPower, float kp); 