#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
motor LFMotor = motor(PORT15, ratio18_1, false);
motor LBMotor = motor(PORT17, ratio18_1, false);
motor RFMotor = motor(PORT4, ratio18_1, false);
motor RBMotor = motor(PORT9, ratio18_1, false);

motor LeftIntake = motor(PORT6, ratio36_1, false);
motor RightIntake = motor(PORT10, ratio36_1, true);
motor_group Intake = motor_group(LeftIntake, RightIntake);

controller Controller1 = controller(primary);
motor Arm = motor(PORT8, ratio36_1, false);
motor Tray = motor(PORT2, ratio36_1, false);  

gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.A);

/* // define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  
  double speed;
  double radians;
  while(true) { 
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("Axis1=%d",Controller1.Axis1.value());
    Controller1.Screen.setCursor( 2, 1 );
    Controller1.Screen.print("Axis2=%d",Controller1.Axis2.value());
    // wait before repeating the process
    speed = getJoyPolarSpeed();
    radians = (PI / 2) - getJoyPolarRadians();
    int rotateValue = Controller1.Axis4.value()/2;
    RadianOutput(radians, speed,rotateValue );
    Controller1.Screen.clearScreen();
    
    wait(10, msec);
  }
  return 0;
}
 */
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  Brain.Screen.clearScreen();
}
//**--------------------- SUPPORT FUNCTIONS ----------------------**//
double getJoyPolarRadians() 
{ 
	return atan2((double) Controller1.Axis2.value(), (double) Controller1.Axis1.value());
}
//**--------------------- SUPPORT FUNCTIONS ----------------------**//
double getJoyPolarSpeed()
{
	double tmpSpeed = sqrt((Controller1.Axis1.value() * Controller1.Axis1.value()) + (Controller1.Axis2.value() * Controller1.Axis2.value()));
	tmpSpeed /= maxMotorSpeed;
	tmpSpeed = tmpSpeed > 1 ? 1 : tmpSpeed;
	return tmpSpeed;
}
//**------------------- MAIN FUNCTIONS --------------------------- **//

