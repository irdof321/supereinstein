#include "underfloor.h"

UnderFloor::UnderFloor(QPoint& point) : BaseElem (point)
{
    _texture = new QPixmap(":/texture/object/underFloor.png");
}
