#include "object.h"
#include <cmath>

Object::Object(QPoint& position) : QObject()
{
    PointZero = QPoint(ZERO_X_REL,ZERO_Y_REL);
    _position = (position+PointZero);
}

Object::~Object()
{

}


void Object::setPosition(QPoint newPosition)
{
    _position = newPosition ;
}


 element Object::getId()
{

}


void Object::addPosition(QPoint addPos)
{
    _position += addPos;
}


const QPoint Object::getPosition()
{
    return _position;
}


const int& Object::getXlength()
{
    return  _XlengthHitBox;
}

const int& Object::getYlength()
{
    return  _YlengthHitBox;
}



