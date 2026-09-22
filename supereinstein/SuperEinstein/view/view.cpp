#include "view.h"

View::View(int x, int y, QWidget *parent) : QWidget(parent)
{
    _XLength=x;
    _YLength=y;
}

View::~View()
{

}
