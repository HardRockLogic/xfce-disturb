#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/scrnsaver.h>
#include <X11/keysym.h>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  Display *display = XOpenDisplay(nullptr);

  if (!display)
    return 1;

  Window root = DefaultRootWindow(display);
  int root_x, root_y, win_x, win_y;
  unsigned int mask;
  // Query cursor posirion
  XQueryPointer(display, root, &root, &root, &root_x, &root_y, &win_x, &win_y,
                &mask);

  // Allocating scrnsaver info
  XScreenSaverInfo *info = XScreenSaverAllocInfo();

  std::cout << "root(x,y) " << root_x << " " << root_y << "\n";
  std::cout << "window(x,y) " << win_x << " " << win_y << "\n";

  // 4 mins sleep is a 240s
  std::this_thread::sleep_for(std::chrono::seconds(4));

  // XScreenSaverQueryInfo(display, root, info);
  // std::cout << "idle itme: " << info->idle << "\n";

  // Set new position
  XWarpPointer(display, None, root, 0, 0, 0, 0, root_x, root_y + 2);
  XFlush(display);

  // Faking key event
  KeyCode a_keycode = XKeysymToKeycode(display, XK_Shift_L);

  // Press and release
  XTestFakeKeyEvent(display, a_keycode, True, 0);
  XTestFakeKeyEvent(display, a_keycode, False, 0);
  XFlush(display);

  XScreenSaverQueryInfo(display, root, info);
  std::cout << "idle itme: " << info->idle << "\n";

  XFree(info);
  XCloseDisplay(display);
  return 0;
}
