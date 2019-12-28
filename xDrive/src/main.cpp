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
  vexcodeInit();
  Controller1.Screen.setCursor( 1, 1 );
  Controller1.Screen.print("autonomous running...");
  //turn  degrees clockwise
  //TurnWithGyro( -90, 20, 2 ,0.4);
  //move to x,y cm top right at speed percent
  //moveCordinate(0,  30, 35);
  //moveCordinate(0,  -30, 35);
 // moveCordinate(-10, 10, 50 );
  //moveCordinateWithPIDandGyro(-30, 0, 50, 2, 0.2 );
  TurnWithGyro( -360, 40, 2 ,0.4);
  //moveCordinateWithPIDandGyro(-30, 0, 50, 2, 0.2 );
 // TurnWithGyro( 360, 40, 2 ,0.4);
  //moveCordinateWithPIDandGyro(-30, 0, 50, 2, 0.2 );
  //TurnWithGyro( -90, 40, 2 ,0.4);
  //moveCordinateWithPIDandGyro(-30, 0, 50, 2, 0.2 );
  //TurnWithGyro( -90, 40, 2 ,0.4);
  //turn  degrees clockwise
  //TurnWithGyro( 90, 20, 2 ,0.4);
  //move to x,y cm top right at speed percent
  //moveCordinate(20,  -10, 20);
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    double speed;
    double radians;
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

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
