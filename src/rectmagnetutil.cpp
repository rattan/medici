#include "rectmagnetutil.h"

void RectMagnetUtil::magnetRect(const Rect &destination, Rect &target) {
    if(isAttached(destination, target)) return;
    
    int rightToLeft = abs(destination.right() - target.left());
    int leftToRight = abs(destination.left() - target.right());
    int topToBottom = abs(destination.top() - target.bottom());
    int bottomToTop = abs(destination.bottom() - target.top());
    
    int attachHorizontal = leftToRight < rightToLeft ? ATTACH_LEFT_TO_RIGHT : ATTACH_RIGHT_TO_LEFT;
    int distanceHorizontal = rightToLeft < leftToRight ? rightToLeft : leftToRight;
    int attachVertical = topToBottom < bottomToTop ? ATTACH_TOP_TO_BOTTOM : ATTACH_BOTTOM_TO_TOP;
    int distanceVertical = topToBottom < bottomToTop ? topToBottom : bottomToTop;
    
    int firstAttach = distanceVertical < distanceHorizontal ? attachVertical : attachHorizontal;
    attach(destination, target, firstAttach);
    if(isAttached(destination, target)) return;
    
    int secondAttach = distanceVertical < distanceHorizontal ? attachHorizontal : attachVertical;
    attach(destination, target, secondAttach);
}

bool RectMagnetUtil::isAttached(const Rect& destination, const Rect& target) {
    if((destination.top() == target.bottom() || destination.bottom() == target.top()) &&
       (destination.right() >= target.left() || destination.left() >= target.right())) return true;
    if((destination.right() == target.left() || destination.left() == target.right()) &&
       (destination.top() >= target.bottom() || destination.bottom() >= target.top())) return true;
    return false;
}

void RectMagnetUtil::attach(const Rect& destination, Rect& target, int direction) {
    switch(direction) {
        case ATTACH_RIGHT_TO_LEFT:
            target.moveTo(target.top(), destination.right());
            break;
        case ATTACH_LEFT_TO_RIGHT:
            target.moveTo(target.top(), destination.left() - target.width());
            break;
        case ATTACH_TOP_TO_BOTTOM:
            target.moveTo(destination.top() + target.height(), target.left());
            break;
        case ATTACH_BOTTOM_TO_TOP:
            target.moveTo(destination.bottom(), target.left());
            break;
    }
}
