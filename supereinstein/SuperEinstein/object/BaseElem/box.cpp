#include "box.h"

Box::Box(QPoint& p) : BaseElem (p)
{
    _texture = new QPixmap(":/texture/object/Box.png");
}
