// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2            
// Controller1          controller                    
// Inertial             inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2            
// Controller1          controller                    
// Inertial3            inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2            
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2            
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// Controller1          controller
// Inertial             inertial      3
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <autonomous.h>
#include <button.h>
#include <utils.h>

button b, b2, yes, no;

square x = {200, 10, 160, 50};

square y = {0, 10, 150, 50};

bool isinLowpowermode = false;

void drivercontrol() {
  Brain.Screen.clearScreen();
  printlnColored((char *)"Driver control active", green);
}

void auton() {
  b.setButtonDisabled(true);
  b2.setButtonDisabled(true);
  Brain.Screen.clearScreen();
  printlnColored((char *)"Autonomous initialized", green);
  autonomous a;
  a.prompt();
}

int CheckCollisions() {
  b.CheckCollisions();
  return 0;
}

int CheckCollisions2() {
  b2.CheckCollisions();
  return 0;
}

int checkyesclicked() {
  yes.CheckCollisions();
  return 0;
}

int checknoclicked() {
  no.CheckCollisions();
  return 0;
}

void lowpowermode() {
  isinLowpowermode = true;
  Drivetrain.setDriveVelocity(50, percentUnits::pct);

  yes.setButtonDisabled(true);
  no.setButtonDisabled(true);
  printAtColored(0, 240, true, (char *)"Low power mode activated", yellow);
  Brain.Screen.clearLine(6);
  no.destroy();
  yes.destroy();
}
void clearScreen() {
  no.setButtonDisabled(true);
  yes.setButtonDisabled(true);
  Brain.Screen.clearLine(6);
  no.destroy();
  yes.destroy();
  printAtColored(0, 240, true, (char *)"Low power mode deactive", red);
}

void SDcardInstalled() {
  Brain.Screen.setFont(fontType::mono12);
  if (Brain.SDcard.isInserted()) {
    printAtColored(375, 10, true, (char *) "SDcard: Installed!", green);
  } else {
    printAtColored(360, 10, true, (char *) "SDcard: Uninstalled!", red);
  }
  Brain.Screen.setFont(fontType::mono20);
}

void imuInstalled()
{
  Brain.Screen.setFont(fontType::mono12);
  if (Inertial.installed()) {
    printAtColored(375, 20, true, (char *) "Imu: Installed!", green);
  } else {
    printAtColored(375, 20, true, (char *) "Imu: Uninstalled!", red);
  }
  Brain.Screen.setFont(fontType::mono20);
}
void lowPowerModePrompt() {
  if (Brain.Battery.capacity() <
      50) { // IF the battery is less than 50% charged ask user if they want to
            // enter low power mode.

    printAtColored(0, 115, true, (char *) "Would you like to activate low power mode?", yellow);

    // Setting up the buttons.
    Brain.Screen.setFillColor(green);
    yes.setup(480 / 2 - 150, 272 / 2 + 10, 100, 50, (char *) "Yes.", lowpowermode);
    Brain.Screen.setFillColor(red);
    no.setup(480 / 2, 272 / 2 + 10, 100, 50, (char *) "No.", clearScreen);
    Brain.Screen.setFillColor(transparent);
    
    // Setting up the buttons.

    // Checking if the button got clicked.
    task check(checkyesclicked);
    task check1(checknoclicked);
  }
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  SDcardInstalled();

  imuInstalled();
  lowPowerModePrompt();

  Brain.Screen.drawImageFromFile("logo.png", 365,
                                 120); // Drawing GearGrinders logo from SDcard.

  // Asking user if they want to enter autonomous or drivercontrol.
  b.setup(x, (char *) "Drivercontrol", drivercontrol);
  b2.setup(y, (char *) "Autonomous", auton);

  // Checking if the buttons got clicked?
  task check(CheckCollisions);
  task check2(CheckCollisions2);

  while (true) {
    // Allow other tasks to run
    this_thread::sleep_for(10);
  }
  return EXIT_SUCCESS;
}