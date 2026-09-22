#include "controller.h"
#include "controller.h"
#include <cmath>

int remaining = 0;

Controller::Controller() : QObject()
{
    /***********************
     * Declaration
     * ********************/
    _timer = new QTimer();
    _pTouchTimer = new QTimer();
    _data = new Data();
    _outView = new OutputView(_data);
    _inView = new InputView(_outView);
    _music = new QSoundEffect();
    _music->setSource(QUrl::fromLocalFile(":/music/music3.wav"));



    /***********************
     * initialisation
     * ********************/
     _timer->setInterval(TIME_INTERVAL);
     _task= no;                           // set the first state, the player is doing nothing
     YMaxJump = 0;
     _onMenu = false;


    /******************************************************************************************************
     * Connections
     * ****************************************************************************************************/
     QObject::connect(this,SIGNAL(showMenu()),_outView,SLOT(showMenu()));
     QObject::connect(this,SIGNAL(gameOver()),_data,SLOT(reset()));
     QObject::connect(this,SIGNAL(gameOver()),_outView,SLOT(gameOver()));
     QObject::connect(this,SIGNAL(sendUpdate()),_outView,SLOT(update()));
     QObject::connect(this,SLOT(start()),_timer,SLOT(start()));

     QObject::connect(_timer,SIGNAL(timeout()),this,SLOT(integrate()));                                          //timer timeout say when the game must be updated
    QObject::connect(_pTouchTimer,SIGNAL(timeout()),this,SLOT(playerIsNoTouch()));
    QObject::connect(_inView,&InputView::UpPushed,this,&Controller::setTask);                                 // input view fill the executions stack for the next update

    QObject::connect(_outView,SIGNAL(sigStart()),_timer,SLOT(start()));
    QObject::connect(_outView,SIGNAL(sigReset()),_data,SLOT(reset()));
    QObject::connect(_outView,SIGNAL(sigStart()),this,SLOT(start()));
    QObject::connect(this,SIGNAL(sigEnd()),_outView,SIGNAL(sigEnd()));
    QObject::connect(_outView,SIGNAL(volume(int)),this,SLOT(setVolume(int)));    
    QObject::connect(_outView,SIGNAL(sigKeyPressed(QKeyEvent*)),_inView,SLOT(sloKeyPressed(QKeyEvent*)));
    QObject::connect(_outView,SIGNAL(sigKeyRleased(QKeyEvent*)),_inView,SLOT(sloKeyReleased(QKeyEvent*)));
    QObject::connect(_outView,SIGNAL(sigDiff(UtilityGame::difficulty)),_data,SLOT(init(UtilityGame::difficulty)));
}

Controller::~Controller()
{
    delete _timer;
    delete _data;
    delete _outView;
    delete _inView;
    delete _music;
}

void Controller::show()
{
    _outView->show();
    _music->play();
}

void Controller::integrate()
{
    Player*p =_data->getPlayer();
    if((!_onMenu)&&!(p->getLife()<0) ){                 //if game is turning
        executionOfTask();
        if(p->getIsJumping()){
            jumpPlayer();
        }

        gravity();
        IAControlBot();

        for (uint k(0); k< _data->getBot().size();k++)   // look if there is a dead bot
        {
            MiniBot* elem = _data->getBot()[k];
            if(elem->isDead()){
                elem->setStatePersonn(deadSate);
                elem->setPosition({elem->getPosition().x(),elem->getPosition().y()+INT_Y_MOVE});
                if(elem->getPosition().y()>1000){                    
                    if(_data->BotIsDead(k))
                    {
                        _timer->stop();
                        _onMenu = true;
                        end();
                    }
                }
            }

            elem = nullptr;
            delete elem;
        }
    }

       if(p->getPosition().y()>690){        // if player is more the y = 690 he die
            _data->playerFall();
            _data->getPlayer()->loseLife();
        }

        _timer->start(TIME_INTERVAL);
        emit sendUpdate();

       if(p->getLife()<0){
           emit gameOver();
           _timer->stop();
           _onMenu = true;
       }
       if(_onMenu && !(remaining>0))
       {
            remaining = _pTouchTimer->remainingTime();
               _pTouchTimer->stop();
       }else if(!_pTouchTimer->isActive()){
           _pTouchTimer->start(remaining);
           remaining=0;
       }

      /* if(p->getPosition().x()>11000)
       {
           _timer->stop();
           _onMenu = true;
           end();
       }*/

       p=nullptr;
       delete p;
}

