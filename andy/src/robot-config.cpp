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

// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool Contoller1RightShouldControlMotorsStopped = true;
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1UpDownButtonsControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
int access = 0;


// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) { 
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3 + Axis1
    // right = Axis3 - Axis1
    int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
    int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
    // check if the value is inside of the deadband range
    if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
      // check if the left motor has already been stopped
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        // stop the left drive motor
        LeftDriveSmart.stop();
        // tell the code that the left motor has been stopped
        DrivetrainLNeedsToBeStopped_Controller1 = false;
      }
    } else {  
      // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
      DrivetrainLNeedsToBeStopped_Controller1 = true;
    }
    // check if the value is inside of the deadband range
    if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
      // check if the right motor has already been stopped
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        // stop the right drive motor
        RightDriveSmart.stop();
        // tell the code that the right motor has been stopped
        DrivetrainRNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
      DrivetrainRNeedsToBeStopped_Controller1 = true;
    }
    // only tell the left drive motor to spin if the values are not in the deadband range
    if (DrivetrainLNeedsToBeStopped_Controller1) {
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
    }
    // only tell the right drive motor to spin if the values are not in the deadband range
    if (DrivetrainRNeedsToBeStopped_Controller1) {
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    }
    // check the ButtonL1/ButtonL2 status to control Arm
    if (Controller1.ButtonL1.pressing()) {
      Arm.setStopping(brake);
      Arm.spin(reverse);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonL2.pressing()) {
      Arm.spin(fwd);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (!Controller1LeftShoulderControlMotorsStopped) {
      Arm.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1LeftShoulderControlMotorsStopped = true;
    }
    // check the ButtonR1/ButtonR2 status to control Arm
    if(access==1){
    if (Controller1.ButtonR1.pressing()) {
      Intake.spin(fwd);
      Contoller1RightShouldControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      Intake.spin(reverse);
      Contoller1RightShouldControlMotorsStopped = false;
    } else  {
      Intake.spin(fwd,5,pct);
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Contoller1RightShouldControlMotorsStopped = true;
    }}if(Controller1.ButtonA.pressing()){
      access=1;
    }
    // check the Up/Down Buttons status to control Tray
    if (Controller1.ButtonUp.pressing()) {
      Tray.setVelocity(50, pct);
      Tray.spin(forward);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (Controller1.ButtonDown.pressing()) {
      Tray.spin(reverse);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (!Controller1UpDownButtonsControlMotorsStopped){
      Tray.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1UpDownButtonsControlMotorsStopped = true;
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

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
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}