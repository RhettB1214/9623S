#include "main.h"
#include "definitions.hpp"
#include "init.hpp"

pros::Motor frontLeft(FL_DRIVE, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor frontRight(FR_DRIVE, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor backLeft(BL_DRIVE, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor backRight(BR_DRIVE, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor cataMotor1(LCATA_MOTOR, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor cataMotor2(RCATA_MOTOR, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotor(INTAKE_MOTOR, MOTOR_GEARSET_06, false, MOTOR_ENCODER_DEGREES);
pros::Motor rollerMotor(ROLLER_MOTOR, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

pros::MotorGroup leftDrive({frontLeft, backLeft});
pros::MotorGroup rightDrive({frontRight, backRight});
pros::MotorGroup cataMotors({cataMotor1, cataMotor2});
pros::MotorGroup intakeMotors({intakeMotor, rollerMotor});

pros::Rotation leftOdom(LEFT_ODOM);
pros::Rotation rightOdom(RIGHT_ODOM);
pros::Rotation midOdom(BACK_ODOM);

pros::Imu imu(IMU_PORT);

pros::ADIDigitalIn limitSwitch({{THREE_WIRE_EXPANDER, LIMIT_SWITCH}});
pros::ADIDigitalOut endgamePiston(ENDGAME_PISTON);