void Controller::executionOfTask()
{
    bool inJumpPhase = _data->getPlayer()->getIsJumping();
        switch (_task) {
            case a :{
                movePersonnLeft(INT_X_MOVE);
                break;
            }
            case d:{
                movePersonnrRight(INT_X_MOVE);
                break;
            }
            case A :{
                if (inJumpPhase){
                    movePersonnLeft(INT_X_MOVE);
                }else{
                    movePersonnLeft(2*INT_X_MOVE);
                }
                break;
            }
            case D:{
                if(inJumpPhase){
                    movePersonnrRight(INT_X_MOVE);
                }else{
                    movePersonnrRight(2*INT_X_MOVE);
                }
                break;
            }
            case space :{
                if(!(inJumpPhase)&&(_data->getPlayer()->getIsOnFloor())){
                    YMaxJump = _data->getPlayer()->getPosition().y()-HEIGHT_JUMP;  // calculate the max height that player can reach from his position
                    _data->getPlayer()->setIsJumping(true);
                }
                break;
            }
            case esc :{
                emit showMenu();
                _onMenu = true;
                _timer->stop();
                break;
            }
            default: {
                if(inJumpPhase||!_data->getPlayer()->getIsOnFloor()){
                    _data->getPlayer()->setStatePersonn(jumpFace);
                }else{
                    _data->getPlayer()->setStatePersonn(stay);
                }
                break;
            }
        }
}

void Controller::movePersonnLeft(int move)
{
    if(!(_data->getPlayer()->getPosition().x()<=64)){
        if (PersonnCanMove(_data->getPlayer(),_task)){
            _data->getPlayer()->movePersonn(-move,0);
            if(_data->getPlayer()->getIsJumping()||!_data->getPlayer()->getIsOnFloor()){
                _data->getPlayer()->setStatePersonn(jumpLeft);
            }else{
                _data->getPlayer()->setStatePersonn(walkLeft);
            }
        }
    }
}

void Controller::movePersonnrRight(int move)
{
    if(!(_data->getPlayer()->getPosition().x()>=11000)){
        if (PersonnCanMove(_data->getPlayer(),_task)){
            _data->getPlayer()->movePersonn(move,0);
            if(_data->getPlayer()->getIsJumping()||!_data->getPlayer()->getIsOnFloor()){
                _data->getPlayer()->setStatePersonn(jumpRight);
            }else{
                _data->getPlayer()->setStatePersonn(walkRight);
            }
        }
    }
}

void Controller::jumpPlayer()
{
    Player* p = _data->getPlayer();
    if(p->getPosition().y()<=YMaxJump){
        p->setIsJumping(false);
    }else{
        if(PlayCanJump()){
             p->movePersonn(0,-INT_Y_MOVE);
        }else{
            p->setIsJumping(false);
        }

    }
    p=nullptr;
    delete  p;
}

bool Controller::PlayCanJump()
{
    Player* p = _data->getPlayer();
    int px = p->getPosition().x();
    int py = p->getPosition().y();

    for(auto elem : _data->getBaseElem()){
        int ox = elem->getPosition().x();
        int oy = elem->getPosition().y();
        if (norm({0,py-oy-DEFAULT_SIZE})<INT_Y_MOVE){
            if(((px>=ox)&&(px<ox+DEFAULT_SIZE))||((px+50>ox)&&(px+50<=ox+DEFAULT_SIZE))){
                _data->getPlayer()->setPosition({_data->getPlayer()->getPosition().x(),elem->getPosition().y()+DEFAULT_SIZE});
                p = nullptr; delete p;
                return false;
            }

        }
    }


    p = nullptr; delete p;
    return true;
}

