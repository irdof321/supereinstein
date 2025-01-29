#ifndef OBJECT_H
#define OBJECT_H

#define ZERO_X_REL 120
#define ZERO_Y_REL 300

#include <QObject>
#include <QPoint>
#include <QLabel>
#include "Utility/Utility.h"

#include <QDebug>

using namespace UtilityGame;

/**
 * @class The Object class
  *Object is the mother class of all objects
  *each object girl must have at least  a position
  *and a hitbox.
  *PointZero is the relative zero in the
  *field.
  *You can choose the same zero of QT in this
  *case don t call the function.

 */

class Object : public QObject
{


        Q_OBJECT
    public:
        Object(QPoint& position);
        ~Object();
        /**
         * @brief getPosition
         * return a QPoint of the position
         * @return
         */
        const QPoint getPosition();
        /**
         * @brief getXlength
         * @return
         * the width
         */
        const int& getXlength();
        /**
         * @brief getYlength
         * @return the length
         */
        const int& getYlength();
        /**
         * @brief setPosition
         *call for change the position
         * @param newPosition
         * is the new position of type QPoint
         */
        void setPosition(QPoint newPosition);
        /**
         * @brief getId
         * @return a type of UtilityGame::element
         * who refer to the correct elem, for example
         * an object return UtilityGame::element::object
         * this function must be ovveride
         */
        virtual element getId();
        /**
         * @brief addPosition
         * add addPos to the current position _position
         * @param addPos
         * addPos is type of QPoint
         */
        void addPosition(QPoint addPos);

    protected:

        /**
         * @brief PointZero
         * Set the QPoint equal to the zero
         */
        QPoint PointZero;
        QPoint _position;
        /**
         * @brief _XlengthHitBox
         * width of the hitbox
         */
        int _XlengthHitBox;
        /**
         * @brief _YlengthHitBox
         * height of the hit box
         */
        int _YlengthHitBox;

};

#endif // OBJECT_H
