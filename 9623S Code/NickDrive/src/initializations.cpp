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
Motor intakeMotor(INTAKE_MOTOR, false, SPEEDBOX, DEGREES);
Motor rollerMotor(ROLLER_MOTOR, false, REGBOX, DEGREES);
Motor leftFront = Motor(FL_DRIVE, false, REGBOX, DEGREES);
Motor rightFront = Motor(-FR_DRIVE, true, REGBOX, DEGREES);
Motor leftBack = Motor(BL_DRIVE, false, REGBOX, DEGREES);
Motor rightBack = Motor(-BR_DRIVE, true, REGBOX, DEGREES);
RotationSensor leftEnc = RotationSensor(LEFT_ODOM);
RotationSensor rightEnc = RotationSensor(RIGHT_ODOM);
RotationSensor midEnc = RotationSensor(BACK_ODOM);


okapi::MotorGroup(cataMotors)({cataMotor1, cataMotor2});
okapi::MotorGroup(intakeMotors)({intakeMotor, rollerMotor});


pros::ADIDigitalIn limitSwitch({{21, 'A'}});
pros::ADIDigitalOut endgamePiston(ENDGAME_PISTON);
pros::ADIDigitalOut blockerPiston(BLOCKER_PISTON);

IMU imu(IMU_PORT);




