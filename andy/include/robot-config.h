using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern smartdrive Drivetrain;
extern controller Controller1;
extern motor Arm;
extern motor Tray;
extern motor LeftIntake;
extern motor RightIntake;
extern motor_group Intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
void run_auto_15();
