#include "vex.h"

using namespace vex;

void run_auto_60(){
    //do red square first
    red_square();
//---------------------------------------------------
    //next do the tower
    task::sleep(100);
    //turn right toward tower
    Drivetrain.setTurnVelocity(20, pct);
    Drivetrain.turnToHeading(-87, rotationUnits::deg,true);
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro3=%f", TurnGyroSmart.rotation());
    task::sleep(100);

    //turn on intake
    task::sleep(200);
    Intake.setVelocity(80, pct);
    Intake.spin(directionType::fwd);

    //move forward at half power
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.driveFor( 750, mm ,true);
    task::sleep(100);

    //
    Intake.stop();

    //
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.driveFor( -150, mm );

    //
    arm_level=3;
    task::sleep(1500);

    //put into first tower
    Intake.setVelocity(100, pct);
    Intake.spin(directionType::rev);
    task::sleep(1000);
    Intake.stop();

    //
    arm_level=0;
    task::sleep(1500);

    //turn right to pick up cube
    Drivetrain.setTurnVelocity(20, pct);
    Drivetrain.turnToHeading(0, rotationUnits::deg,true);
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro3=%f", TurnGyroSmart.rotation());
    task::sleep(100);

    //turn on intake
    Intake.setVelocity(80, pct);
    Intake.spin(directionType::fwd);

    //move forward at half power
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.driveFor( 200, mm ,true);
    task::sleep(300);

    //
    Intake.stop();

    //turn right toward second tower
    Drivetrain.setTurnVelocity(20, pct);
    Drivetrain.turnToHeading(96, rotationUnits::deg,true);

    //
    arm_level=2;
    task::sleep(1500);

    //move forward at half power
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.driveFor( 700, mm ,true);
    task::sleep(100);

    //put into first tower
    Intake.setVelocity(100, pct);
    Intake.spin(directionType::rev);
    task::sleep(1000);
    Intake.stop();


}