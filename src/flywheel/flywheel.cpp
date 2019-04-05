#include "flywheel.hpp"

Flywheel::Flywheel()
    : flywheelController(AsyncControllerFactory::velIntegrated(
          {LEFT_FLYWHEEL, RIGHT_FLYWHEEL})),
      indexer(INDEXER),
      leftFlywheel(LEFT_FLYWHEEL),
      rightFlywheel(RIGHT_FLYWHEEL)
{
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

void Flywheel::fireForEffect()
{
  flywheelController.setTarget(FIRST_SHOT_RPM);
  fire();
  flywheelController.setTarget(SECOND_SHOT_RPM);
  fire();
  flywheelController.setTarget(HOLD_RPM);
}
