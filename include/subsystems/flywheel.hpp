#ifndef FLYWHEEL_H_INCLUDED
#define FLYWHEEL_H_INCLUDED

#include "../../include/main.h"

using namespace okapi;

class Flywheel
{
public:
  Flywheel();

  void intake();
  void fireForEffect();

private:
  AsyncVelIntegratedController flywheelController;
  Motor indexer;
  Motor leftFlywheel;
  Motor rightFlywheel;

  void fire();

  static constexpr int INTAKE_TRAVEL = 250;
  static constexpr int INTAKE_VEL = 30;
  static constexpr int FIRE_VEL = 60;

  // TODO: Get these setpoints
  const int FIRST_SHOT_RPM = 20;
  const int SECOND_SHOT_RPM = 10;
  const int HOLD_RPM = 10;
  const int FIRE_CURRENT = 10;

  static constexpr int LEFT_FLYWHEEL = 6;
  static constexpr int RIGHT_FLYWHEEL = -7;
  static constexpr int INDEXER = -13;
};

#endif
