#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "chassisBuilder.hpp"
#include "functions.hpp"
#include "variables.hpp"
#include "gui.hpp"
#include "auton.hpp"


using namespace okapi;



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
	endgamePiston.set_value(0);
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
	createButtons();
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
	switch(autonID)
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
	}



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
		controller->HolonomicLib::AsyncHolonomicChassisController::getPose().theta,
		0.05);


		//Cata Control
		if (master.getDigital(Y))
		{
			shoot();
			pros::delay(125);
			load();
		}


		//Roller Control
		if (master.getDigital(R1))
		{
			rollerMotor.moveVoltage(12000);
		}
		if (master.getDigital(R2))
		{
			rollerMotor.moveVoltage(-12000);
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
		    intakeMotor.moveVoltage(12000);
            shouldIntakeOuttake = false;
        }else if(shouldIntakeOuttake == true)
        {
            intakeMotor.moveVoltage(-12000);
            shouldIntakeIntake = false;
        }else if(shouldIntakeIntake == false && shouldIntakeOuttake == false)
	    {
			intakeMotor.moveVoltage(0);
	    }else 
	    {
		    //shouldIntakeRun is neither true nor false, so do nothing
	    }


		//Endgame Control
		if (master.getDigital(L1) && master.getDigital(L2) && master.getDigital(R1) && master.getDigital(R2))
		{
			endgamePiston.set_value(1);
		}

		
	}

}

