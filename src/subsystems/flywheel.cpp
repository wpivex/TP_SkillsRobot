#include "../../include/subsystems/flywheel.hpp"

Flywheel::Flywheel()
    : flywheelController(AsyncControllerFactory::velIntegrated(
          {LEFT_FLYWHEEL, RIGHT_FLYWHEEL})),
      indexer(INDEXER),
      leftFlywheel(LEFT_FLYWHEEL),
      rightFlywheel(RIGHT_FLYWHEEL)
{
  leftFlywheel.setBrakeMode(AbstractMotor::brakeMode::coast);
  rightFlywheel.setBrakeMode(AbstractMotor::brakeMode::coast);
  indexer.setBrakeMode(AbstractMotor::brakeMode::brake);

  indexer.setGearing(AbstractMotor::gearset::green);
}

void Flywheel::fire()
{
  flywheelController.waitUntilSettled();
  do
  {
    indexer.moveVelocity(FIRE_VEL);
  } while (leftFlywheel.get_current_draw() < FIRE_CURRENT || rightFlywheel.get_current_draw() < FIRE_CURRENT);
  indexer.moveVelocity(0);
}

void Flywheel::intake()
{
  indexer.moveRelative(INTAKE_TRAVEL, INTAKE_VEL);
}

void Flywheel::startFlywheel()
{
  flywheelController.setTarget(MID_FLAG_RPM);
}

void Flywheel::fireForEffect()
{
  flywheelController.setTarget(MID_FLAG_RPM);
  fire();
  flywheelController.setTarget(HIGH_FLAG_RPM);
  fire();
  flywheelController.setTarget(MID_FLAG_RPM);
}
