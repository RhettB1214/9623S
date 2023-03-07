#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "functions.hpp"
#include "variables.hpp"
#include "chassisBuilder.hpp"

void load()
{
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
	
}

