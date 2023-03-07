#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/device/rotarysensor/rotationSensor.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"

using namespace okapi;

Controller(master);

Motor cataMotor1(LCATA_MOTOR, false, TORQUEBOX, DEGREES);
Motor cataMotor2(RCATA_MOTOR, true, TORQUEBOX, DEGREES);
Motor intakeMotor(INTAKE_MOTOR, true, REGBOX, DEGREES);
Motor rollerMotor(ROLLER_MOTOR, false, REGBOX, DEGREES);
Motor FLDrive(FL_DRIVE, false, REGBOX, DEGREES);
Motor FRDrive(FR_DRIVE, true, REGBOX, DEGREES);
Motor BLDrive(BL_DRIVE, false, REGBOX, DEGREES);
Motor BRDrive(BR_DRIVE, true, REGBOX, DEGREES);
RotationSensor leftOdom(LEFT_ODOM);
RotationSensor rightOdom(RIGHT_ODOM);
RotationSensor centerOdom(BACK_ODOM);
IMU imu(IMU_PORT);

okapi::MotorGroup(cataMotors)({cataMotor1, cataMotor2});


pros::ADIDigitalIn limitSwitch({{21, 'A'}});
pros::ADIDigitalOut endgamePiston(ENDGAME_PISTON);






