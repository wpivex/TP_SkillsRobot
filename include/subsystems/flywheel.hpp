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
  void stopFlywheel();
  void fireForEffect();
  Motor indexer;

private:
  Motor leftFlywheel;
  Motor rightFlywheel;

  static constexpr int INTAKE_TRAVEL = 350;
  static constexpr int INTAKE_VEL = 45;

  static constexpr int FIRE_VEL = 60;

  static constexpr int FIRE_VOLTAGE = 8350;

  static constexpr int LEFT_FLYWHEEL = 18;
  static constexpr int RIGHT_FLYWHEEL = -8;
  static constexpr int INDEXER = -13;
};

#endif
