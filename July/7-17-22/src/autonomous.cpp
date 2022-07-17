#include <button.h>
#include "autonomous.h"
#include "vex.h"

bool isLeft;


square leftSquare = 
{
  480 / 2 - 200,
   240 / 2,
   120,
   60
};
square rightSquare = 
{
  480 / 2 + 50,
   240 / 2,
   120,
   60
};
void start();
button l, r;
int left1()
{
    l.CheckCollisions();
    return 0;
}

int right1()
{
    r.CheckCollisions();
    return 0;
}

void leftButtonFunctionality()
{
  isLeft = true;
  l.setButtonDisabled(true);
  r.setButtonDisabled(true);
  l.clear();
  r.clear();
  start();
}

void rightButtonFunctionality()
{
  isLeft = false;
  l.setButtonDisabled(true);
  r.setButtonDisabled(true);
  l.clear();
  r.clear();
  start();
}

void autonomous::prompt()
{
  
  l.setup(leftSquare, (char *) "Left Side", leftButtonFunctionality);

  r.setup(rightSquare, (char *) "Right Side", rightButtonFunctionality);

  task check1(left1);
  task check2(right1);
}

void kill(thread current_thread)
{
  current_thread.interrupt();
}

void start()
{
  Brain.Screen.print("Inside of setup");


  if(!isLeft)
  {
    Brain.Screen.print("Right side selected...");
    return;
  }
  // else
  Brain.Screen.print("Left side selected...");
}