#include "main.h"
#include "definitions.hpp"

using namespace okapi;

extern Motor intakeMotor;
extern Motor rollerMotor;
extern MotorGroup cataMotors;
extern Controller master;
extern pros::ADIDigitalIn limitSwitch;
extern pros::ADIDigitalOut endgamePiston;
extern pros::ADIDigitalOut cataPiston;
extern Motor FLDrive;
extern Motor FRDrive;
extern Motor BLDrive;
extern Motor BRDrive;
extern RotationSensor leftOdom;
extern RotationSensor rightOdom;
extern RotationSensor centerOdom;
extern IMU imu;
