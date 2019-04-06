#include "../include/main.h"

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

Chassis chassis_op;
Arm arm_op;
Flywheel flywheel_op;

void intakeBalls()
{
	flywheel_op.intake();
	arm_op.armController.setTarget(arm_op.STASH_SETPOINT);
}

void opcontrol()
{
	Controller controller;

	while (true)
	{
		// bool thisIDEisCompleteGarbage = true;

		chassis_op.chassisController.tank(controller.getAnalog(ControllerAnalog::leftY),
										  controller.getAnalog(ControllerAnalog::rightY));

		/*
		if (controller.getDigital(ControllerDigital::A))
		{
			arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::B))
		{
			intakeBalls();
		}
		else if (controller.getDigital(ControllerDigital::X))
		{
			arm_op.armController.setTarget(arm_op.DOWN_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::Y))
		{
			arm_op.armController.setTarget(arm_op.SCORE_SETPOINT);
		}
		*/

		if (controller.getDigital(ControllerDigital::L1))
		{
			flywheel_op.flywheelController.setTarget(100);
		}
		else if (controller.getDigital(ControllerDigital::L2))
		{
			flywheel_op.flywheelController.setTarget(50);
		}
		else if (controller.getDigital(ControllerDigital::R1))
		{
			flywheel_op.flywheelController.setTarget(0);
		}

		/*int leftCurrent = flywheel_op.leftFlywheel.getCurrentDraw();
		int rightCurrent = flywheel_op.leftFlywheel.getCurrentDraw();

		std::ostringstream strsL;
		strsL << leftCurrent;
		std::string strL = strsL.str();

		std::ostringstream strsR;
		strsR << rightCurrent;
		std::string strR = strsR.str();

		pros::lcd::set_text(1, strL);
		pros::lcd::set_text(2, strR);*/

		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		pros::Task::delay(10);
	}
}
