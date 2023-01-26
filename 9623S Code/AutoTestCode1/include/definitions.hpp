#include "main.h"


//Drive Motor Definitions
#define FL_DRIVE 1
#define FR_DRIVE -2
#define BL_DRIVE 3
#define BR_DRIVE -4


//Game object Motor Definitions
#define CATA_MOTOR1 11
#define CATA_MOTOR2 20
#define INTAKE_MOTOR 7
#define ROLLER_MOTOR 8


//Sensor Definitions
#define RIGHT_ODOM 9
#define LEFT_ODOM 10
#define BACK_ODOM 12

//Three Wire Port Definitions
#define LIMIT_SWITCH 'A'
#define ENDGAME_PISTON 'B'



//Controller Inputs
#define L1 okapi::ControllerDigital::L1
#define L2 okapi::ControllerDigital::L2
#define R1 okapi::ControllerDigital::R1
#define R2 okapi::ControllerDigital::R2
#define A okapi::ControllerDigital::A
#define B okapi::ControllerDigital::B
#define X okapi::ControllerDigital::X
#define Y okapi::ControllerDigital::Y
#define Up okapi::ControllerDigital::up
#define Down okapi::ControllerDigital::down
#define Right okapi::ControllerDigital::right
#define Left okapi::ControllerDigital::left
#define LeftX okapi::ControllerAnalog::leftX
#define LeftY okapi::ControllerAnalog::leftY
#define RightX okapi::ControllerAnalog::rightX
#define RightY okapi::ControllerAnalog::rightY

//Gearbox Definitions
#define TORQUEBOX okapi::AbstractMotor::gearset::red
#define REGBOX okapi::AbstractMotor::gearset::green
#define SPEEDBOX okapi::AbstractMotor::gearset::blue

//Unit Definitions
#define DEGREES okapi::AbstractMotor::encoderUnits::degrees
#define ROTATIONS okapi::AbstractMotor::encoderUnits::rotations