#include "vex.h"

using namespace vex;
void red_square(){
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
    moveCordinateGyro(0, 1400, 30, 2, 0.3);
    task::sleep(100);

    //stop intake
    LeftIntake.stop();
    RightIntake.stop();
    //move back
    moveCordinateGyro(0, -890, 90, 2, 0.3);

    task::sleep(100);
    //turn left toward blue square
    TurnWithGyro(132, 20, 2 ,0.4);
    task::sleep(100); 
    //move forward
    Arm.rotateTo(0,deg,false);
    Intake.setVelocity(10, pct);
    Intake.spin(reverse);
    moveCordinateGyro(0, 370, 50, 2, 0.3);

    //push tray
    Tray.setVelocity(45, pct);
    Intake.setVelocity(27, pct);
    Intake.spin(reverse);
    Tray.rotateTo(850,degrees, true);
    //move forward
    moveCordinateGyro(0, 20, 15, 2, 0.3);
    task::sleep(100);
    //put tray
    Tray.setVelocity(80, pct);
    Tray.rotateTo(0,degrees, false);
    //move back
    moveCordinateGyro(0, -300, 80, 2, 0.3);
    Intake.stop();
    Intake.setVelocity(100, pct);

}