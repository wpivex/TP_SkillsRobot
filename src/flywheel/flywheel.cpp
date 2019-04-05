#include "flywheel.hpp"

// Ports
const int LEFT_FLYWHEEL = 6;
const int RIGHT_FLYWHEEL = 7;
const int INDEXER = -13;

// TODO: Get all these setpoints
const int FIRE_TRAVEL = 40;
const int FIRE_VEL = 20;

const int INTAKE_TRAVEL = 250;
const int INTAKE_VEL = 30;

Flywheel::Flywheel()
    : left_flywheel(LEFT_FLYWHEEL), // TODO: Get actual reversed info
      right_flywheel(RIGHT_FLYWHEEL, true),
      indexer(INDEXER)
{
  Flywheel::desiredVelocity = 0;
}

void Flywheel::flywheelTask(void *)
{
  left_flywheel.set_brake_mode(MOTOR_BRAKE_COAST);
  right_flywheel.set_brake_mode(MOTOR_BRAKE_COAST);

  left_flywheel.set_gearing(MOTOR_GEARSET_6);
  right_flywheel.set_gearing(MOTOR_GEARSET_6);

  while (true)
  {
    left_flywheel.move_velocity(desiredVelocity);
    right_flywheel.move_velocity(desiredVelocity);

    pros::delay(10);
  }
}

void Flywheel::setFlywheelRPM(double vel)
{
  desiredVelocity = vel;
}

void Flywheel::intake()
{
  indexer.move_relative(INTAKE_TRAVEL, INTAKE_VEL);
}

void Flywheel::fire()
{
  while (!((left_flywheel.get_actual_velocity() + VEL_MARGIN) > desiredVelocity || (right_flywheel.get_actual_velocity() + VEL_MARGIN) > desiredVelocity))
  {
    pros::delay(50);
  }
  indexer.move_relative(FIRE_TRAVEL, FIRE_VEL);
  pros::delay(200);
}

void Flywheel::fireForEffect()
{
  setFlywheelRPM(FIRST_SHOT_RPM);
  fire();
  setFlywheelRPM(SECOND_SHOT_RPM);
  fire();
  setFlywheelRPM(0);
}
