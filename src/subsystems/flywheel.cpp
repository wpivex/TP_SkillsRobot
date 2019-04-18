#include "../../include/subsystems/flywheel.hpp"

Flywheel::Flywheel()
    : indexer(INDEXER),
      leftFlywheel(LEFT_FLYWHEEL),
      rightFlywheel(RIGHT_FLYWHEEL)
{
  leftFlywheel.setBrakeMode(AbstractMotor::brakeMode::coast);
  rightFlywheel.setBrakeMode(AbstractMotor::brakeMode::coast);
  indexer.setBrakeMode(AbstractMotor::brakeMode::brake);

  indexer.setGearing(AbstractMotor::gearset::green);
}

void Flywheel::intake()
{
  indexer.moveRelative(INTAKE_TRAVEL, INTAKE_VEL);
}

void Flywheel::startFlywheel()
{
  leftFlywheel.moveVoltage(FIRE_VOLTAGE);
  rightFlywheel.moveVoltage(FIRE_VOLTAGE);
}

void Flywheel::stopFlywheel()
{
  leftFlywheel.moveVoltage(0);
  rightFlywheel.moveVoltage(0);
}

void Flywheel::fireForEffect()
{
  indexer.moveVelocity(FIRE_VEL);
  pros::delay(1600);
  indexer.moveVelocity(0);
}
