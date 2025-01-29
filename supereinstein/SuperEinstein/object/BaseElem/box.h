#ifndef BOX_H
#define BOX_H

#include "baseelem.h"

/**
 * @class The Box class it is a baseElem who
 * represent Box
 */
class Box : public BaseElem
{
    public:
        /**
         * @brief Box
         * @param p  is the position
         */
        Box(QPoint& p);
};

#endif // BOX_H