/*
* Converts radians, speed, and rotation to an x-drive holonomic configuration
* to enable robot to go in any direction at speed
*  
* Requires robot-config.h to be updated (uses FRONT_LEFT_MOTOR, etc. definitions)
*  
* @param radians The heading of motion, where 0 is forward, PI/2 is right (see compass)
* @param speed The speed of motion, from 0 to 1
* @param rotation The speed of rotation of the bot, from -127 to 127
*/
void RadianOutput(double radians, double speed, int rotation)
{
	if (speed > 0)
	{
		double frontLeftOutput	=	 maxMotorSpeed * cos((PI / 4) - radians) ,
		       frontRightOutput =	 -maxMotorSpeed * cos((PI / 4) + radians) ,
		       rearRightOutput	=	 -maxMotorSpeed * cos((PI / 4) - radians) ,
		       rearLeftOutput	=    maxMotorSpeed * cos((PI / 4) + radians);

		frontLeftOutput += rotation;
		frontRightOutput += rotation;
		rearRightOutput += rotation;
		rearLeftOutput += rotation;

		double output[4] = { frontLeftOutput, frontRightOutput, rearLeftOutput, rearRightOutput };
		double maxValue = 0;
    for (int i = 0; i < 4; i++)
    {
      if (output[i] > maxValue) maxValue = output[i];
    }
		speed *= maxMotorSpeed / maxValue;

		frontLeftOutput *= speed;
		frontRightOutput *= speed;
		rearLeftOutput *= speed;
		rearRightOutput *= speed;
		LFMotor.spin(directionType::fwd, frontLeftOutput , percentUnits::pct);
		RFMotor.spin(directionType::fwd, frontRightOutput , percentUnits::pct);
		LBMotor.spin(directionType::fwd, rearLeftOutput , percentUnits::pct);
		RBMotor.spin(directionType::fwd, rearRightOutput , percentUnits::pct);
	}
	else if (rotation > DEADBAND || rotation < -DEADBAND)
	{
		LFMotor.spin(directionType::fwd, rotation , percentUnits::pct);
		RFMotor.spin(directionType::fwd, rotation , percentUnits::pct);
		LBMotor.spin(directionType::fwd, rotation , percentUnits::pct);
		RBMotor.spin(directionType::fwd, rotation , percentUnits::pct);
	}
	else
	{
		LFMotor.stop(brakeType::brake);
		RFMotor.stop(brakeType::brake);
		LBMotor.stop(brakeType::brake);
		RBMotor.stop(brakeType::brake);
	}
}
//**------------------- convert travel distance to rotation degrees --------------------------- **//
double getDegrees(double centimeters){
    float degreePerCM = 360 / WHEEL_CIRCUMFERENCE ;
    return centimeters*degreePerCM;

}
//**------------------- robot moves to (x1, y1) at the speed percentage--------------------------- **//
void moveCordinate(double x1, double y1, double speedPercent){
    Controller1.Screen.setCursor( 2, 1 );
    Controller1.Screen.print("to x1= %.1f y1= %.1f",x1,y1);
    double radians = PI/2-atan2(y1, x1);
		LFMotor.resetPosition();
		RFMotor.resetPosition();
		LBMotor.resetPosition();
		RBMotor.resetPosition();
		LFMotor.rotateTo( getDegrees( sqrt(2)*(  x1+y1))/2, rotationUnits::deg , speedPercent*cos((PI / 4) - radians), velocityUnits::pct, false);
		RFMotor.rotateTo( getDegrees( sqrt(2)*(  x1-y1))/2, rotationUnits::deg , speedPercent*cos((PI / 4) + radians), velocityUnits::pct, false);
		LBMotor.rotateTo( getDegrees( sqrt(2)*( -x1+y1))/2, rotationUnits::deg , speedPercent*cos((PI / 4) + radians), velocityUnits::pct, false);
		RBMotor.rotateTo( getDegrees( sqrt(2)*( -x1-y1))/2, rotationUnits::deg , speedPercent*cos((PI / 4) - radians), velocityUnits::pct, true);
}
//**------------------- robot moves to (x1, y1) at maxTurnPower and stops use PID --------------------------- **//
void moveCordinateWithPIDandGyro(double x1, double y1, int maxTurnPower, int minTurnPower, float kp){
    TurnGyroSmart.resetRotation();
    double targetDegreesLF = getDegrees( sqrt(2)*(  x1+y1))/2;
    double targetDegreesRF = getDegrees( sqrt(2)*(  x1-y1))/2;
    double targetDegrees = (targetDegreesLF<0?-targetDegreesLF:targetDegreesLF)>(targetDegreesRF<0?-targetDegreesRF:targetDegreesRF)?targetDegreesLF:targetDegreesRF ;
    motor targetMotor = (targetDegreesLF<0?-targetDegreesLF:targetDegreesLF)>(targetDegreesRF<0?-targetDegreesRF:targetDegreesRF)?LFMotor:RFMotor ;
    double error = targetDegrees ;
    double dirError = 0 ;
    double speedPercent;
    double rotatedDegrees;
    double radians = PI/2-atan2(y1, x1);
    double heading = radians * 180/PI;
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("h,t %.1f %.1f",heading,targetDegrees);
		LFMotor.resetPosition();
		RFMotor.resetPosition();
		LBMotor.resetPosition();
		RBMotor.resetPosition();
    while ((error<0?-error:error)>2){
      if((error<0?-error:error) >= 120)
          speedPercent = maxTurnPower ;
      else{
          speedPercent = (error<0?-1:1) * error * kp +  minTurnPower;
      }
      dirError = TurnGyroSmart.rotation()*PI/180;
      LFMotor.spin(directionType::fwd, speedPercent*cos((PI / 4) - radians - dirError), velocityUnits::pct);
      RFMotor.spin(directionType::rev, speedPercent*cos((PI / 4) + radians - dirError), velocityUnits::pct);
      LBMotor.spin(directionType::fwd, speedPercent*cos((PI / 4) + radians - dirError), velocityUnits::pct);
      RBMotor.spin(directionType::rev, speedPercent*cos((PI / 4) - radians - dirError), velocityUnits::pct);
      //wait(20, msec); // Sleep the task for a short amount of time to
      rotatedDegrees=targetMotor.position(rotationUnits::deg);
		  error = targetDegrees - rotatedDegrees;
      Controller1.Screen.setCursor( 2, 1 );
      Controller1.Screen.print(rotatedDegrees);
    }
    LFMotor.stop();
    RFMotor.stop();
    LBMotor.stop();
    RBMotor.stop();
}
//**------------------- turn to target degrees clockwise plus --------------------------- **//
// need initial gyro
// if kp=1,   error 45 degree and minimum power 5 will produce 45*1  + 5 =50   percent 
// if kp=0.5, error 45 degree and minimum power 5 will produce 45*.5 + 5 =27.5 percent 
void TurnWithGyro(int targetDegrees, int maxTurnPower, int minTurnPower, float kp){
  TurnGyroSmart.resetRotation();
  double error = targetDegrees;
  double speedPercent;
  double gyroRotation;
  Controller1.Screen.setCursor( 1, 1 );
  Controller1.Screen.print(targetDegrees);
	while((error<0?-error:error) > 1){
		if((error<0?-error:error) >= 25)
			speedPercent = (error<0?-1:1) * maxTurnPower ;
		else{
        speedPercent = error * kp + (error<0?-1:1) * minTurnPower;
    }
    LFMotor.spin(directionType::fwd, speedPercent, percentUnits::pct);
    RFMotor.spin(directionType::fwd, speedPercent, percentUnits::pct);
    LBMotor.spin(directionType::fwd, speedPercent, percentUnits::pct);
    RBMotor.spin(directionType::fwd, speedPercent, percentUnits::pct);
    wait(20, msec); // Sleep the task for a short amount of time to
    gyroRotation=TurnGyroSmart.rotation();
		error = targetDegrees - gyroRotation;
    Controller1.Screen.setCursor( 2, 1 );
    Controller1.Screen.print(gyroRotation);
	}
  LFMotor.stop();
  RFMotor.stop();
  LBMotor.stop();
  RBMotor.stop();
}
//**------------------- turn to target degrees clockwise plus without gyro --------------------------- **//
// void turn( double turnAngle, double speedPercent){
//     Controller1.Screen.setCursor( 2, 1 );
//     Controller1.Screen.print("turning  angle= %d ",turnAngle);
//     double rotateCM = PI * WHEELS_WIDTH * turnAngle /360;
// 		LFMotor.rotateFor(directionType::fwd,  getDegrees( rotateCM), rotationUnits::deg, speedPercent, velocityUnits::pct, false);
// 		RFMotor.rotateFor(directionType::fwd,  getDegrees( rotateCM), rotationUnits::deg, speedPercent, velocityUnits::pct, false);
// 		LBMotor.rotateFor(directionType::fwd,  getDegrees( rotateCM), rotationUnits::deg, speedPercent, velocityUnits::pct, false);
// 		RBMotor.rotateFor(directionType::fwd,  getDegrees( rotateCM), rotationUnits::deg, speedPercent, velocityUnits::pct, true);
// }
