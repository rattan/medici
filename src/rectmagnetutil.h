#pragma once

#include "rect.h"

#include <cmath>

class RectMagnetUtil {
private:
    static const int ATTACH_RIGHT_TO_LEFT = 1;
    static const int ATTACH_LEFT_TO_RIGHT = 2;
    static const int ATTACH_TOP_TO_BOTTOM = 3;
    static const int ATTACH_BOTTOM_TO_TOP = 4;
    static bool isAttached(const Rect& destination, const Rect& target);
    static void attach(const Rect& destination, Rect& target, int direction);
public:
    static void magnetRect(const Rect& destination, Rect& target);
};
