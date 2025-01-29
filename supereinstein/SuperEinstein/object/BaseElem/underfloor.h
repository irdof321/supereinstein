#ifndef UNDERFLOOR_H
#define UNDERFLOOR_H

#include "baseelem.h"

/**
 * @class The UnderFloor class
 * it is a baseElem who rpresnt all thinks under
 * the floor height
 */
class UnderFloor : public BaseElem
{
    public:
        /**
         * @brief UnderFloor
         * @param point is the position
         */
        UnderFloor(QPoint& point);
};

#endif // UNDERFLOOR_H
