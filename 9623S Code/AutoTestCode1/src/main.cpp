#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "chassisBuilder.hpp"
#include "functions.hpp"
#include "pros/rtos.hpp"
#include "variables.hpp"
#include "auton.hpp"
#include "gui.hpp"


using namespace okapi;

//This builder builds a odometry enabled chassis controller using OkapiLib
std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
	.withMotors(
		FLDrive, 
		FRDrive,
		BRDrive, 
		BLDrive
	)
    .withDimensions(REGBOX, {{3.25_in, 9.5_in}, imev5GreenTPR})
	.withSensors(
		RotationSensor{LEFT_ODOM},
        RotationSensor{RIGHT_ODOM},
        RotationSensor{BACK_ODOM}
	)
	.withOdometry({{2.75_in, 12.5_in, 0_in, 2.75_in}, quadEncoderTPR})
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
std::shared_ptr<XDriveModel> model = std::static_pointer_cast<XDriveModel> (chassis->getModel());


void autonomousTurn(double targetDeg, float kP, float kI, float kD)
{
	double error;
	double integral;
	double lastError;
	double derivative;
	double totalError = 0;
	double integralActiveZone = 15;
	double power = targetDeg;
	while (imu.get() != targetDeg)
	{
		if (error == 0)
			{
				lastError = 0;
			}
			if (abs(error) < integralActiveZone && error != 0)
			{
				totalError += error;
			}else {
				totalError = 0;
			}
			float finalAdjustment = (error * kP) + (totalError * kI) + ((error - lastError) * kD);
			int AdjustedPower = power + finalAdjustment;
			if (AdjustedPower > 200)
			{
				AdjustedPower = 200;
			}
			if (AdjustedPower < -200)
			{
				AdjustedPower = -200;
			}
			model->rotate(AdjustedPower);
			pros::delay(5);
	}
	model->stop();
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
	
	
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
	//createButtons();
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
	/*switch(autonID)
	{
	case 1:
			redClose();
			break;
	case 2:
			redFar();
			break;
	case 3:
			blueClose();
			break;
	case 4:
			blueFar();
			break;
	case 5:
			skills();
			break;
	case 0:
			opcontrol();
			break;
	}*/



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
		//Drivetrain Control
		model->fieldOrientedXArcade(
		master.getAnalog(ControllerAnalog::leftY),
		master.getAnalog(ControllerAnalog::leftX),
		master.getAnalog(ControllerAnalog::rightX),
		imu.get()*degree,
		0.05);


		//Turn Function
		if (master.getDigital(Y))
		{
			autonomousTurn(90, kP, kI, kD);
		}

		//PID Tuning
		if (master.getDigital(Up) && master.getDigital(R1))
		{
			kP += 0.01;
			pros::delay(100);
		}
		else if (master.getDigital(Down) && master.getDigital(R1))
		{
			kP -= 0.01;
			pros::delay(100);
		}
		else if (master.getDigital(Up) && master.getDigital(R2))
		{
			kI += 0.01;
			pros::delay(100);
		}
		else if (master.getDigital(Down) && master.getDigital(R2))
		{
			kI -= 0.01;
			pros::delay(100);
		}
		else if (master.getDigital(Up) && master.getDigital(L1))
		{
			kD += 0.01;
			pros::delay(100);
		}
		else if (master.getDigital(Down) && master.getDigital(L1))
		{
			kD -= 0.01;
			pros::delay(100);
		}
		else if (master.getDigital(Right) && master.getDigital(R1))
		{
			kP += 0.1;
			pros::delay(100);
		}
		else if (master.getDigital(Left) && master.getDigital(R1))
		{
			kP -= 0.1;
			pros::delay(100);
		}
		else if (master.getDigital(Right) && master.getDigital(R2))
		{
			kI += 0.1;
			pros::delay(100);
		}
		else if (master.getDigital(Left) && master.getDigital(R2)) 
		{
			kI -= 0.1;
			pros::delay(100);
		}
		else if (master.getDigital(Right) && master.getDigital(L1))
		{
			kD += 0.1;
			pros::delay(100);
		}
		else if (master.getDigital(Left) && master.getDigital(L1))
		{
			kD -= 0.1;
			pros::delay(100);
		}
		else if (master.getDigital(A))
		{
			pros::lcd::print(0, "kP: %f", kP);
			pros::lcd::print(1, "kI: %f", kI);
			pros::lcd::print(2, "kD: %f", kD);
			pros::delay(100);
		}





	}

}

