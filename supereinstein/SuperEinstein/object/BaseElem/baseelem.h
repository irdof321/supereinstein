#ifndef BASEELEM_H
#define BASEELEM_H

#include "object/object.h"
#include <QLabel>

#define DEFAULT_SIZE 50

/**
 * @class The BaseElem class
 * is the class who contains all object that
 * don t need to move, means that they have a QPixmap
 * that it have to be iniatilzed in each daugther
 */

class BaseElem : public Object
{
        Q_OBJECT
    protected:
        /**
         * @variable _texture
         * contains the image of the object
         */
        QPixmap* _texture;
    public:
        /**
         * @brief BaseElem
         * @param point is the position
         */
        BaseElem(QPoint& point);
        ~BaseElem();
        /**
          * @brief getPixmap
          * @return the QPixmap _texture
          */
         QPixmap* getPixmap();
        void setZero(QPoint& zero);
};

#endif // BASEELEM_H
