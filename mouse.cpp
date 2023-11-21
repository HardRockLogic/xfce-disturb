#include "mouse.h"
#include <X11/Xlib.h>
#include <iostream>
#include <signal.h>

void Mouse::disturbe(Display *display, Window *root, int *root_x, int *root_y,
                     int *win_x, int *win_y, unsigned int *mask) {
  short unsigned step;
  if (position_state_) {
    step = -1;
  } else {
    step = 1;
  }

  if (!(display && root && root_x && root_y && win_x && win_y && mask)) {
    std::cerr << "\nSome pointers are emtpy, cannot proceed.\n";
    raise(SIGINT);
  }
  XQueryPointer(display, *root, root, root, root_x, root_y, win_x, win_y, mask);

  XWarpPointer(display, None, *root, 0, 0, 0, 0, *root_x, *root_y + step);
  XFlush(display);

  position_state_ = !position_state_;
}
