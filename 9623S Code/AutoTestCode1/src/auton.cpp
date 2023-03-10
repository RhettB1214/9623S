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
    controller->setTarget({0_in, 0_in, -90_deg});
    controller->waitUntilSettled();
    controller->setTarget({48_in, -48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, 135_deg});

}


//Red Far Side Auton Function
void redFar()
{
    controller->setTarget({24_in, 0_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, -5_in, 0_deg});
    controller->waitUntilSettled();
    rollerMotor.moveVelocity(200);
    pros::delay(500);
    rollerMotor.moveVelocity(0);
    controller->setTarget({0_in, 0_in, 45_deg});
    controller->waitUntilSettled();
    controller->setTarget({-48_in, 48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, -90_deg});
    controller->waitUntilSettled();
    shoot();
    pros::delay(125);
    load();
    controller->setTarget({0_in, 0_in, 90_deg});
    controller->waitUntilSettled();
    controller->setTarget({-48_in, 48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, -135_deg});
}

//Blue Close Side Auton Function
void blueClose()
{
    controller->setTarget({5_in, 0_in, 0_deg});
    controller->waitUntilSettled();
    rollerMotor.moveVelocity(200);
    pros::delay(500);
    rollerMotor.moveVelocity(0);
    controller->setTarget({0_in, 0_in, -45_deg});
    controller->waitUntilSettled();
    controller->setTarget({-48_in, 48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, 90_deg});
    controller->waitUntilSettled();
    shoot();
    pros::delay(125);
    load();
    controller->setTarget({0_in, 0_in, -90_deg});
    controller->waitUntilSettled();
    controller->setTarget({-48_in, 48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, 135_deg});
}


//Blue Far Side Auton Function
void blueFar()
{
    controller->setTarget({-24_in, 0_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 5_in, 0_deg});
    controller->waitUntilSettled();
    rollerMotor.moveVelocity(200);
    pros::delay(500);
    rollerMotor.moveVelocity(0);
    controller->setTarget({0_in, 0_in, 45_deg});
    controller->waitUntilSettled();
    controller->setTarget({48_in, -48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, -90_deg});
    controller->waitUntilSettled();
    shoot();
    pros::delay(125);
    load();
    controller->setTarget({0_in, 0_in, 90_deg});
    controller->waitUntilSettled();
    controller->setTarget({48_in, -48_in, 0_deg});
    controller->waitUntilSettled();
    controller->setTarget({0_in, 0_in, -135_deg});
}

//Programming Skills Auton Function
void skills()
{

}
