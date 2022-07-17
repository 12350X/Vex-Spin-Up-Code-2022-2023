#include <utils.h>
#include <vex.h>

using namespace vex;


void printlnColored(string args, color c)
{
  Brain.Screen.setPenColor(c);
  Brain.Screen.print(args);
  Brain.Screen.newLine();
  Brain.Screen.setPenColor(white);
}

void printColored(string args, color c)
{
  Brain.Screen.setPenColor(c);
  Brain.Screen.print(args);
  Brain.Screen.setPenColor(white);
}

void printAtColored(int x, int y, bool opaque, string args, color c)
{
  Brain.Screen.setPenColor(c);
  Brain.Screen.printAt(x, y, opaque, args);
  Brain.Screen.setPenColor(white);
}