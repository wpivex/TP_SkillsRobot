#include "drivebase/drivebase.hpp"
#include "flywheel/flywheel.hpp"
#include "arm/arm.hpp"

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

Flywheel flywheel;
Arm arm;
Chassis chassis;

void initializeTasks()
{
    // pros::Task flywheel_task(flywheel.flywheelTask);
}

void scoreCap()
{
    arm.armController.setTarget(arm.SCORE_SETPOINT);
    pros::delay(200);
    chassis.chassisController.moveDistance(0.75_ft);
    arm.armController.setTarget(arm.DOWN_SETPOINT);
}

void intakeBalls()
{
    flywheel.intake();
    arm.armController.setTarget(arm.STASH_SETPOINT);
}

void autonomous()
{
    // Initialize
    initializeTasks();

    // STAGE ONE
    // Step
    chassis.chassisController.moveDistance(1_m);
    chassis.driveIntoCap();

    // Step
    arm.armController.setTarget(arm.SECURE_SETPOINT);
    pros::delay(50);
    chassis.chassisController.moveDistance(-1_m);

    // Step
    chassis.chassisController.turnAngle(-45_deg);

    // Step
    chassis.chassisController.moveDistanceAsync(-7_ft);
    pros::delay(200);
    arm.armController.setTarget(arm.STASH_SETPOINT);
    arm.armController.waitUntilSettled();
    chassis.chassisController.waitUntilSettled();

    // Step
    chassis.chassisController.turnAngle(90_deg);

    // Step
    chassis.ramWallBackwards(200);

    // Step
    scoreCap();

    // Step
    flywheel.setFlywheelRPM(FIRST_SHOT_RPM);
    chassis.chassisController.moveDistance(0.5_ft);

    // Step
    chassis.chassisController.turnAngle(90_deg);

    // Step
    chassis.ramWallForwards(200);

    // Step
    flywheel.fireForEffect();

    // STAGE TWO
    // Step
    chassis.chassisController.moveDistance(-0.5_ft);

    // Step
    chassis.chassisController.turnAngle(-45_deg);

    // Step
    chassis.chassisController.moveDistance(2_ft);
    chassis.driveIntoCap();

    // Step
    arm.armController.setTarget(arm.STASH_SETPOINT);
    chassis.chassisController.moveDistanceAsync(-3_ft);
    arm.armController.waitUntilSettled();
    chassis.chassisController.waitUntilSettled();

    // Step
    chassis.chassisController.turnAngle(-45_deg);

    // TODO: This might be able to be a helper. We'll see.
    // Step
    chassis.ramWallBackwards(200);

    // Step
    scoreCap();

    // Step
    flywheel.setFlywheelRPM(FIRST_SHOT_RPM);
    chassis.chassisController.moveDistance(0.5_ft);

    // Step
    chassis.chassisController.turnAngle(90_deg);
}
