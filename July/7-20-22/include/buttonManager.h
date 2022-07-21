#include <button.h>

class buttonManager
{
  public:
    void addButtons(button b[], int size);
    void addButton(int (*functionpointer)(void));
};