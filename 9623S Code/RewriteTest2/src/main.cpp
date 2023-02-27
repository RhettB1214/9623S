#include "main.h"
#include "definitions.hpp"
#include "inits.hpp"

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
															Logger::LogLevel::info
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
	chassis->moveDistanceAsync(-1_ft); //Drives the Robot back into the roller Asyncronsly 
	pros::delay(250); //Waits 250 milliseconds
	rollerMotor.moveRelative(250, 200); //Spins the Roller Motor 250 degrees
	pros::delay(250); //Waits 250 milliseconds
	chassis->stop(); //Stops the Chassis
	chassis->moveDistance(4_in); //Drives the Chassis 4 inches off of the Roller
	intakeMotors.moveVoltage(12000); //Turns the intake system on
	pros::delay(50); //Waits for 50 milliseconds 
	chassis->turnAngle(180_deg); //Turns the robot 135 degrees because it accounts for error in the robot
	chassis->setMaxVelocity(100); //Sets the robots maximum Chassis velocities 100 RPM
	chassis->moveDistance(-1.325_ft); //Drives the Robot 1.325 feet and picks up the first disc
	intakeMotors.moveVelocity(0); //Turns the intake off
	chassis->setMaxVelocity(200); //Sets the Maximum chassis velocity to 200 RPM
	chassis->turnAngle(-55_deg); //Turns the robot 45 degrees to the left accounting for error in the robot
	chassis->moveDistanceAsync(-3_ft); //Moves the robot 3 feet backwards into the roller
	pros::delay(450); //waits 450 milliseconds to give the robot time to make it to the roller
	rollerMotor.moveRelative(250, 200); //Spins the Roller motor 250 degrees
	pros::delay(450); //Waits 450 milliseconds giving the robot time to spin the roller
	chassis->stop(); //Stops the chassis
	chassis->moveDistance(6_in); //Moves the robot 6 inches off the roller
	chassis->waitUntilSettled(); //Waits until the chassis has stopped moving
	intakeMotors.moveVoltage(12000); //Turns the intake system on
	pros::delay(50); //Waits 50 milliseconds
	chassis->turnAngle(-112.5_deg); //Turns the robot 90 degrees to the left accounting for error in the robot
	chassis->setMaxVelocity(125); //Sets the maximum chassis velocity to 125 RPM
	chassis->moveDistance(3.5_ft); //Drives the robot forward 3.5 feet
	chassis->waitUntilSettled();//Waits untill the robot has stopped moving
	intakeMotors.moveVelocity(0); //Turns the intake off to help with shot grouping
	pros::delay(50); //Waits 50 milliseconds
	autonShoot(); //Fires the first volley of discs
	pros::delay(25); //waits 25 milliseconds
	chassis->moveDistanceAsync(-1.625_ft);
	pros::delay(25);
	load();
	pros::delay(25);
	chassis->stop();
	chassis->setMaxVelocity(100);
	chassis->turnAngle(-135_deg);
	intakeMotors.moveVoltage(12000);
	chassis->moveDistance(-1.5_ft);
	chassis->turnAngle(-55_deg);
	chassis->moveDistance(-2.5_ft);
	chassis->turnAngle(120_deg);
	chassis->moveDistance(0.5_ft);
	chassis->waitUntilSettled();
	pros::delay(1000);
	intakeMotors.moveVelocity(0);
	pros::delay(50);
	autonShoot();
	pros::delay(25);
	load();



	


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
	
}
