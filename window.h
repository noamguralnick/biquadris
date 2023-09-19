#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <string>
#include <X11/Xlib.h>

class Xwindow {
  Display *dg;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=800, int height=600);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  enum {White=0, Black, Red, Green, Blue, Purple}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void drawGridLines(int x, int y, int gridSize);

  void drawCell(int x, int y, int cellColor);

};

#endif
