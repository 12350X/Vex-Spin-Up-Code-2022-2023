
#include "vex.h"

#include "button.h"

typedef char *string;
square s;
bool clicked = false;
bool isDisabled = false;
bool hasSender = false;
void (*functionpointer)(void);
void (*senderFunctionPointer)(char *);
char *text1;
string senderArgs;

bool checkCollsion(point p, square s)
{
    return p.x >= s.x && p.x <= s.x + s.w && p.y >= s.y && p.y <= s.y + s.h;
}

void button::setButtonDisabled(bool x)
{
  isDisabled = x;
}

void button::draw()
{
  Brain.Screen.drawRectangle(s.x, s.y, s.w, s.h);
  int tw = vexDisplayStringWidthGet(text1);
  int th = vexDisplayStringHeightGet(text1);
  int tl = s.x + (s.w / 2) - (tw / 2);
  int tt = s.y + (s.h / 2) - (th / 2);
  Brain.Screen.printAt(tl, tt, false, text1);
}

void button::destroy()
{
  clear();
  setButtonDisabled(true);
}

void button::clear()
{
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(s.x, s.y, s.w, s.h);
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(s.x, s.y, s.w, s.h);
  Brain.Screen.setPenColor(transparent);
  
}



void button::setup(int x, int y, int width, int height, string text, void (*ptr)(void))
{
    s = {x, y, width, height};
    text1 = text;
    functionpointer = ptr;
    return;
}
void button::setup(int x, int y, int width, int height, string text, void (*ptr)(char *), char *sender)
{
    s = {x, y, width, height};
    senderFunctionPointer = ptr;
    text1 = text;
    hasSender = true;
    senderArgs = sender;
    return;
}

void button::setup(square s, string text,  void (*ptr)(char *), char *sender) {button::setup(s.x, s.y, s.w, s.h, text, ptr, sender);}

void button::setup(square s, string text, void (*ptr)(void)) {button::setup(s.x, s.y, s.w, s.h, text, ptr);}
