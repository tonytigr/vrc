 #include "vex.h"

using namespace vex;

void run_auto_test(){

    task::sleep(500);
 //print
  Controller1.Screen.setCursor( 1, 1 );
  Controller1.Screen.print("autonomous running...");
  //move to x,y cm top right at speed percent
  moveCordinateGyro(0, 30, 50, 2, 0.3 );
  //turn  degrees clockwise
  TurnWithGyro( -90, 40, 2 ,0.4);
  //move to x,y cm top right at speed percent
  moveCordinateGyro(0, 30, 50, 2, 0.3 );
  //turn  degrees clockwise
  TurnWithGyro( -90, 40, 2 ,0.4);
  //move to x,y cm top right at speed percent
  moveCordinateGyro(0, 30, 50, 2, 0.3 );
  //turn  degrees clockwise
  TurnWithGyro( -90, 40, 2 ,0.4);
  //move to x,y cm top right at speed percent
  moveCordinateGyro(0, 30, 50, 2, 0.3 );
  //turn  degrees clockwise
  TurnWithGyro( -90, 40, 2 ,0.4);

}