#include "vex.h"

using namespace vex;
void red_square(){
    //task::sleep(500);
    //lift tray and arm to release extension

    //lift tray and arm to release extension
    Arm.setStopping(brake);
    Intake.setVelocity(100, pct);
    Intake.spin(reverse);
    //
    // arm_level = 2;
    // task::sleep(2000);

    Arm.setVelocity(60, pct);
    Arm.rotateTo(60,deg,false);
    Tray.setVelocity(50, pct);
    Tray.rotateTo(150,degrees, true);
    wait(0.5, seconds);
    Tray.setVelocity(100, pct);
    Tray.rotateTo(0,degrees, true);
    //arm_level = 1;
    Arm.setVelocity(100, pct);
    Arm.rotateTo(25,deg,true);
    //put down tray and arm
//    Arm.setVelocity(60, pct);
//    Arm.rotateTo(0,deg,false);
    Intake.stop();
//    Arm.rotateTo(12,deg,false).
    //turn on intake
    task::sleep(200);
    Intake.setVelocity(100, pct);
    Intake.spin(directionType::fwd);
    
    //move forward at half power
    Drivetrain.setDriveVelocity(20, pct );
    Drivetrain.turnToHeading(0, rotationUnits::deg,true);
    task::sleep(100);
    Drivetrain.driveFor( 900, mm ,true);
    task::sleep(100);
    
    //stop intake
    Intake.stop();
    
    //move back
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.turnToHeading(0, rotationUnits::deg,true);
    task::sleep(100);
    Drivetrain.setDriveVelocity(90, pct );
    Drivetrain.driveFor( -500, mm ,true);
    task::sleep(100);

    

    //turn left toward blue square
    Drivetrain.setDriveVelocity(30, pct );
    Drivetrain.turnToHeading(110, rotationUnits::deg,true);
    task::sleep(100);
    Drivetrain.setDriveVelocity(90, pct);
    Drivetrain.setTurnVelocity(90, pct);
    task::sleep(100); 
    
    //move forward
    Arm.rotateTo(0,deg,false);
    Intake.setVelocity(10, pct);
    Intake.spin(reverse);
    Drivetrain.setDriveVelocity(50, pct );
    Drivetrain.driveFor( 360, mm ,false);

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
    Drivetrain.driveFor( -350, mm );
    Intake.stop();
    Intake.setVelocity(100, pct);

}