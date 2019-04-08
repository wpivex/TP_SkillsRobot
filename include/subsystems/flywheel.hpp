#ifndef FLYWHEEL_H_INCLUDED
#define FLYWHEEL_H_INCLUDED

#include "../../include/main.h"

using namespace okapi;

class Flywheel
{
public:
  Flywheel();

  void intake();
  void startFlywheel();
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
  static constexpr int FIRE_CURRENT = 1700;

  static constexpr int HIGH_FLAG_RPM = 145; // Int 145, PID 29, Blue 435
  static constexpr int MID_FLAG_RPM = 127;  // Int 124, PID 25, Blue 372

  static constexpr int LEFT_FLYWHEEL = 18;
  static constexpr int RIGHT_FLYWHEEL = -8;
  static constexpr int INDEXER = -13;
};

#endif
