#ifndef FLOOR_H
#define FLOOR_H

#include "baseelem.h"


/**
 * @class The Floor class it is a baseElem who
 * represent floor
 */
class Floor : public BaseElem
{
        Q_OBJECT

    public:
        /**
         * @brief Floor
         * @param point  is the position
         */
        Floor(QPoint& point);
        ~Floor();

};

#endif // FLOOR_H
