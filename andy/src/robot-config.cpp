#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT17, ratio18_1, false);
motor leftMotorB = motor(PORT20, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

motor rightMotorA = motor(PORT11, ratio18_1, true); 
motor rightMotorB = motor(PORT14, ratio18_1, true); 
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);

motor LeftIntake = motor(PORT6, ratio36_1, false);
motor RightIntake = motor(PORT10, ratio36_1, true);
motor_group Intake = motor_group(LeftIntake, RightIntake);

gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.A);
smartdrive Drivetrain= smartdrive(LeftDriveSmart, RightDriveSmart, TurnGyroSmart, 319.19, 320, 165, mm, 1);
controller Controller1 = controller(primary);
motor Arm = motor(PORT8, ratio36_1, false);
motor Tray = motor(PORT2, ratio36_1, false);  

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
Arm.setStopping(hold);

  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}
