#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"

using namespace okapi;

Controller(master);

Motor cataMotor1(9, false, TORQUEBOX, DEGREES);
Motor cataMotor2(10, true, TORQUEBOX, DEGREES);
Motor intakeMotor(1, false, SPEEDBOX, DEGREES);
Motor rollerMotor(2, false, REGBOX, DEGREES);

MotorGroup cataMotors({cataMotor1, cataMotor2});
MotorGroup intakeMotors({intakeMotor, rollerMotor});

pros::ADIDigitalIn limitSwitch({{21,'A'}});
pros::ADIDigitalOut endgamePiston('F');

IMU imu(15);