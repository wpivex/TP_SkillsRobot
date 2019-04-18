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

void scoreCap(QLength pullOut)
{
	chassis_op.ramWallForwards(750);
	arm_op.armController.setTarget(arm_op.SCORE_SETPOINT);
	pros::delay(1100);
	chassis_op.chassisController.moveDistance(-pullOut);
}

void scoreCapQuick(QLength pullOut)
{
	arm_op.armController.setTarget(arm_op.SCORE_SETPOINT);
	chassis_op.ramWallForwards(500);
	pros::delay(500);
	chassis_op.chassisController.moveDistance(-pullOut);
}

void opcontrol()
{
	Controller controller;

	while (true)
	{
		chassis_op.chassisController.tank(controller.getAnalog(ControllerAnalog::leftY),
										  controller.getAnalog(ControllerAnalog::rightY));

		if (controller.getDigital(ControllerDigital::A))
		{

			/* FIrst bit of routine. Works!! */
			pros::delay(200);
			chassis_op.driveIntoCap();
			arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
			pros::delay(500);
			chassis_op.experimentalChassisController.get()->moveDistance(1.9_ft);
			flywheel_op.startFlywheel();
			chassis_op.chassisController.turnAngle(-42_deg);
			intakeBalls();
			chassis_op.experimentalChassisController.get()->moveDistance(5.08_ft);
			chassis_op.chassisController.turnAngle(84_deg);
			scoreCap(0.75_ft);
			arm_op.armController.setTarget(arm_op.DOWN_SETPOINT);
			chassis_op.chassisController.turnAngle(82_deg);
			chassis_op.ramWallBackwards(700);
			flywheel_op.fireForEffect();
			/* ----------------------------- */

			/* Second part of routine. In Progress */
			chassis_op.experimentalChassisController.get()->moveDistance(0.3_ft);
			chassis_op.chassisController.turnAngle(-81.5_deg);
			chassis_op.experimentalChassisController.get()->moveDistance(-1.8_ft);
			chassis_op.driveIntoCap();
			arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
			pros::delay(500);
			chassis_op.experimentalChassisController.get()->moveDistanceAsync(1.37_ft);
			pros::delay(1000);
			intakeBalls();
			chassis_op.experimentalChassisController.get()->waitUntilSettled();
			arm_op.armController.waitUntilSettled();
			chassis_op.chassisController.turnAngle(-84.5_deg);
			scoreCapQuick(0.5_ft);
			arm_op.armController.setTarget(arm_op.DOWN_SETPOINT);
			chassis_op.chassisController.turnAngle(-83_deg);
			chassis_op.experimentalChassisController.get()->moveDistance(2.25_ft);
			chassis_op.chassisController.turnAngle(-83_deg);
			chassis_op.ramWallBackwards(300);
			flywheel_op.fireForEffect();
			/* ----------------------------------- */

			/* Third part of routine. In Progress */
			chassis_op.experimentalChassisController.get()->moveDistance(0.3_ft);
			chassis_op.chassisController.turnAngle(-77.5_deg);
			chassis_op.driveIntoCap();
			arm_op.armController.setTarget(arm_op.SECURE_SETPOINT);
			pros::delay(500);
			chassis_op.chassisController.turnAngle(-5_deg);
			chassis_op.experimentalChassisController.get()->moveDistanceAsync(-2.52_ft);
			pros::delay(1000);
			intakeBalls();
			chassis_op.experimentalChassisController.get()->waitUntilSettled();
			arm_op.armController.waitUntilSettled();
			chassis_op.chassisController.turnAngle(-84.5_deg);
			scoreCapQuick(0.5_ft);
			arm_op.armController.setTarget(arm_op.DOWN_SETPOINT);
			chassis_op.chassisController.turnAngle(-83_deg);
			chassis_op.experimentalChassisController.get()->moveDistance(0.8_ft);
			chassis_op.chassisController.turnAngle(-83_deg);
			chassis_op.ramWallBackwards(500);
			flywheel_op.fireForEffect();
			/* ---------------------------------- */
		}

		pros::Task::delay(10);
	}
}
