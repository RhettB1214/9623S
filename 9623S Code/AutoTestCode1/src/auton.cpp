#include "main.h"
#include "definitions.hpp"
#include "initializations.hpp"
#include "chassisBuilder.hpp"
#include "functions.hpp"
#include "variables.hpp"
#include "auton.hpp"

using namespace okapi;


//Red Close Side Auton Function
void redClose()
{
    controller->setTarget({-5_in, 0_in, 0_deg});
    controller->waitUntilSettled();
    rollerMotor.moveVelocity(200);
    pros::delay(500);
    rollerMotor.moveVelocity(0);
    controller->setTarget({0_in, 0_in, -45_deg});
    controller->waitUntilSettled();
    controller->setTarget({48_in, -48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, 90_deg});
    controller->waitUntilSettled();
    shoot();
    pros::delay(125);
    load();
    pros::delay(125);
    controller->setTarget({0_in, 0_in, -90_deg});
    controller->waitUntilSettled();
    controller->setTarget({-48_in, -48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, 135_deg});
    controller->waitUntilSettled();

}


//Red Far Side Auton Function
void redFar()
{

}

//Blue Close Side Auton Function
void blueClose()
{

}


//Blue Far Side Auton Function
void blueFar()
{

}

//Programming Skills Auton Function
void skills()
{

}
