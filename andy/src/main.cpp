/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    20, 17, 11, 14, A
// Controller1          controller                    
// Arm                  motor         8               
// Tray                 motor         2               
// LeftIntake           motor         6               
// RightIntake          motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

int arm_level=0;
int arm_level_previous = -1;
//arm position 0 - ground 1 - lower tower 2 - middle tower level
int arm_position[3] =  {0, 320, 420};

//int intakeDirection = 0;

int tray_max_degrees = 850 ;
int tray_position[3] =  {0, 200, 220};
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  run_auto_15();
   }

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void armRaise(){
  if(arm_level<2){
    arm_level_previous = arm_level;
		arm_level = arm_level +1;
  }
}
void armDown(){
  if(arm_level>0){
    arm_level_previous = arm_level;
		arm_level = arm_level -1;
  }
}
// void intakeForward(){
//   if(intakeDirection != 1)
// 		intakeDirection = 1;
//   else
//     intakeDirection = 0;
// }
// void intakeBackward(){
//   if(intakeDirection != -1)
// 		intakeDirection = 1;
//   else
//     intakeDirection = 0;
// }
void usercontrol(void) {
  // User control code here, inside the loop
  // define a task that will handle monitoring inputs from Controller1
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  // VEXcode generated functions
  // define variables used for controlling motors based on controller inputs
  bool Contoller1RightShouldControlMotorsStopped = true;
  //bool Controller1LeftShoulderControlMotorsStopped = true;
  bool Controller1UpDownButtonsControlMotorsStopped = true;
  //bool DrivetrainLNeedsToBeStopped_Controller1 = true;
  //bool DrivetrainRNeedsToBeStopped_Controller1 = true;
  int access = 0;
  //raise arm 0->1 1->2
  Controller1.ButtonL1.pressed(armRaise);//every time Button L1 is pressed function() is run
  //put down arm 2->1 1->0
  Controller1.ButtonL2.pressed(armDown);//every time Button L1 is pressed function() is run
  //intake forward
  //Controller1.ButtonL1.pressed(intakeForward);//every time Button L1 is pressed function() is run
  //intake backward
  //Controller1.ButtonL2.pressed(intakeBackward);//every time Button L1 is pressed function() is run
  while(true) { 
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3 + Axis1
    // right = Axis3 - Axis1
    int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
    int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
    /* // check if the value is inside of the deadband range
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
    if (DrivetrainLNeedsToBeStopped_Controller1) { */
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
    // }
    // // only tell the right drive motor to spin if the values are not in the deadband range
    // if (DrivetrainRNeedsToBeStopped_Controller1) {
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    // }
    // check the ButtonL1/ButtonL2 status to control Arm
/*     if (Controller1.ButtonL1.pressing()) {
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
 */    // check the ButtonR1/ButtonR2 status to control Intake
    if (Controller1.ButtonR1.pressing()) {
      Intake.spin(fwd);
      Contoller1RightShouldControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      Intake.spin(reverse);
      Contoller1RightShouldControlMotorsStopped = false;
    } else  {
      if(access==1){
        Intake.spin(fwd,5,pct);
      }else{
        Intake.stop();
      }
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Contoller1RightShouldControlMotorsStopped = true;
    }
    //Button A toggle access
    if(Controller1.ButtonA.pressing()){
      access = access==1?0:1;
    }
  
    //
    if(arm_level != arm_level_previous){
      Tray.rotateTo(tray_position[arm_level], rotationUnits::deg,false);
      Arm.rotateTo(arm_position[arm_level], rotationUnits::deg);
      arm_level_previous = arm_level ;
    }   
    // check the Up/Down Buttons status to control Tray
    if (Controller1.ButtonUp.pressing() && Tray.position(rotationUnits::deg)<tray_max_degrees) {
      double speed = (1000 - Tray.position(rotationUnits::deg))/ 13 ;
      Tray.setVelocity(speed, pct);
      Tray.spin(forward);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (Controller1.ButtonDown.pressing() && Tray.position(rotationUnits::deg)>0) {
      Tray.setVelocity(100, pct);
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
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Tray.setBrake(brake);
   Intake.setVelocity(100, pct);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
