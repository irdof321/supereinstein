#include "floor.h"
#include <QDir>
#include <QString>

Floor::Floor(QPoint& point) : BaseElem (point)
{
    _texture = new QPixmap(":/texture/object//Floor1.png");
}

Floor::~Floor()
{
    delete _texture;
}


