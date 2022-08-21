#pragma once

#include "point.h"

// rectangle class
//          top, y
//       +----------+                \
//  left |          | right          | height
//  x    |          | (left + width) |
//       |          |                |
//       +----------+                /
//   bottom (top + height)
//       \----------/
//           width

namespace med {

class Rect {
    Point _topLeft;
    unsigned int _width, _height;
public:
    Rect();
    Rect(int top, int left, unsigned int width, unsigned int height);
    Rect(const Point &topLeft, unsigned int width, unsigned int height);

    unsigned int width() const;
    unsigned int height() const;
    int top() const;
    int left() const;
    int bottom() const;
    int right() const;
    Point center() const;
    
    void moveTo(int top, int left);
    void moveTo(const Point &topLeft);
    void resize(unsigned int width, unsigned int height);
    bool inside(int y, int x) const;
    bool inside(const Point &pos) const;
    bool overlap(const Rect& other) const;
    unsigned long long area() const;
};

}
