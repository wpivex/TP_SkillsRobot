#include "../../include/subsystems/drivebase.hpp"

bool test = true;

Chassis::Chassis()
    : cap_button('C'),
      chassisController(
          ChassisControllerFactory::create(
              {FRONT_LEFT_DRIVE, BACK_LEFT_DRIVE},
              {FRONT_RIGHT_DRIVE, BACK_RIGHT_DRIVE},
              ADIEncoder('A', 'B', false),
              ADIEncoder('G', 'H', true),
              IterativePosPIDController::Gains{0.00045, 0.0000007, 0.0000000012},
              IterativePosPIDController::Gains{0.0001, 0.0001, 0.0000000012},
              IterativePosPIDController::Gains{0.00065, 0.0001, 0.00000000012},
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
    chassisController.forward(-0.5);
  }
}

void Chassis::ramWallBackwards(int duration)
{
  chassisController.forward(-0.5);
  pros::delay(duration);
  chassisController.stop();
}

void Chassis::ramWallForwards(int duration)
{
  chassisController.forward(0.5);
  pros::delay(duration);
  chassisController.stop();
}
