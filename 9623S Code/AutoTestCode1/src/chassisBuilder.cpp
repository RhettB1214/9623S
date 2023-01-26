#include "chassisBuilder.hpp"
#include "initializations.hpp"
#include "definitions.hpp"

using namespace okapi;

//This builder builds a odometry enabled chassis controller using OkapiLib
std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
	.withMotors(
		FL_DRIVE, 
		FR_DRIVE,
		BR_DRIVE, 
		BL_DRIVE
	)
	.withSensors(
		RotationSensor(RIGHT_ODOM, false),
		RotationSensor(LEFT_ODOM, false),
		RotationSensor(BACK_ODOM, false)
	)
	.withOdometry({{2.75_in, 7_in, 1_in, 2.75_in}, quadEncoderTPR})
	.buildOdometry();


//This casts the previously built chassis controller to one that can be ran asynchronously with other processes
std::shared_ptr<HolonomicLib::AsyncHolonomicChassisController> controller = HolonomicLib::AsyncHolonomicChassisControllerBuilder(chassis)
    // PID gains (must be tuned for your robot)
    .withDistGains(
        {0.05, 0.0, 0.00065, 0.0} // Translation gains
    )
    .withTurnGains(
        {0.05, 0.0, 0.00065, 0.0} // Turn gains
    )
    .build();
	


//This casts the first chassis controller to a X-Drive specific chassis model
std::shared_ptr<XDriveModel> model = std::static_pointer_cast<XDriveModel> (chassis->getModel());


