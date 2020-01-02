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

extern int arm_level;
extern int arm_level_previous;
//arm position 0 - ground 1- elevated 2 - lower tower 3 - middle tower level
extern int arm_position[4] ;

extern int Tray_Velocity ;
extern int tray_max_degrees ;
extern int tray_position[4] ;

extern int idle_flag ;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
void run_auto_15();
void run_auto_60();
void blue_rectangle();
void blue_square();
void red_rectangle();
void red_square();