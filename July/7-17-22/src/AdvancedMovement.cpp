#include <vex.h>
#include <AdvancedMovement.h>
#include <utils.h>

bool isInstalled;
motor_group motors(LeftDriveSmart, RightDriveSmart);
void AdvancedMovement::setup() // YOU NEED TO CALL THIS BEFORE USING!!!!!!
{
  Inertial.calibrate();
  isInstalled = Inertial.installed();
  if(!isInstalled)
    printlnColored((char *) "Inertial not installed", red);
}

void AdvancedMovement::turnPID(int angle)
{ 
  double kP = 0;
  double kI= 0;
  double kD = 0;
  int integral = 0;
  int error = 0;
  int prevError = 0;
  int power = 0;
  int derivative = 0;

  while (abs(error) > 0.5)
  {
    error = angle - Inertial.rotation(deg);
    integral = integral + error;
    if (error == 0 || error > angle)
      integral = 0;
    if (error > 360)
      integral = 0;
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    LeftDriveSmart.spin(fwd, power, volt);
    RightDriveSmart.spin(fwd, -1 * power, volt);
    wait(15, msec);
  }
}