#include "../../include/subsystems/drivebase.hpp"

Chassis::Chassis()
    : cap_button('C'),
      chassisController(
          ChassisControllerFactory::create(
              {FRONT_LEFT_DRIVE, BACK_LEFT_DRIVE},
              {FRONT_RIGHT_DRIVE, BACK_RIGHT_DRIVE},
              ADIEncoder('A', 'B', false),
              ADIEncoder('G', 'H', true),
              IterativePosPIDController::Gains{0.0035, 0.0, 0.000003}, // TODO: Get these PID Values.
              IterativePosPIDController::Gains{0.0, 0.0, 0.0},
              IterativePosPIDController::Gains{0.004, 0.0, 0.00000003},
              AbstractMotor::gearset::green,
              {WHEEL_DIAMETER, CHASSIS_WIDTH}) // TODO: Apply scaling with the lit encoders
      )
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
