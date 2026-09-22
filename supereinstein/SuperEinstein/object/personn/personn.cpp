#include "personn.h"

Personn::Personn(QPoint& p): Object (p)
{
    _labelStates = new QMap<stateOfPersonn,QLabel*>();
    _isOnFloor = false;
}

Personn::~Personn()
{
    for(auto elem : *_labelStates)
    {
        elem = nullptr;
        delete elem;
    }
    delete _labelStates;
}

void Personn::setStatePersonn(stateOfPersonn state)
{
    _state = state;
}


void Personn::setIsJumping(bool isJumping)
{
    if(isJumping==false){
        _state = stay;
    }
    _isJumping = isJumping;
}

bool Personn::getIsJumping()
{
    return _isJumping;
}

bool Personn::getIsOnFloor()
{
    return _isOnFloor;
}

void Personn::setIsOnFloor(bool b)
{
    _isOnFloor = b;
}

void Personn::movePersonn(int dx, int dy)
{
    if(dx>=0){
        this->addPosition({dx,dy});

    }else if (dx<0) {
            this->addPosition({dx,dy});
    }
}

bool Personn::isDead()
{
    if(_life<=0){return true;}
    return false;
}

void Personn::loseLife()
{
    _life--;
}


int Personn::getLife()
{
    return _life;
}

void Personn::setLife(int life)
{
    _life = life;
}

element Personn::getId()
{
    //return nothing because a personn can be declared
}

void Personn::setScaledSize(QSize scale)
{
    for (auto elem : *_labelStates)
    {
        elem->movie()->setScaledSize(scale);
        elem->setFixedSize(scale);
    }
}

bool Personn::getIsTouch()
{
    return _isTouch;
}

void Personn::setIsTouch(bool b)
{
    //_isTouch = b;
}



QLabel* Personn::getLabel()
{
    return nullptr;
}




void Personn::closeAndHide()
{
    /*************************************
     * close and hide all label thate they
     * are not used
     * **********************************/
    for(auto e : (*_labelStates).keys()){
        if (e != _state){
            (*_labelStates).value(e)->movie()->stop();
            (*_labelStates).value(e)->hide();
        }
    }
}

