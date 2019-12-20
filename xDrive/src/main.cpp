/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\zhangto                                          */
/*    Created:      Thu Dec 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LFMotor              motor         2               
// LBMotor              motor         3               
// RFMotor              motor         5               
// RBMotor              motor         6               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
//**--------------------- SUPPORT FUNCTIONS ----------------------**//
double getJoyPolarRadians() 
{ 
	return atan2((double) Controller1.Axis1.value(), (double) Controller1.Axis1.value());
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
* Requires CortexDefinition.h to be updated (uses FRONT_LEFT_MOTOR, etc. definitions)
*  
* @param radians The heading of motion, where 0 is forward, PI/2 is right (see compass)
* @param speed The speed of motion, from 0 to 1
* @param rotation The speed of rotation of the bot, from -127 to 127
*/
void RadianOutput(double radians, double speed, int rotation)
{
	if (speed > 0)
	{
		double frontLeftOutput	=	-maxMotorSpeed * cos((PI / 4) - radians) ,
		       frontRightOutput =	 maxMotorSpeed * cos((PI / 4) + radians) ,
		       rearRightOutput	=	 maxMotorSpeed * cos((PI / 4) - radians) ,
		       rearLeftOutput	=   -maxMotorSpeed * cos((PI / 4) + radians);

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
		LFMotor.setVelocity( frontLeftOutput , percentUnits::pct);
		RFMotor.setVelocity( frontRightOutput , percentUnits::pct);
		LBMotor.setVelocity( rearLeftOutput , percentUnits::pct);
		RBMotor.setVelocity( rearRightOutput , percentUnits::pct);
	}
	else if (rotation > DEADBAND || rotation < -DEADBAND)
	{
		LFMotor.setVelocity( rotation , percentUnits::pct);
		RFMotor.setVelocity( rotation , percentUnits::pct);
		LBMotor.setVelocity( rotation , percentUnits::pct);
		RBMotor.setVelocity( rotation , percentUnits::pct);
	}
	else
	{
		LFMotor.stop(brakeType::brake);
		RFMotor.stop(brakeType::brake);
		LBMotor.stop(brakeType::brake);
		RBMotor.stop(brakeType::brake);
	}
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

		PolarJoystick joystick;
		while (true)
		{
			joystick.speed = getJoyPolarSpeed();
			joystick.radians = (PI / 2) - getJoyPolarRadians();
      Controller1.Screen.print("speed=%f", joystick.speed);
      Controller1.Screen.print("radians=%f", joystick.radians);
			RadianOutput(joystick.radians, joystick.speed, Controller1.Axis4.value());
			task::sleep(20);
		}
  
}
