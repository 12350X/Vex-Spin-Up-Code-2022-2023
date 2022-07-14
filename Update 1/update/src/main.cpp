/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\adams                                            */
/*    Created:      Wed Jul 13 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    2, 1            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <vex.h>
#include <button.h>
#include <utils.h>

using namespace vex;
using namespace utils;

typedef char *string;
button b, b2;
square x = {200, 0, 150, 50};

square y = {0, 0, 150, 50};

void Autonomous(void)
{
  Drivetrain.drive(forward);
}

void buttonFunction()
{
  Brain.Screen.print("clicked");
}
int CheckCollisions() {b.CheckCollisions(); return 0;}
int CheckCollisions2() {b2.CheckCollisions(); return 0;}
int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.drawImageFromFile("logo.png", 365, 120);
  b.setup(x, "Drivercontrol?", buttonFunction);
  b2.setup(y, "Autonomous?", buttonFunction);
  task check(CheckCollisions);
  task check2(CheckCollisions2);


  Autonomous();
  while(true) {
    // Allow other tasks to run
    this_thread::sleep_for(10);
  }
  return EXIT_SUCCESS;

}
