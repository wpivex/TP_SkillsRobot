#include "../../include/subsystems/arm.hpp"

Arm::Arm()
    : armController(AsyncControllerFactory::posPID(
          {LEFT_ARM, RIGHT_ARM},
          liftkP,
          liftkI,
          liftkD)),
      leftArm(LEFT_ARM),
      rightArm(RIGHT_ARM)
{
    leftArm.setGearing(AbstractMotor::gearset::red);
    rightArm.setGearing(AbstractMotor::gearset::red);
}
