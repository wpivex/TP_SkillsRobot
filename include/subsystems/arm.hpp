#ifndef ARM_H_INCLUDED
#define ARM_H_INCLUDED

#include "../../include/main.h"

using namespace okapi;

class Arm
{
public:
  Arm();
  AsyncPosPIDController armController;

  static constexpr int DOWN_SETPOINT = 0;
  static constexpr int SECURE_SETPOINT = 130;
  static constexpr int STASH_SETPOINT = 210;
  static constexpr int SCORE_SETPOINT = 375;


  Motor leftArm;
  Motor rightArm;
private:
  static constexpr int LEFT_ARM = -11;
  static constexpr int RIGHT_ARM = 6;

  static constexpr double liftkP = 0.00200;
  static constexpr double liftkI = 0.000001;
  static constexpr double liftkD = 0.00019;
};

#endif
