#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/rotationSensor.hpp"
#include "pros/adi.hpp"

using namespace okapi;

Controller(master);

Motor cataMotor1(LCATA_MOTOR, false, TORQUEBOX, DEGREES);
Motor cataMotor2(RCATA_MOTOR, true, TORQUEBOX, DEGREES);
Motor intakeMotor(INTAKE_MOTOR, false, REGBOX, DEGREES);
Motor rollerMotor(ROLLER_MOTOR, false, REGBOX, DEGREES);


okapi::MotorGroup(cataMotors)({cataMotor1, cataMotor2});
okapi::MotorGroup(intakeMotors)({intakeMotor, rollerMotor});


pros::ADIDigitalIn limitSwitch({{21, 'A'}});
pros::ADIDigitalOut endgamePiston(ENDGAME_PISTON);

IMU imu(IMU_PORT);




