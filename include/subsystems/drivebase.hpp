#ifndef DRIVEBASE_H_INCLUDED
#define DRIVEBASE_H_INCLUDED

#include "../../include/main.h"

using namespace okapi;

class Chassis
{
public:
  Chassis();
  ChassisControllerPID chassisController;

  void driveIntoCap();
  void ramWallBackwards(int duration);
  void ramWallForwards(int duration);

private:
  ADIButton cap_button;

  static constexpr int FRONT_LEFT_DRIVE = 10;
  static constexpr int BACK_LEFT_DRIVE = -2;
  static constexpr int FRONT_RIGHT_DRIVE = 3;
  static constexpr int BACK_RIGHT_DRIVE = -20;

  static constexpr auto WHEEL_DIAMETER = 3.25_in;
  static constexpr auto CHASSIS_WIDTH = 6.75_in;
  static constexpr auto SCALE_ENCODER = 5.68888;
};

#endif
