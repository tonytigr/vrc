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
int Tray_Velocity = 60 ;
int tray_max_degrees = 920 ;

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
  // void moveCordinateGyro(double x1, double y1, int maxTurnPower, int minTurnPower, float kp);
  // void TurnWithGyro(int targetDegrees, int maxTurnPower, int minTurnPower, float kp); 
  // ..........................................................................
  //No need in Competition, pre_auton() will be run before autonomous()
  pre_auton();
  run_auto_test();
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
int idle_flag = 0;
void idleToggle(){
    idle_flag = idle_flag==1? 0:1;
}

void usercontrol(void) {
  // User control code here, inside the loop
  bool Contoller1RightShouldControlMotorsStopped = true;
  bool Controller1UpDownButtonsControlMotorsStopped = true;

  //every time Button A is pressed idleToggle() is run
  Controller1.ButtonA.pressed(idleToggle);
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
