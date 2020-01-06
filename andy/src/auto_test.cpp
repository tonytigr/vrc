#include "vex.h"

using namespace vex;

void run_auto_test(){

    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro0=%f", TurnGyroSmart.rotation());

    Drivetrain.setTurnVelocity(20, pct);
    Drivetrain.turnToHeading(90, rotationUnits::deg,true);
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro1=%f", TurnGyroSmart.rotation());
    task::sleep(1000);

    Drivetrain.turnToHeading(180, rotationUnits::deg,true);
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro2=%f", TurnGyroSmart.rotation());
    task::sleep(1000);

    Drivetrain.turnToHeading(270, rotationUnits::deg,true);
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro3=%f", TurnGyroSmart.rotation());
    task::sleep(1000);

    Drivetrain.turnToHeading(360, rotationUnits::deg,true);
    Controller1.Screen.setCursor( 1, 1 );
    Controller1.Screen.print("gyro4=%f", TurnGyroSmart.rotation());
    task::sleep(1000);

}