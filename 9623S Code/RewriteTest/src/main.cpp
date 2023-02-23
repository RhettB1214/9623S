#include "main.h"
#include "ARMS/config.h"
#include "initializations.hpp"
#include "definitions.hpp"

using namespace okapi;

std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
	.withMotors(6, -8, -7, 5)
	.withSensors(RotationSensor{20}, RotationSensor{18}, RotationSensor{19})
	.withClosedLoopControllerTimeUtil(50, 5, 250_ms)
	.withLogger(
			std::make_shared<Logger>(
												TimeUtilFactory::createDefault().getTimer(),
												"/ser/sout",
												Logger::LogLevel::info
											)
			   )
	.withMaxVelocity(200)
	.withDimensions(AbstractMotor::gearset::green, {{3.25_in, 9.5_in}, imev5GreenTPR})
	.withOdometry({{2.75_in, 12.5_in, 1_in, 2.75_in}, quadEncoderTPR}, StateMode::CARTESIAN)
	.buildOdometry();

std::shared_ptr<ThreeEncoderXDriveModel> model = std::static_pointer_cast<ThreeEncoderXDriveModel> (chassis->getModel());


void drve()
{
	model->fieldOrientedXArcade(
	master.getAnalog(LeftY), 
	master.getAnalog(LeftX), 
	master.getAnalog(RightX), 
	imu.get()*degree,
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
	while(limitSwitch.get_value() == 0)
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

void shortSideAuton()
{
	arms::chassis::move({24, 12, -90});
	arms::chassis::waitUntilFinished(0.5);
	chassis->moveDistanceAsync(-3_ft);
	pros::delay(450);
	rollerMotor.moveRelative(200, 200);
	pros::delay(350);
	chassis->stop();
	chassis->moveDistance(4_in);
	chassis->waitUntilSettled();
	arms::chassis::move({42, 18, -45});
	arms::chassis::move(1.75);
	pros::delay(750);
	autonShoot();
	pros::delay(30);
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
	arms::init();
	Logger::setDefaultLogger(
						std::make_shared<Logger>(
															TimeUtilFactory::createDefault().getTimer(),
															"/ser/sout",
															Logger::LogLevel::info
														)
			   				);
	cataMotors.setBrakeMode(AbstractMotor::brakeMode::hold);



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
	shortSideAuton();
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
	while(true)
	{

		//Drive Code
		model->fieldOrientedXArcade(
		master.getAnalog(LeftY),
		master.getAnalog(LeftX),
		master.getAnalog(RightX),
		imu.get()*degree,
		0.05);


		//Cata Control
		if (master.getDigital(B))
		{
			shoot();
			pros::delay(125);
			load();
		}
		if(master.getDigital(Y))
		{
			load();
		}


		//Roller Control
		if(master.getDigital(L1))
		{
			rollerMotor.moveVoltage(12000);
		}
		else if(master.getDigital(L2))
		{
			rollerMotor.moveVoltage(-12000);
		}

		//Intake Control
		if(master.getDigital(R1) && limitSwitch.get_value() == 1)
		{
			intakeMotor.moveVoltage(12000);
		}
		else if(master.getDigital(R2) && limitSwitch.get_value() == 1)
		{
			intakeMotor.moveVoltage(-12000);
		}
		else
		{
			intakeMotor.moveVoltage(0);
		}


		//Endgame Control
		if(master.getDigital(L1) && master.getDigital(R1) && master.getDigital(L2) && master.getDigital(R2))
		{
			endgamePiston.set_value(1);
		}
		else
		{
			endgamePiston.set_value(0);
		}

		
	}
	
	
}
