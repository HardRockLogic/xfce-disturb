#ifndef MOUSE_H
#define MOUSE_H

#include <X11/Xlib.h>

class Mouse {
private:
  bool position_state_;

  Display *display;
  Window root;
  int root_x, root_y, win_x, win_y;
  unsigned int mask;

public:
  void disturbe();
};

#endif
