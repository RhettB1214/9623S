#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/adi.hpp"

using namespace okapi;

Controller(master);

Motor cataMotor1(CATA_MOTOR1, true, TORQUEBOX, DEGREES);
Motor cataMotor2(CATA_MOTOR2, true, TORQUEBOX, DEGREES);
Motor intakeMotor(INTAKE_MOTOR, true, REGBOX, DEGREES);
Motor rollerMotor(ROLLER_MOTOR, false, REGBOX, DEGREES);

okapi::MotorGroup(cataMotors)({cataMotor1, cataMotor2});


pros::ADIDigitalIn limitSwitch(LIMIT_SWITCH);
pros::ADIDigitalOut endgamePiston(ENDGAME_PISTON);





