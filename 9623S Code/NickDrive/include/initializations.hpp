#include "main.h"
#include "definitions.hpp"

using namespace okapi;

extern Motor intakeMotor;
extern Motor rollerMotor;
extern MotorGroup cataMotors;
extern Controller master;
extern pros::ADIDigitalIn limitSwitch;
extern pros::ADIDigitalOut endgamePiston;
extern pros::ADIDigitalOut blockerPiston;
extern IMU imu;
extern MotorGroup intakeMotors;
extern Motor leftFront;
extern Motor rightFront;
extern Motor leftBack;
extern Motor rightBack;
extern RotationSensor leftEnc;
extern RotationSensor rightEnc;
extern RotationSensor midEnc;
