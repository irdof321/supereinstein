#ifndef NEWTON_H
#define NEWTON_H

#include "minibot.h"


class Newton : public MiniBot
{
        Q_OBJECT
    public:
        Newton(QPoint& p,Matrix* posWorld);
        element getId() ;
        bool thereIsHole(UtilityGame::direction dir);
        void setNewtonGif();
    private:
        QPoint _initPoint;
};

#endif // NEWTON_H
