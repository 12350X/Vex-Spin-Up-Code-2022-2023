
#include <autonomous.h>
#include <utils.h>
#include <gifclass.h>
#include <button.h>
#include <Menu.h>


// Changed vex/mkenv.mk line: 86 colum 130,131 to 17.
// Obviously to use newer version of C++ -std=gnu++17.
button b, b2, yes, no, powerSettings, back;
bool inMainMenu = true;
Menu currentMenu, mainMenu, autonomousMenu, driverMenu, powerMenu;
square x = {480-160, 50, 160, 50};

square y = {480-160, 125, 160, 50};

square power = {x.x - 165, x.y, x.w, x.h};
bool isinLowpowermode = false;

void handleAutonDriver(char *sender)
{
  Brain.Screen.print(sender);
  
  if(strcmp(sender, "Autonomous") == 0 && inMainMenu)
  {
    b.destroy();
    b2.destroy();
    currentMenu = autonomousMenu;
    Brain.Screen.clearScreen();
    printlnColored((char *)"Autonomous initialized", green);
    autonomous a;
    a.prompt();
  }
  else if(strcmp(sender, "Driver") == 0 && inMainMenu)
  {
    currentMenu = driverMenu;
    Brain.Screen.clearScreen();
    b.destroy();
    b2.destroy();
    printlnColored((char *)"Driver control active", green);
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
/*
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

*/
void powerSettingsButton();
void setupMainMenu()
{
  Brain.Screen.clearScreen();
  SDcardInstalled();

  imuInstalled();
  powerSettings.setup(power, (char *) "Power Settings", powerSettingsButton);
  b.setup(x, (char *) "Drivercontrol", handleAutonDriver, (char *) "Driver");
  b2.setup(y, (char *) "Autonomous", handleAutonDriver, (char *) "Autonomous");
}
void powerSettingsButton()
{

  //inMainMenu = false;
  back.draw();
  b.destroy();
  b2.destroy();
  powerSettings.destroy();
  currentMenu = powerMenu;
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(fontType::mono30);
  printAtColored(480 / 2 - 75, 20, false, "Power Settings.", yellow);
  Brain.Screen.setFont(fontType::mono20);
  //back.setup(430, 185, 50, 50, (char *) "back", setupMainMenu);
  //button buttons[1] = {back};
  /*
  Brain.Screen.drawLine(480 / 3, 240 / 2, 480 / 2, 240 / 2);
  int radius = 10;
  point middle = {480 / 3, 240 / 2};
  Brain.Screen.drawCircle(middle.x, middle.y, radius);
  point p = {Brain.Screen.xPosition(), Brain.Screen.yPosition()};
  */
}


bool update = true;
int updateMenu()
{
  while(update){
    currentMenu.Update();
    wait(20, msec);
  }
  return 0;
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  /*
  powerSettings.setup(power, (char *) "Power Settings", powerSettingsButton) ;
  b.setup(x, (char *) "Drivercontrol", handleAutonDriver, (char *) "Driver");
  b2.setup(y, (char *) "Autonomous", handleAutonDriver, (char *) "Autonomous");
  */

  mainMenu.addButton(power.x, power.y, power.w, power.h, (char *) "Power Settings", powerSettingsButton);
  powerMenu.addButton(430, 185, 50, 50, (char *) "back", setupMainMenu);
  back.clear();
  currentMenu = mainMenu;
  task check(updateMenu);
  Brain.Screen.drawLine(121, 0, 121, 240);
  SDcardInstalled();

  imuInstalled();
  //lowPowerModePrompt();

  vex::Gif gif("intro.gif", 0, 0 );
  
  while(true) {
    Brain.Screen.render();
  }
  update = false;
  return EXIT_SUCCESS;
}