#include "baseelem.h"

BaseElem::BaseElem(QPoint& point) : Object (point)
{
    _XlengthHitBox = DEFAULT_SIZE;
    _YlengthHitBox = DEFAULT_SIZE;
}

BaseElem::~BaseElem()
{

}

QPixmap* BaseElem::getPixmap()
{
    return _texture;
}

void BaseElem::setZero(QPoint& zero)
{
    PointZero = zero;
}

