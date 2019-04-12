#include "../../include/subsystems/drivebase.hpp"

Chassis::Chassis()
    : cap_button('C'),
      chassisController(
          ChassisControllerFactory::create(
              {FRONT_LEFT_DRIVE, BACK_LEFT_DRIVE},
              {FRONT_RIGHT_DRIVE, BACK_RIGHT_DRIVE},
              ADIEncoder('A', 'B', false),
              ADIEncoder('G', 'H', true),
              IterativePosPIDController::Gains{0.0004, 0.00000048, 0.0000000012},
              IterativePosPIDController::Gains{0.0001, 0.000001, 0.000000000012},
              IterativePosPIDController::Gains{0.0006, 0.00001, 0.00000000012},
              AbstractMotor::gearset::green,
              {RESOLUTION / ((WHEEL_DIAMETER).convert(meter) * 1_pi),
               RESOLUTION * (CHASSIS_WIDTH).convert(meter) / (WHEEL_DIAMETER).convert(meter) / 360}))
{
  chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);
}

void Chassis::driveIntoCap()
{
  while (!cap_button.isPressed())
  {
    chassisController.forward(10);
  }
}

void Chassis::ramWallBackwards(int duration)
{
  chassisController.forward(-10);
  pros::delay(duration);
  chassisController.stop();
}

void Chassis::ramWallForwards(int duration)
{
  chassisController.forward(10);
  pros::delay(duration);
  chassisController.stop();
}
