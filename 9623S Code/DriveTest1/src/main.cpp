#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"

#include "variables.hpp"


using namespace okapi;

//This builder builds a odometry enabled chassis controller using OkapiLib
std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
	.withMotors(
		FL_DRIVE, 
		FR_DRIVE,
		BR_DRIVE,
		BL_DRIVE
	)
	.withDimensions(REGBOX, {{3.25_in, 9.5_in}, imev5GreenTPR})
	.withSensors(
		RotationSensor{LEFT_ODOM},
        RotationSensor{RIGHT_ODOM},
        RotationSensor{BACK_ODOM}
	)
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

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


 void drve()
 {
	model->fieldOrientedXArcade(
	master.getAnalog(ControllerAnalog::leftY),
	master.getAnalog(ControllerAnalog::leftX),
	master.getAnalog(ControllerAnalog::rightX),
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
	
	while (limitSwitch.get_value() == 0) 
	{
		cataMotors.moveVoltage(12000);
		drve();
	}
	cataMotors.moveVelocity(0);
	
}
void initialize() 
{
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
		imu.get()*degree,
		0.05);


		//Cata Control
		if (master.getDigital(B))
		{
			shoot();
			load();
		}
		if (master.getDigital(Y))
		{
			load();
		}


		//Roller Control
		if (master.getDigital(R1))
		{
			rollerMotor.moveVoltage(6000);
		}
		if (master.getDigital(R2))
		{
			rollerMotor.moveVoltage(-6000);
		}


		//Intake Control
        //Intake Variable Toggle Code
        if(master.getDigital(L1) != lastKnownStateOfButtonIntake)
	    // check if the button's state is different from its last known state (has there been a change?)
	    {

			lastKnownStateOfButtonIntake = master.getDigital(L1); //updates last know state of button for next loop

			if(master.getDigital(L1))
			//check the new state of the button (what just happened?)
			{

				//the button was just pressed, so toggle the state of the intake
				if(shouldIntakeIntake == true)
				{
					shouldIntakeIntake = false;
				}
				else if(shouldIntakeIntake == false)
				{
					shouldIntakeIntake = true;
				}
				else
				{
					//the button was just released, but we dont care, so do nothing
				}
			}
	    }

        //Outtake Variable Toggle Code
        if(master.getDigital(L2) != lastKnownStateOfButtonOuttake)
        {
			lastKnownStateOfButtonOuttake = master.getDigital(L2);

			if(master.getDigital(L2))
			{
				if(shouldIntakeOuttake == true)
				{
					shouldIntakeOuttake = false;
				}
				else if(shouldIntakeOuttake == false)
				{
					shouldIntakeOuttake = true;
				}
				else
				{
					//the button was just released, but we dont care, so do nothing
				}
			}
        }

	    //Intake & Outake Controll Toggle Code
	    if(shouldIntakeIntake == true)
	    //Spins the Motor if shouldIntakeRun is equal to true
	    {
		    intakeMotors.moveVoltage(12000);
            shouldIntakeOuttake = false;
        }else if(shouldIntakeOuttake == true)
        {
            intakeMotors.moveVoltage(-12000);
            shouldIntakeIntake = false;
        }else if(shouldIntakeIntake == false && shouldIntakeOuttake == false)
	    {
			intakeMotors.moveVelocity(0);
	    }else 
	    {
		    //shouldIntakeRun is neither true nor false, so do nothing
	    }
	}
	
}
