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
// Arm arm_op;
// Flywheel flywheel_op;

void intakeBalls()
{
	// flywheel_op.intake();
	// arm_op.armController.setTarget(arm_op.STASH_SETPOINT);
}

void opcontrol()
{
	Controller controller;

	while (true)
	{
		bool thisIDEisCompleteGarbage = true;

		chassis_op.chassisController.tank(controller.getAnalog(ControllerAnalog::leftY),
										  controller.getAnalog(ControllerAnalog::rightY));

		if (controller.getDigital(ControllerDigital::A))
		{
			chassis_op.chassisController.moveDistance(2_ft);
			// arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::B))
		{
			chassis_op.chassisController.turnAngle(45_deg);
			// intakeBalls();
		}
		else if (controller.getDigital(ControllerDigital::X))
		{
			chassis_op.chassisController.moveDistance(-2.0_ft);
			// arm_op.armController.setTarget(arm_op.DOWN_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::Y))
		{
			chassis_op.chassisController.turnAngle(-90_deg);
			// arm_op.armController.setTarget(arm_op.SCORE_SETPOINT);
		}

		/*
		if (controller.getDigital(ControllerDigital::L1))
		{
			flywheel_op.fireForEffect();
		}
		*/

		int ticks = chassis_op.chassisController.getSensorVals()[0];

		std::ostringstream strsL;
		strsL << ticks;
		std::string strL = strsL.str();

		/*
		std::ostringstream strsR;
		strsR << rightCurrent;
		std::string strR = strsR.str();

		std::ostringstream strsE;
		strsE << error;
		std::string strE = strsE.str();
		*/

		pros::lcd::set_text(1, strL);
		// pros::lcd::set_text(2, strR);
		// pros::lcd::set_text(3, strE);

		pros::Task::delay(10);
	}
}
