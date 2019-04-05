#include "arm.hpp"

Arm::Arm()
    : armController(AsyncControllerFactory::posPID(
          {LEFT_ARM, RIGHT_ARM},
          liftkP,
          liftkI,
          liftkD))
{
}
