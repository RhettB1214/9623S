#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "functions.hpp"

void load()
{
	cataMotors.moveRelative(998, 100);
	cataMotors.moveVelocity(0);
	while (limitSwitch.get_value() == 0) 
	{
	cataMotors.moveVelocity(100);
	}
	while (limitSwitch.get_value() == 1) 
	{
	cataMotors.moveVelocity(0);
	}
}

void shoot()
{
	cataMotors.moveRelative(90, 100);
	cataMotors.moveVelocity(0);
	cataPiston.set_value(0);
}