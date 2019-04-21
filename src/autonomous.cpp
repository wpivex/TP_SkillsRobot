#include "../include/main.h"

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

Chassis chassis_auto;
Arm arm_auto;
Flywheel flywheel_auto;

void intakeBallsAuto()
{
    flywheel_auto.intake();
    arm_auto.armController.setTarget(arm_auto.STASH_SETPOINT);
}

void scoreCapAuto(QLength pullOut)
{
    chassis_auto.ramWallForwards(1000);
    arm_auto.armController.setTarget(arm_auto.SCORE_SETPOINT);
    pros::delay(1100);
    chassis_auto.chassisController.moveDistance(-pullOut);
}

void scoreCapQuickAuto(QLength pullOut)
{
    arm_auto.armController.setTarget(arm_auto.SCORE_SETPOINT);
    chassis_auto.ramWallForwards(500);
    pros::delay(500);
    chassis_auto.chassisController.moveDistance(-pullOut);
}

void autonomous()
{
    /* FIrst bit of routine. Works!! */
    chassis_auto.driveIntoCap();
    arm_auto.armController.setTarget(arm_auto.SECURE_SETPOINT);
    pros::delay(500);
    chassis_auto.experimentalChassisController.get()->moveDistance(1.7_ft);
    flywheel_auto.startFlywheel();
    chassis_auto.chassisController.turnAngle(-43.75_deg);
    intakeBallsAuto();
    chassis_auto.experimentalChassisController.get()->moveDistance(5.2_ft);
    chassis_auto.chassisController.turnAngle(84_deg);
    scoreCapAuto(0.875_ft);
    arm_auto.armController.setTarget(arm_auto.DOWN_SETPOINT);
    chassis_auto.chassisController.turnAngle(82_deg);
    chassis_auto.ramWallBackwards(1200);
    flywheel_auto.fireForEffect();
    /* ----------------------------- */

    /* Second part of routine. Works!! */
    chassis_auto.experimentalChassisController.get()->moveDistance(0.3_ft);
    chassis_auto.chassisController.turnAngle(-81.5_deg);
    chassis_auto.experimentalChassisController.get()->moveDistance(-1.8_ft);
    chassis_auto.driveIntoCap();
    arm_auto.armController.setTarget(arm_auto.SECURE_SETPOINT);
    pros::delay(1000);
    intakeBallsAuto();
    chassis_auto.driveIntoPole(true);
    arm_auto.armController.waitUntilSettled();
    pros::delay(1000);
    chassis_auto.experimentalChassisController.get()->moveDistance(0.28_ft);
    chassis_auto.chassisController.turnAngle(-85.0_deg);
    scoreCapQuickAuto(0.5_ft);
    arm_auto.armController.setTarget(arm_auto.DOWN_SETPOINT);
    chassis_auto.chassisController.turnAngle(-83_deg);
    chassis_auto.experimentalChassisController.get()->moveDistance(2.4_ft);
    chassis_auto.chassisController.turnAngle(-83_deg);
    chassis_auto.ramWallBackwards(300);
    flywheel_auto.fireForEffect();
    /* ------------------------------- */

    /* Third part of routine. Works!! */
    chassis_auto.experimentalChassisController.get()->moveDistance(0.3_ft);
    chassis_auto.chassisController.turnAngle(-77.5_deg);
    chassis_auto.driveIntoCap();
    arm_auto.armController.setTarget(arm_auto.SECURE_SETPOINT);
    pros::delay(500);
    intakeBallsAuto();
    chassis_auto.chassisController.turnAngle(-5_deg);
    chassis_auto.driveIntoPole(false);
    arm_auto.armController.waitUntilSettled();
    pros::delay(1000);
    chassis_auto.experimentalChassisController.get()->moveDistance(0.167_ft);
    chassis_auto.chassisController.turnAngle(-83.5_deg);
    scoreCapQuickAuto(0.5_ft);
    arm_auto.armController.setTarget(arm_auto.DOWN_SETPOINT);
    chassis_auto.chassisController.turnAngle(-83_deg);
    chassis_auto.experimentalChassisController.get()->moveDistance(0.8_ft);
    chassis_auto.chassisController.turnAngle(-83_deg);
    chassis_auto.ramWallBackwards(500);
    flywheel_auto.fireForEffect();
    /* ------------------------------ */

    /* Fourth part of routine. Works!! */
    chassis_auto.experimentalChassisController.get()->moveDistance(2.5_ft);
    chassis_auto.chassisController.turnAngle(20_deg);
    chassis_auto.experimentalChassisController.get()->moveDistance(1.7_ft);
    chassis_auto.chassisController.turnAngle(-83.5_deg - 20_deg);
    chassis_auto.experimentalChassisController.get()->moveDistance(3.5_ft);
    /* ------------------------------- */
}
