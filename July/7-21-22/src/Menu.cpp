
#include <button.h>
#include <vector>
#include <Menu.h>
#include <stdio.h>
#include <vex.h>

bool isActive;

void Menu::addButton(int x, int y, int width, int height, char *text, void (*ptr)(void))
{
  button b;
  b.setup(x, y, width, height, text, ptr);
  buttons.push_back(b);
}
void Menu::Update()
{
  for (size_t i = 0; i < buttons.size(); i++) {
    button* btn = &buttons[i];
    point p = {
      Brain.Screen.xPosition(),
      Brain.Screen.yPosition()
    };
    if(checkCollsion(&p, &btn -> s))
    {
      btn -> functionpointer();
    }
  }
}

bool Menu::checkCollsion(point *p, square *s)
{
    return p -> x >= s -> x && p -> x <= s -> x + s -> w && p -> y >= s-> y && p->y <= s -> y + s -> h;
}
