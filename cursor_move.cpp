#include "mouse.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/scrnsaver.h>
#include <X11/keysym.h>
#include <chrono>
#include <iostream>
#include <signal.h>
#include <thread>

Display *display = nullptr;
XScreenSaverInfo *info = nullptr;
// Mills constant -> 240000 is 4secs in mills
unsigned long const wait = 5000;

void singalHeader(int signum) {
  if (display) {
    XCloseDisplay(display);
    std::cout << "\nX11 display closed.\n";
  }
  if (info) {
    XFree(info);
    std::cout << "Screen Saver info freed.\n";
  }
  exit(signum);
}

int main() {
  signal(SIGINT, singalHeader);

  display = XOpenDisplay(nullptr);

  if (!display)
    return 1;

  Window root = DefaultRootWindow(display);
  info = XScreenSaverAllocInfo();

  int root_x, root_y, win_x, win_y;
  unsigned int mask;

  Mouse mouse{};

  while (1) {
    XScreenSaverQueryInfo(display, root, info);

    if (info->idle >= wait) {
      std::cout << "Shift Shot\n";

      mouse.disturbe(display, &root, &root_x, &root_y, &win_x, &win_y, &mask);

      // Faking key event
      KeyCode a_keycode = XKeysymToKeycode(display, XK_Shift_L);

      // Press and release
      XTestFakeKeyEvent(display, a_keycode, True, 0);
      XTestFakeKeyEvent(display, a_keycode, False, 0);
      XFlush(display);

    } else {
      unsigned long eta = wait - info->idle;
      std::cout << "ETA: " << eta << "\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(eta));
    }
  }

  XFree(info);
  XCloseDisplay(display);
  return 0;
}
