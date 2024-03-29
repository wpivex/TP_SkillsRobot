#ifndef DRIVEBASE_H_INCLUDED
#define DRIVEBASE_H_INCLUDED

#include "../../include/main.h"

using namespace okapi;
using namespace std;

class Chassis
{
public:
  Chassis();
  ChassisControllerPID chassisController;
  shared_ptr<ChassisControllerPID> experimentalChassisController;

  void driveIntoCap();
  void driveIntoPole(bool isForward);
  void ramWallBackwards(int duration);
  void ramWallForwards(int duration);

private:
  ADIButton cap_button;
  pros::ADIUltrasonic pole_ultrasonic;

  static constexpr int FRONT_LEFT_DRIVE = 10;
  static constexpr int BACK_LEFT_DRIVE = -2;
  static constexpr int FRONT_RIGHT_DRIVE = 3;
  static constexpr int BACK_RIGHT_DRIVE = -19;

  static constexpr auto WHEEL_DIAMETER = 3.25_in;
  static constexpr auto CHASSIS_WIDTH = 6.66_in;
  static constexpr auto RESOLUTION = 2048.0;
};

#endif
