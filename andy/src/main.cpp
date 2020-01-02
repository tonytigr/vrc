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
  run_auto_60();
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
  arm_level_previous = arm_level;
  if(arm_level == 3){
		arm_level = 0;
  }else{
		arm_level = arm_level + 1;
  }
}
void armDown(){
  arm_level_previous = arm_level;
  if(arm_level == 0){
		arm_level = 3;
  }else{
		arm_level = arm_level - 1;
  }
}
void idleToggle(){
    idle_flag = idle_flag==1? 0:1;
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
  bool Contoller1RightShouldControlMotorsStopped = true;
  bool Controller1UpDownButtonsControlMotorsStopped = true;
  //raise arm 0->1 1->2 2->3 3->1
  Controller1.ButtonL1.pressed(armDown);//every time Button L1 is pressed function() is run
  //put down arm 3->2 2->1 1->0 0->3
  Controller1.ButtonL2.pressed(armRaise);//every time Button L1 is pressed function() is run
  //Button A toggle access
  Controller1.ButtonA.pressed(idleToggle);//every time Button L1 is pressed function() is run
  while(true) { 
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3 + Axis1
    // right = Axis3 - Axis1
    LeftDriveSmart.setVelocity(Controller1.Axis3.position() + Controller1.Axis1.position(), percent);
    LeftDriveSmart.spin(forward);
    RightDriveSmart.setVelocity(Controller1.Axis3.position() - Controller1.Axis1.position(), percent);
    RightDriveSmart.spin(forward);
    // check the ButtonR1/ButtonR2 status to control Intake
    if (Controller1.ButtonR1.pressing()) {
      Intake.spin(fwd);
      Contoller1RightShouldControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      Intake.spin(reverse);
      Contoller1RightShouldControlMotorsStopped = false;
    } else  {
      if(idle_flag==1){
        Intake.spin(fwd,5,pct);
      }else{
        Intake.stop();
      }
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Contoller1RightShouldControlMotorsStopped = true;
    }
    // check the Up/Down Buttons status to control Tray
    if (Controller1.ButtonUp.pressing() && Tray.position(rotationUnits::deg) < tray_max_degrees) {
      //double speed = (1000 - Tray.position(rotationUnits::deg))/ 13 ;
      Tray.setVelocity(Tray_Velocity, pct);
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
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