bool Controller::PersonnCanMove(Personn* p, UiEvent keyMove)
{

    int xp = p->getPosition().x();
    int yp = p->getPosition().y();

    int pxSize = p->getXlength();
    int pySize = p->getYlength();

    /*************************************************
     * the distance between the personn and the objects
     * is lower than 500 because it doesn t need more
     * computations
     * ***********************************************/

    for(auto elem : _data->getBaseElem()){
        if (norm({p->getPosition()-elem->getPosition()})<500){

            int xo = elem->getPosition().x();
            int yo = elem->getPosition().y();
            if(!canMoveCalc( xp,  yp, xo, yo, pxSize, pySize, keyMove, p,false)){return false;}
        }


    }//for
    /************************************************************************************
     * Same with bot
     * ***********************************************************************************/


    if(p->getId()!=Bot){
        for(auto elem : _data->getBot()){
            if (norm({p->getPosition()-elem->getPosition()})<500){

                int xo = elem->getPosition().x();
                int yo = elem->getPosition().y();
                if(!canMoveCalc( xp,  yp, xo, yo, pxSize, pySize, keyMove, p,true)){return false;}
            }


        }//for
    }

    // look if the obstacle is a Bot
    if(p->getId()==Bot)
    {
        int Xp =_data->getPlayer()->getPosition().x();
        int Yp = _data->getPlayer()->getPosition().y();
       if(BotHurtPlayer( xp,  yp, Xp,
                       Yp, X_SIZE_PLAYER, Y_SIZE_PLAYER, keyMove))
       {
           if(!_data->getPlayer()->getIsTouch())
           {
               _data->getPlayer()->loseLife();
               _data->getPlayer()->setIsTouch(true);
               _pTouchTimer->start(2000);
           }
       }
    }
    p = nullptr; delete p;
    return  true;
}

bool Controller::canMoveCalc(int xp, int yp, int xo, int yo, int pxSize, int pySize, UiEvent keyMove,Personn* p,
                             bool withBot,int oXsize,int oYsize)
{
    if((keyMove== UiEvent::a)||(keyMove==UiEvent::A)){                                   //he want to moveleft
        if((xp<=xo +pxSize)&&(xp>xo)){
            if(((yo>=yp)&&(yo<yp+pySize))||((yo+oYsize>yp)&&(yo+oYsize<=yp))){
                if(!p->getIsTouch()&&withBot&&(p->getId()==Einstein)){
                    p->loseLife();
                    p->setIsTouch(true);
                    _pTouchTimer->setSingleShot(true);
                    _pTouchTimer->start(2000);
                    return false;
                }
                p->setPosition({xo+oXsize,yp});
                p = nullptr;
                delete p;
                return false;
            }
        }
    }//UiEvent a
    if((keyMove==UiEvent::d)||(keyMove==UiEvent::D)){
        if((xp+pxSize>=xo)&&(xp+pxSize<xo+oXsize)){
            if(((yo>=yp)&&(yo<yp+pySize))||((yo+oYsize>yp)&&(yo+oYsize<=yp))){
                if(!p->getIsTouch()&&withBot&&(p->getId()==Einstein)){
                    p->loseLife();
                    p->setIsTouch(true);
                    _pTouchTimer->setSingleShot(true);
                    _pTouchTimer->start(2000);
                }
                p->setPosition({xo-pxSize,yp});;
                p = nullptr;
                delete p;
                return false;
            }
        }

    }//UiEvent d
    return true;
}

bool Controller::BotHurtPlayer(int xb, int yb, int xp, int yp, int pxSize, int pySize, UiEvent keyMove)
{
    if(keyMove==a){
        if((xb>xp && xb<=xp+pxSize)&&(((yb<=yp)&&(yb>yp+pySize))||((yb+50<=yp+pySize)&&(yb+50>yp))))
        {
            return true;
        }
        return false;
    }
    if(keyMove==d){
        if((xb+50>=xp && xb+50<xp+pxSize)&&(((yb<=yp)&&(yb>yp+pySize))||((yb+50<=yp+pySize)&&(yb+50>yp))))
        {
            return true;
        }
        return false;
    }

}



