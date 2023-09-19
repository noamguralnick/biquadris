#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  dg = XOpenDisplay(NULL);
  if (dg == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(dg);
  w = XCreateSimpleWindow(dg, RootWindow(dg, s), 10, 10, width, height, 1,
                          BlackPixel(dg, s), WhitePixel(dg, s));
  XSelectInput(dg, w, ExposureMask | KeyPressMask);
  XMapRaised(dg, w);

  Pixmap pix = XCreatePixmap(dg,w,width,
        height,DefaultDepth(dg,DefaultScreen(dg)));
  gc = XCreateGC(dg, pix, 0,(XGCValues *)0);

  XFlush(dg);
  XFlush(dg);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[7][10]={"white", "black", "red", "green", "blue"};

  cmap=DefaultColormap(dg,DefaultScreen(dg));
  for(int i=0; i < 5; ++i) {
      XParseColor(dg,cmap,color_vals[i],&xcolour);
      XAllocColor(dg,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(dg,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(dg, w, &hints);

  XSynchronize(dg,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(dg, gc);
  XCloseDisplay(dg);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(dg, gc, colours[colour]);
  XFillRectangle(dg, w, gc, x, y, width, height);
  XSetForeground(dg, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(dg, w, DefaultGC(dg, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawGridLines(int x, int y, int gridSize) {
  int width = 220;  
  int height = 360; 

  for (int i = 0; i <= width; i += gridSize) {
    XDrawLine(dg, w, gc, x + i, y, x + i, y + height);
  }

  for (int j = 0; j <= height; j += gridSize) {
    XDrawLine(dg, w, gc, x, y + j, x + width, y + j);
  }
}

void Xwindow::drawCell(int x, int y, int cellColor) {
  int gridSize = 20; 

  int cellX = x * gridSize;
  int cellY = y * gridSize;
  int cellSize = gridSize;

  fillRectangle(cellX, cellY, cellSize, cellSize, cellColor);
}
