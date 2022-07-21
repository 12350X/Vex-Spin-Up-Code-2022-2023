#include <button.h>
#include "autonomous.h"
#include "vex.h"
#include <AdvancedMovement.h>
#include <utils.h>
bool isLeft, inTestMode = false;

competition c;
square leftSquare = 
{
  480 / 2 - 200,
   240 / 2 - 30,
   120,
   60
};
square rightSquare = 
{
  480 / 2 + 50,
  240 / 2 - 30,
  120,
  60
};

square stest = 
{
    
  165,
  240 / 2 + 50,
  120,
  60
};

button l, r, test;

void start();

AdvancedMovement robot;



void leftButtonFunctionality()
{
  isLeft = true;
  l.destroy();
  r.destroy();
  test.destroy();
  start();
}

void rightButtonFunctionality()
{
  isLeft = false;
  l.destroy();
  r.destroy();
  test.destroy();
  start();
}

void testMode()
{
  l.destroy();
  r.destroy();
  test.destroy();
  inTestMode = true;
  start();
}
void autonomous::prompt()
{
  robot.setup();

  l.setup(leftSquare, (char *) "Left Side", leftButtonFunctionality);

  r.setup(rightSquare, (char *) "Right Side", rightButtonFunctionality);

  test.setup(stest, (char *) "test", testMode);
  c.autonomous(start);
}

void kill(thread current_thread)
{
  Drivetrain.stop(brake);
  current_thread.interrupt(); // You are meant to pass in the task thread you started autonomous on.
}

void start()
{
  
  printlnColored((char *) "Autonomous Started :)", green);

  if(inTestMode) // Test Mode.
  {
    // To be implemented.
    return;
  }
  if(!isLeft) // Right side.
  {
    // To be implemented.
    return;
  }
  // Left side.
  // To be implemented.
}

