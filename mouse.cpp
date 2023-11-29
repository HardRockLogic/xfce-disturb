#include "mouse.h"
#include <X11/Xlib.h>
#include <ios>
#include <iostream>
#include <signal.h>

Mouse::Mouse() { position_state_ = true; };

void Mouse::disturbe(Display *display, Window *root, int *root_x, int *root_y,
                     int *win_x, int *win_y, unsigned int *mask) {
  short step;
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

  // XWarpPointer(display, None, *root, 0, 0, 0, 0, *root_x, *root_y + step);
  XWarpPointer(display, None, *root, 0, 0, 0, 0, *root_x, step);
  std::cout << *root_y << '\n';
  std::cout << *root_y + step << '\n';
  XFlush(display);

  // std::cout << step << '\n';

  position_state_ = !position_state_;
}
// TODO:
// - debug print step
// - try to copy root inside mehtod
// - try to change QueryPointer wague signature
// (optionally) use DefaltRootWindow macros inside func call
