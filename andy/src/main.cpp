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
  task::sleep(500);
  //lift tray and arm to release extension

  //lift tray and arm to release extension
  Arm.setStopping(brake);
   Tray.setVelocity(100, pct);
   Intake.setVelocity(100, pct);
   Intake.spin(reverse);
   Tray.rotateTo(330,degrees, false);
   Arm.setVelocity(100, pct);
   Arm.rotateTo(200,deg,true);
   //put down tray and arm
   Tray.setVelocity(100, pct);
    Arm.rotateTo(0,deg,false);
    wait(0.5, seconds);
   Tray.rotateTo(0,degrees, true);
   Arm.setVelocity(60, pct);
   Intake.stop();
   Arm.rotateTo(12,deg,false);
   Controller1.Screen.print("gyro=11");
   //turn on intake
   task::sleep(200);
   LeftIntake.setVelocity(100, pct);
   RightIntake.setVelocity(100, pct);
   LeftIntake.spin(directionType::fwd);
   RightIntake.spin(directionType::fwd);


   //move forward at half power
   task::sleep(100);
   Drivetrain.setDriveVelocity(40, pct );
   Drivetrain.driveFor( 200, mm ,true);
   Drivetrain.turnToHeading(0, rotationUnits::deg,false);
      Drivetrain.driveFor( 950, mm ,true);
   task::sleep(100);
   //MOVE BACK
   Drivetrain.setDriveVelocity(90, pct );
   Drivetrain.driveFor( -275, mm ,true);
   task::sleep(100);
   //turn left toward blue rectangle
   Drivetrain.turnFor( -111, degrees );
   task::sleep(100);
   //move forward
   Drivetrain.setDriveVelocity(50, pct );
   Drivetrain.driveFor( 700, mm ,true);
   task::sleep(100);
      //stop intake
   LeftIntake.stop();
   RightIntake.stop();
   //turn to rect
   Drivetrain.turnFor( -12, degrees );
   Drivetrain.driveFor( 100, mm ,false);




   /*
   //move forward at half power
   Drivetrain.setDriveVelocity(30, pct );
   Drivetrain.turnToHeading(0, rotationUnits::deg,true);
   task::sleep(100);
   Drivetrain.driveFor( 1200, mm ,true);
   task::sleep(100);

   //stop intake
   LeftIntake.stop();
   RightIntake.stop();
  //move back
   Drivetrain.setDriveVelocity(90, pct );
   Drivetrain.driveFor( -590, mm ,true);
   
   task::sleep(100);
   //turn left toward blue square
   Drivetrain.setDriveVelocity(0, pct);
   Drivetrain.setTurnVelocity(15, pct);
   Drivetrain.turnFor( 132, degrees );
   Drivetrain.setDriveVelocity(90, pct);
   Drivetrain.setTurnVelocity(90, pct);
   task::sleep(100);
   //move forward
    Arm.rotateTo(0,deg,false);
  Intake.setVelocity(10, pct);
  Intake.spin(reverse);
   Drivetrain.setDriveVelocity(50, pct );
   Drivetrain.driveFor( 370, mm ,false);
*/




   //push tray
   Tray.setVelocity(45, pct);
   Intake.setVelocity(27, pct);
   Intake.spin(reverse);
   Tray.rotateTo(850,degrees, true);
   //move forward
   Drivetrain.setDriveVelocity(15, pct );
   Drivetrain.driveFor( 20, mm ,true);
   task::sleep(100);
   //put tray
   Tray.setVelocity(80, pct);
   Tray.rotateTo(0,degrees, false);
   //move back
   Drivetrain.setDriveVelocity(80, pct );
   Drivetrain.driveFor( -300, mm );
   Intake.stop();
   Intake.setVelocity(100, pct);
  /*Arm.setStopping(brake);
   Tray.setVelocity(100, pct);
   Intake.setVelocity(100, pct);
   Intake.spin(reverse);
   Tray.rotateTo(350,degrees, false);
   Arm.setVelocity(100, pct);
   Arm.rotateTo(250,deg,true);
   //put down tray and arm
   Tray.setVelocity(100, pct);
   Tray.rotateTo(0,degrees, false);
   Arm.setVelocity(60, pct);
   Intake.stop();
   Arm.rotateTo(20,deg,true);
   Controller1.Screen.print("gyro=11");
   //turn on intake
   task::sleep(200);
   LeftIntake.setVelocity(100, pct);
   RightIntake.setVelocity(100, pct);
   LeftIntake.spin(directionType::fwd);
   RightIntake.spin(directionType::fwd);
   //move forward at half power
   Drivetrain.turnToHeading(0, rotationUnits::deg,true);
   Drivetrain.setDriveVelocity(30, pct );
   task::sleep(100);
   Drivetrain.driveFor( 1200, mm ,true);
   task::sleep(100);

   //stop intake
   LeftIntake.stop();
   RightIntake.stop();
  //move back
   Drivetrain.setDriveVelocity(90, pct );
   Drivetrain.driveFor( -590, mm ,true);
   
   task::sleep(100);
   //turn left toward blue square
   Drivetrain.setDriveVelocity(0, pct);
   Drivetrain.setTurnVelocity(20, pct);
   Drivetrain.turnFor( 130, degrees );
   Drivetrain.setDriveVelocity(90, pct);
   Drivetrain.setTurnVelocity(90, pct);
   task::sleep(100);
   //move forward
    Arm.rotateTo(0,deg,false);
  
   Drivetrain.setDriveVelocity(50, pct );
   Drivetrain.driveFor( 370, mm ,false);
   //push tray
   Tray.setVelocity(45, pct);
   Intake.setVelocity(27, pct);
   Intake.spin(reverse);
   Tray.rotateTo(850,degrees, true);
   //move forward
   Drivetrain.setDriveVelocity(40, pct );
   Drivetrain.driveFor( 20, mm ,true);
   task::sleep(100);
   //put tray
   Tray.setVelocity(80, pct);
   Tray.rotateTo(0,degrees, false);
   //move back
   Drivetrain.setDriveVelocity(80, pct );
   Drivetrain.driveFor( -300, mm );
   Intake.stop();
   Intake.setVelocity(100, pct);
   */
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

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
