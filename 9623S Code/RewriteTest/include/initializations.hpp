#include "main.h"

using namespace okapi;


extern Controller master;
extern Motor cataMotor1;
extern Motor cataMotor2;
extern Motor intakeMotor;
extern Motor rollerMotor;
extern MotorGroup cataMotors;
extern MotorGroup intakeMotors;
extern pros::ADIDigitalIn limitSwitch;
extern pros::ADIDigitalOut endgamePiston;
extern IMU imu;