#include "../../include/subsystems/drivebase.hpp"

Chassis::Chassis()
    : cap_button('C'),
      pole_ultrasonic('E', 'F'),
      chassisController(
          ChassisControllerFactory::create(
              {FRONT_LEFT_DRIVE, BACK_LEFT_DRIVE},
              {FRONT_RIGHT_DRIVE, BACK_RIGHT_DRIVE},
              ADIEncoder('A', 'B', false),
              ADIEncoder('G', 'H', true),
              IterativePosPIDController::Gains{0.00045, 0.0000007, 0.0000000012},
              IterativePosPIDController::Gains{0.0001, 0.0001, 0.0000000012},
              IterativePosPIDController::Gains{0.00069, 0.0001, 0.0000012},
              AbstractMotor::gearset::green,
              {RESOLUTION / ((WHEEL_DIAMETER).convert(meter) * 1_pi),
               RESOLUTION * (CHASSIS_WIDTH).convert(meter) / (WHEEL_DIAMETER).convert(meter) / 360}))
{
  chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

  initializer_list<Motor> leftDriveMotors{Motor(FRONT_LEFT_DRIVE), Motor(BACK_LEFT_DRIVE)};
  initializer_list<Motor> rightDriveMotors{Motor(FRONT_RIGHT_DRIVE), Motor(BACK_RIGHT_DRIVE)};
  auto driveLeft = make_shared<MotorGroup>(leftDriveMotors);
  auto driveRight = make_shared<MotorGroup>(rightDriveMotors);
  auto leftEnc = make_shared<ADIEncoder>('A', 'B', false);
  auto rightEnc = make_shared<ADIEncoder>('G', 'H', true);
  auto scales = ChassisScales({RESOLUTION / ((WHEEL_DIAMETER).convert(meter) * 1_pi),
                               RESOLUTION * (CHASSIS_WIDTH).convert(meter) / (WHEEL_DIAMETER).convert(meter) / 360});

  experimentalChassisController = make_shared<ChassisControllerPID>(
      TimeUtilFactory::create(),
      make_shared<SkidSteerModel>(driveLeft, driveRight, leftEnc, rightEnc, 200, 12000),
      make_unique<IterativePosPIDController>(0.00045, 0.0000007, 0.0000000012, 0,
                                             TimeUtilFactory::withSettledUtilParams(100, 25, 250_ms), make_unique<PassthroughFilter>()),
      make_unique<IterativePosPIDController>(0.000000000000001, 0, 0, 0,
                                             TimeUtilFactory::withSettledUtilParams(1000, 100, 0_ms), make_unique<PassthroughFilter>()),
      make_unique<IterativePosPIDController>(0.00065, 0.001, 0.00000000012, 0,
                                             TimeUtilFactory::create(), make_unique<PassthroughFilter>()),
      AbstractMotor::gearset::green,
      scales);

  experimentalChassisController->startThread();
  experimentalChassisController->setBrakeMode(AbstractMotor::brakeMode::brake);
}

void Chassis::driveIntoCap()
{
  while (!cap_button.isPressed())
  {
    chassisController.forward(-0.5);
  }
  chassisController.stop();
}

void Chassis::ramWallBackwards(int duration)
{
  chassisController.forward(-2.00);
  pros::delay(duration);
  chassisController.stop();
}

void Chassis::ramWallForwards(int duration)
{
  chassisController.forward(0.5);
  pros::delay(duration);
  chassisController.stop();
}

void Chassis::driveIntoPole(bool isForward)
{
  double spd = 0.5;
  double us = -1;
  if (!isForward)
  {
    spd = -spd;
  }
  while (!(us < 275 && us > 10))
  {
    chassisController.forward(spd);
    us = pole_ultrasonic.get_value();
    pros::delay(10);
  }

  chassisController.stop();
}