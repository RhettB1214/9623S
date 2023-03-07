#include "main.h"
#include "definitions.hpp"
#include "init.hpp"


lemlib::Drivetrain_t drivetrain
{
    &leftDrive,
    &rightDrive,
    10,
    3.25,
    200
};

lemlib::TrackingWheel leftOdomWheel(&leftOdom, 2.75, -6.25);
lemlib::TrackingWheel rightOdomWheel(&rightOdom, 2.75, 6.25);
lemlib::TrackingWheel midOdomWheel(&midOdom, 2.75, 0);

lemlib::OdomSensors_t odomSensors
{
    &leftOdomWheel,
    &rightOdomWheel,
    &midOdomWheel,
    nullptr,
    &imu
};

//forward/backward PID
lemlib::ChassisController_t lateralController
{
    0, //kP
    0, //kD
    1, //smallErrorRange
    100, //smallErrorTimeout
    3, //largeErrorRange
    500, //largeErrorTimeout
    5 //Slew Rate

};

//turning PID
lemlib::ChassisController_t angularController
{
    0, //kP
    0, //kD
    1, //smallErrorRange
    100, //smallErrorTimeout
    3, //largeErrorRange
    500, //largeErrorTimeout
    5 //Slew Rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, odomSensors);



void screen() 
{
    while(true)
    {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(0, "X: %f", pose.x);
        pros::lcd::print(1, "Y: %f", pose.y);
        pros::lcd::print(2, "Angle: %f", pose.theta);
    }
}


void load()
{
    while(limitSwitch.get_value() == 0)
	{
		cataMotors.move_voltage(12000);
	}
	cataMotors.move_velocity(0);
}

void autonShoot()
{
	while(limitSwitch.get_value() == 1)
	{
		cataMotors.move_voltage(12000);
	}
	cataMotors.move_velocity(0);
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
    load();
	chassis.calibrate();
    pros::Task screenTask(screen);
    chassis.setPose(62, -41, -90);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
    chassis.setPose(62, -41, 90);
    chassis.moveTo(62, -44, 250);
    rollerMotor.move_relative(250, 200);
    pros::delay(300);
    chassis.setPose(62, -41, -90);
    chassis.moveTo(54, -41, 250, 200);
    intakeMotors.move_voltage(12000);
    chassis.turnTo(48, -48, 250, true);
    chassis.setPose(54, -41, 135);
    chassis.moveTo(43, -55, 250);
    intakeMotors.move_voltage(0);
    chassis.turnTo(42, -48, 250, false);
    chassis.moveTo(42, -67, 100);
    rollerMotor.move_relative(250, 200);
    pros::delay(300);
    chassis.setPose(42, -67, 0);
    chassis.moveTo(42, -57, 250);
    intakeMotors.move_voltage(12000);
    chassis.turnTo(-53, -53, 250);
    chassis.moveTo(-20, -53, 250);
    intakeMotors.move_voltage(0);
    pros::delay(25);
    autonShoot();
    pros::delay(25);
    load();
    chassis.setPose(-20, -53, 90);
    chassis.moveTo(12, -53, 250);
    intakeMotors.move_voltage(12000);
    chassis.turnTo(12, -36, 250);
    chassis.moveTo(12, -36, 250);
    chassis.turnTo(-12, -12, 250);
    chassis.moveTo(-12, -12, 250);
    chassis.setPose(-12, -12, -45);
    chassis.turnTo(-53, -53, 250);
    chassis.moveTo(-18, -18, 250);
    intakeMotors.move_voltage(0);
    pros::delay(25);
    autonShoot();
    pros::delay(25);
    load();
    pros::delay(25);
    intakeMotors.move_voltage(12000);
    chassis.setPose(-18, -18, 45);
    chassis.moveTo(-12, -12, 250);
    chassis.turnTo(36, 12, 250);
    chassis.moveTo(-48, 24, 250, 125);
    chassis.setPose(-48, 24, 135);
    chassis.moveTo(-53, -17, 250);
    chassis.turnTo(-53, -53, 250);
    intakeMotors.move_voltage(0);
    pros::delay(25);
    autonShoot();
    pros::delay(25);
    load();
    chassis.setPose(-53, -17, 0);
    chassis.moveTo(-53, 39, 250);
    chassis.turnTo(-69, 39, 250);
    chassis.moveTo(-69, 39, 100);
    rollerMotor.move_relative(250, 200);
    pros::delay(300);
    chassis.setPose(-69, 39, 90);



    
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
void opcontrol() {
	
}
