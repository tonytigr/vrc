#include "vex.h"

using namespace vex;

void run_auto_60(){

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
    Intake.setVelocity(100, pct);
    Intake.spin(directionType::fwd);
   
    //move forward at half power
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.turnToHeading(0, rotationUnits::deg,true);
    task::sleep(100);
    Drivetrain.driveFor( 1200, mm ,true);
    task::sleep(100);

    //stop intake
    Intake.stop();
    //move back
    Drivetrain.setDriveVelocity(90, pct );
    Drivetrain.driveFor( -890, mm ,true);

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
    Drivetrain.driveFor( 350, mm ,false);

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
//---------------------------------------------------
//next do the tower
    task::sleep(100);
    //turn right toward tower
    Drivetrain.setDriveVelocity(0, pct);
    Drivetrain.setTurnVelocity(15, pct);
    Drivetrain.turnFor( 150, degrees );
    Drivetrain.setDriveVelocity(90, pct);
    Drivetrain.setTurnVelocity(90, pct);

    //turn on intake
    task::sleep(200);
    Intake.setVelocity(80, pct);
    Intake.spin(directionType::fwd);

    //move forward at half power
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.driveFor( 700, mm ,true);
    task::sleep(100);

    //
    Intake.stop();

    //
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.driveFor( -80, mm );

    //
    arm_level=3;

    //
    Intake.spin(directionType::fwd);
    task::sleep(600);
    Intake.stop();

}