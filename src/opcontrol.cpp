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

void scoreCap()
{
	arm_op.armController.setTarget(arm_op.SCORE_SETPOINT);
	chassis_op.ramWallForwards(500);
	pros::delay(500);
	chassis_op.chassisController.moveDistance(-1_ft);
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
			arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
			pros::delay(2000);
			intakeBalls();
			pros::delay(2000);
			scoreCap();

			/* FIrst bit of routine. Works, but needs way to avoid angle PID
			pros::delay(500);
			chassis_op.driveIntoCap();
			chassis_op.chassisController.stop();
			pros::delay(250);
			arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
			pros::delay(500);
			chassis_op.chassisController.moveDistance(2.1_ft);
			chassis_op.chassisController.turnAngle(45_deg);
			intakeBalls();
			chassis_op.chassisController.moveDistance(4.95_ft);
			chassis_op.chassisController.turnAngle(-90_deg);
			*/
		}
		else if (controller.getDigital(ControllerDigital::B))
		{
			arm_op.armController.setTarget(arm_op.STASH_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::X))
		{
			arm_op.armController.setTarget(arm_op.STASH_SETPOINT);
		}
		else if (controller.getDigital(ControllerDigital::Y))
		{
			arm_op.armController.setTarget(arm_op.STASH_SETPOINT);
		}

		pros::Task::delay(10);
	}
}
