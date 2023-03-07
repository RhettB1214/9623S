#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "variables.hpp"


using namespace okapi;

//This builder builds a odometry enabled chassis controller using OkapiLib
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


//This casts the previously built chassis controller to one that can be ran asynchronously with other processes
std::shared_ptr<HolonomicLib::AsyncHolonomicChassisController> controller = HolonomicLib::AsyncHolonomicChassisControllerBuilder(chassis)
    // PID gains (must be tuned for your robot)
    .withDistGains(
        {0.05, 0.0, 0.00065, 0.0} // Translation gains
    )
    .withTurnGains(
        {0.05, 0.0, 0.00065, 0.0} // Turn gains
    )
	.withDistSettleParameters(
        0.5_in, // Max error
        2.0_in / 1_s, // Max derivative
        100_ms // Wait time
    )
    .withTurnSettleParameters(
        5_deg, // Max error
        20_deg / 1_s, // Max derivative
        100_ms // Wait time
    )
    .build();
	


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
	chassis->setState({0_in, 0_in, 0_deg});
	chassis->moveDistance(1.75_ft);
	chassis->turnToAngle(-125_deg);
	chassis->moveDistanceAsync(-3_ft);
	pros::delay(450);
	rollerMotor.moveRelative(200, 200);
	pros::delay(350);
	chassis->stop();
	chassis->moveDistance(4_in);
	chassis->turnAngle(-50_deg);
	chassis->moveDistance(4.75_ft);
	chassis->setMaxVelocity(100);
	chassis->turnAngle(123_deg);
	chassis->setMaxVelocity(50);
	chassis->moveDistance(-6_in);
	rollerMotor.moveVoltage(12000);
	pros::delay(500);
	autonShoot();
	pros::delay(15);
	load();
	pros::delay(15);
	intakeMotors.moveVoltage(12000);
	pros::delay(600);
	autonShoot();
	pros::delay(15);
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

	
	
	while (true) 
	{
		model->fieldOrientedXArcade(
		master.getAnalog(ControllerAnalog::leftY),
		master.getAnalog(ControllerAnalog::leftX),
		master.getAnalog(ControllerAnalog::rightX),
		(imu.get()) *degree,
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
		while (master.getDigital(L1))
		{
			rollerMotor.moveVoltage(6000);
		}
		while (master.getDigital(L2))
		{
			rollerMotor.moveVoltage(-6000);
		}


		//Intake Control
       if (master.getDigital(R1)&& limitSwitch.get_value() == 1)
	   {
		intakeMotors.moveVoltage(12000);
		if (master.getDigital(B))
		{
			shoot();
			pros::delay(125);
			load();
		}
	   }
	   if(master.getDigital(R2) && limitSwitch.get_value() == 1)
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


	   if (master.getDigital(X) && master.getDigital(Up))
	   {
		   blockerDeployed = true;
		   blockerPiston.set_value(1);
		   pros::delay(50);
		   blockerPiston.set_value(0);
		   pros::delay(50);
		   blockerPiston.set_value(1);
		   pros::delay(50);
		   blockerPiston.set_value(0);
		   pros::delay(50);
		   blockerPiston.set_value(1);
	   }

	   if (master.getDigital(L1) && master.getDigital(L2) && master.getDigital(R1) && master.getDigital(R2))
	   {
		   endgamePiston.set_value(1);
	   }
	}
	
}
