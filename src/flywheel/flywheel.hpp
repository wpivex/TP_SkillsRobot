#ifndef FLYWHEEL_H_INCLUDED
#define FLYWHEEL_H_INCLUDED

#include "../../include/main.h"

// TODO: Get all these setpoints
const int VEL_MARGIN = 2;
const int FIRST_SHOT_RPM = 20;
const int SECOND_SHOT_RPM = 10;

class Flywheel
{
public:
  Flywheel();

  void flywheelTask(void *);
  void setFlywheelRPM(double vel);
  void intake();
  void fireForEffect();

private:
  pros::Motor left_flywheel;
  pros::Motor right_flywheel;
  pros::Motor indexer;
  double desiredVelocity;

  void fire();
};

#endif