void Controller::gravity()
{
    // **********gravity player*********************************
    Player* p = _data->getPlayer();

    int xp = p->getPosition().x();
    int yp = p->getPosition().y();
    int pxSize = p->getXlength();
    int pySize = p->getYlength();
    p->setIsOnFloor(false);

    // gravity : player-> cool elemnt
    for(auto elem : _data->getBaseElem()){
        int yo = elem->getPosition().y();
        int xo = elem->getPosition().x();
        if(((xp>=xo)&&(xp<xo+DEFAULT_SIZE))||((xp+pxSize<=xo+DEFAULT_SIZE)&&(xp+pxSize>=xo))){
            if((yp+pySize==yo)){
                p->setIsOnFloor(true);
            }
        }
    }


    // gravity : player-> bot

    for(uint k(0);k<_data->getBot().size();k++){
        MiniBot* elem = _data->getBot()[k];
        int yb = elem->getPosition().y();
        int xb = elem->getPosition().x();
        int xbSize = DEFAULT_SIZE;
        int ybSize = DEFAULT_SIZE;
        if(elem->getId()== newton){
            xbSize = X_SIZE_PLAYER;
            ybSize = Y_SIZE_PLAYER;
        }
        if(((xp>=xb)&&(xp<xb+xbSize))||((xp+pxSize<=xb+xbSize)&&(xp+pxSize>=xb))){
            if((yp+pySize==yb)&&!elem->isDead()&&!p->getIsTouch()){
                p->setIsOnFloor(true);
                elem->loseLife();
            }
        }
        elem = nullptr;
        delete elem;
    }

    if((!p->getIsOnFloor())&&!(p->getIsJumping())){
        p->movePersonn(0,INT_Y_MOVE);
    }

    //*****************gravity bot******************************
    for(auto bot : _data->getBot()){
        int xb = bot->getPosition().x();
        int yb = bot->getPosition().y();;

        int xbSize = DEFAULT_SIZE;
        int ybSize = DEFAULT_SIZE;
        if(bot->getId()== newton){
            xbSize = X_SIZE_PLAYER;
            ybSize = Y_SIZE_PLAYER;
        }

        bot->setIsOnFloor(false);
        for(auto elem : _data->getBaseElem()){
            int yo = elem->getPosition().y();
            int xo = elem->getPosition().x();
            if(((xb>=xo)&&(xb<xo+DEFAULT_SIZE))||((xb+xbSize<=xo+DEFAULT_SIZE)&&(xb+xbSize>=xo))){
                if((yb+ybSize==yo)){
                    bot->setIsOnFloor(true);
                    if(bot->getId()== newton){
                        bot->setPosition({bot->getPosition().x(),yo-100});
                    }else{
                        bot->setPosition({bot->getPosition().x(),yo-50});
                    }
                }
            }
        }

        if((!bot->getIsOnFloor())){
            bot->movePersonn(0,INT_Y_MOVE);
        }
    }

        p = nullptr;
        delete p;


}

void Controller::IAControlBot()
{
    for(auto bot : _data->getBot()){
        if (bot->getMoveRight()){
            if (bot->thereIsHole(UtilityGame::direction::right)){
                bot->setMoveRight(false);
                if(PersonnCanMove(bot,UiEvent::a)){
                    bot->movePersonn(- INT_X_MOVE,0);
                    bot->setStatePersonn(walkLeft);
                }
            }else{
                if(PersonnCanMove(bot,UiEvent::d)){
                    bot->movePersonn(INT_X_MOVE,0);
                }

            }//right
        }else{
            if (bot->thereIsHole(UtilityGame::direction::left)){
                bot->setMoveRight(true);
                if(PersonnCanMove(bot,UiEvent::d)){
                    bot->movePersonn(INT_X_MOVE,0);
                    bot->setStatePersonn(walkRight);
                }
            }else{
                if(PersonnCanMove(bot,UiEvent::a)){
                    bot->movePersonn(-INT_X_MOVE,0);
                }
            }//left
        }
    }// for _data.getBot()
}

void Controller::setTask(UiEvent task)
{

    _task = task;
}

void Controller::start()
{
    _onMenu = false;
}

void Controller::setVolume(int v)
{
    qreal vr = v;
    _music->setVolume(vr/100);
}

void Controller::playerIsNoTouch()
{
    _data->getPlayer()->setIsTouch(false);
}

void Controller::end()
{
    _data->reset();
    emit showMenu();
    emit sigEnd();
}
