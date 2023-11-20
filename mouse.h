#ifndef MOUSE_H
#define MOUSE_H

#include <X11/Xlib.h>

class Mouse {
private:
  bool position_state_;

public:
  Mouse();
  void disturbe(Display *, Window, int &, int &, int &, int &, unsigned int &);
};

#endif
