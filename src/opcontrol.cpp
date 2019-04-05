#include "arm/arm.hpp"
#include "drivebase/drivebase.hpp"
#include "flywheel/flywheel.hpp"

#include <sstream>

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

using namespace okapi;

Controller controller;

Chassis chassis;
Arm arm;
Flywheel flywheel;

void intakeBalls()
{
	flywheel.intake();
	arm.armController.setTarget(arm.STASH_SETPOINT);
}

void opcontrol()
{

	while (true)
	{
		//bool thisIDEisCompleteGarbage = true;

		// Tank drive with left and right sticks
		chassis.chassisController.tank(controller.getAnalog(ControllerAnalog::leftY),
									   controller.getAnalog(ControllerAnalog::rightY));

		if (controller.getDigital(ControllerDigital::A))
		{
			arm.armController.setTarget(arm.SECURE_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::B))
		{
			intakeBalls();
		}
		else if (controller.getDigital(ControllerDigital::X))
		{
			arm.armController.setTarget(arm.DOWN_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::Y))
		{
			arm.armController.setTarget(arm.SCORE_SETPOINT);
		}

		/*
		auto ticks = test_left.get_raw_position(time);

		std::ostringstream strs;
		strs << ticks;
		std::string str = strs.str();
*/
		//pros::lcd::set_text(1, str);

		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		pros::Task::delay(10);
	}
}
