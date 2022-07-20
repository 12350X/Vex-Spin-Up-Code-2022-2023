
#include <autonomous.h>
#include <utils.h>
#include <buttonManager.h>

// Changed vex/mkenv.mk line: 86 colum 130,131 to 17.
// Obiously to use newer version of C++ -std=gnu++17.
button b, b2, yes, no;


square x = {200, 10, 160, 50};

square y = {0, 10, 150, 50};

bool isinLowpowermode = false;

void handleAutonDriver(char *sender)
{
  Brain.Screen.print(sender);
  if(strcmp(sender, "Autonomous") == 0)
  {
    Brain.Screen.clearScreen();
    printlnColored((char *)"Driver control active", green);
  }
  else if(strcmp(sender, "Driver") == 0)
  {
    b.destroy();
    b2.destroy();
    Brain.Screen.clearScreen();
    printlnColored((char *)"Autonomous initialized", green);
    autonomous a;
    a.prompt();
  }
  else
  {
    Brain.Screen.print("unknown");
  }
}
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
    return;
  }
  yes.destroy();
  no.destroy();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  buttonManager bm;

  SDcardInstalled();

  imuInstalled();

  b.setup(x, (char *) "Drivercontrol", handleAutonDriver, (char *) "Driver");
  b2.setup(y, (char *) "Autonomous", handleAutonDriver, (char *) "Autonomous");
  button prototype;

  lowPowerModePrompt();

  button buttons[5] = {b, b2, yes, no, prototype};
  bm.addButtons(buttons, sizeof(buttons) / sizeof(button));

  Brain.Screen.drawImageFromFile("logo.png", 365,
                                 120); // Drawing GearGrinders logo from SDcard.

  // Asking user if they want to enter autonomous or drivercontrol.
  

  while (true) {
    // Allow other tasks to run
    this_thread::sleep_for(10);
  }
  return EXIT_SUCCESS;
}