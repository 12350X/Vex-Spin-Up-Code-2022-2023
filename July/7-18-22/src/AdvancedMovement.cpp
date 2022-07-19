#include <vex.h>
#include <AdvancedMovement.h>
#include <utils.h>

bool isInstalled;

void AdvancedMovement::setup() // YOU NEED TO CALL THIS BEFORE USING!!!!!!
{
  Inertial.calibrate();
  isInstalled = Inertial.installed();
  if(!isInstalled)
    printlnColored((char *) "Inertial not installed", red);
}

void AdvancedMovement::turn(turnType dir, double speed, double angle)
{
  if (!isInstalled) // FAILSAFE if the inertial sensor is not installed the code wont work properly, so this prevents that.
  {
    Drivetrain.turnFor(dir, angle, degrees);
    return;
  }
  if (dir != right)
  {
    while(Inertial.rotation(degrees) < angle && isInstalled)
    {
      Drivetrain.turn(dir, speed, rpm);
      wait(5, msec);
    }
    Drivetrain.stop(hold);
    return;
  }

  while(Inertial.rotation(degrees) < angle && isInstalled)
  {
    Drivetrain.turn(dir, speed, rpm);
    wait(5, msec);
  }
  Drivetrain.stop(hold); 
}
