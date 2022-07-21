#pragma once

#include <vector>
#include <button.h>

class Menu { 
  public:
    void Update();
    void addButton(int x, int y, int width, int height, char *text, void (*ptr)(void));
  bool checkCollsion(point *p, square *s);
  std::vector<button> buttons;
};

