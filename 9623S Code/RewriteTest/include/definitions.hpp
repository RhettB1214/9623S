#include "main.h"


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