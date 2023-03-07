#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"
#include "pros/rtos.hpp"
#include "variables.hpp"
#include <cstdio>
#include <functional>
#include <ostream>


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
		RotationSensor{LEFT_ODOM},
        RotationSensor{RIGHT_ODOM},
        RotationSensor{BACK_ODOM}
	)
	.withClosedLoopControllerTimeUtil(50, 5, 250_ms)
	.withLogger(
		std::make_shared<Logger>(
			TimeUtilFactory::createDefault().getTimer(),
			"/ser/sout",
			Logger::LogLevel::debug
		)
	)
	.withMaxVelocity(150)
	/*.withGains({0.0015, 0.0, 0.000, 0.0},
		   	   {0.001, 0.0, 0.000, 0.0},
		       {0.001, 0.0, 0.000, 0.0})
	.withDerivativeFilters(std::make_unique<AverageFilter<3>>(),
						   std::make_unique<AverageFilter<3>>(),
						   std::make_unique<AverageFilter<3>>())*/
	.withDimensions(REGBOX, {{3.25_in, 9.5_in}, imev5GreenTPR})
	.withOdometry({{2.75_in, 12.5_in, 1_in, 2.75_in}, quadEncoderTPR}, StateMode::CARTESIAN)
	.buildOdometry();



	


//This casts the first chassis controller to a X-Drive specific chassis model
std::shared_ptr<ThreeEncoderXDriveModel> model = std::static_pointer_cast<ThreeEncoderXDriveModel> (chassis->getModel());

void drve()
 {
	model->fieldOrientedXArcade(
	master.getAnalog(ControllerAnalog::leftY),
	master.getAnalog(ControllerAnalog::leftX),
	master.getAnalog(ControllerAnalog::rightX),
	(imu.get())*degree,
	0.05);
 }

void shoot()
{
	
	while(limitSwitch.get_value() == 1)
	{
		cataMotors.moveVoltage(12000);
		drve();
	}
	cataMotors.moveVelocity(0);
}

void load()
{
	
	while (limitSwitch.get_value() == 0) 
	{
		cataMotors.moveVoltage(12000);
		drve();
	}
	cataMotors.moveVelocity(0);
	
}

void autonShoot()
{
	
	while(limitSwitch.get_value() == 1)
	{
		cataMotors.moveVoltage(12000);
	}
	cataMotors.moveVelocity(0);
}

void shortSideAutonRoute()
{
	chassis->setState({0_in, 0_in, 0_deg});
	chassis->stop();
	chassis->moveDistance(1.75_ft);
	chassis->waitUntilSettled();
	chassis->turnToAngle(-125_deg);
	chassis->waitUntilSettled();
	chassis->moveDistanceAsync(-3_ft);
	pros::delay(450);
	rollerMotor.moveRelative(200, 200);
	pros::delay(350);
	chassis->stop();
	chassis->waitUntilSettled();
	chassis->moveDistance(4_in);
	chassis->waitUntilSettled();
	chassis->turnAngle(-47.5_deg);
	chassis->waitUntilSettled();
	chassis->moveDistance(4.625_ft);
	chassis->waitUntilSettled();
	chassis->setMaxVelocity(100);
	chassis->turnAngle(123_deg);
	chassis->waitUntilSettled();
	chassis->setMaxVelocity(50);
	chassis->moveDistance(1.75_in);
	chassis->waitUntilSettled();
	//rollerMotor.moveVoltage(12000);
	pros::delay(1000);
	autonShoot();
	pros::delay(15);
	load();
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
	Logger::setDefaultLogger(
		std::make_shared<Logger>(
			TimeUtilFactory::createDefault().getTimer(),
			"/ser/sout",
			Logger::LogLevel::debug
		)
	);
	cataMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
	load();
	
	
} 

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() 
{

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() 
{

}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{
	shortSideAutonRoute();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() 
{


	//autonomous();

	while (true) 
	{
		model->fieldOrientedXArcade(
		master.getAnalog(ControllerAnalog::leftY),
		master.getAnalog(ControllerAnalog::leftX),
		master.getAnalog(ControllerAnalog::rightX),
		(imu.get() - lastIMUCheck)*degree,
		0.05);


		//Cata Control
		if (master.getDigital(B))
		{
			shoot();
			pros::delay(125);
			load();
		}
		if (master.getDigital(Y))
		{
			load();
		}


		//Roller Control
		if (master.getDigital(L1))
		{
			rollerMotor.moveRelative(200, 200);
		}
		if (master.getDigital(L2))
		{
			rollerMotor.moveRelative(-200, 200);
		}


		//Intake Control
       if (master.getDigital(R1))
	   {
		intakeMotors.moveVoltage(12000);
		if (master.getDigital(B))
		{
			shoot();
			pros::delay(125);
			load();
		}
	   }
	   if(master.getDigital(R2))
	   {
		intakeMotors.moveVoltage(-12000);
		if (master.getDigital(B))
		{
			shoot();
			pros::delay(125);
			load();
		}
	   }
	   if(master.getDigital(R1) == 0 && master.getDigital(R2) == 0)
	   {
		intakeMotors.moveVoltage(0);
	   }
	   while(master.getDigital(X))
	   {
		printf("X: %f\n", chassis->getState().x.convert(foot));
		printf("Y: %f\n", chassis->getState().y.convert(foot));
		printf("Angle: %f\n", chassis->getState().theta.convert(degree));
	   }
	}
	
}
