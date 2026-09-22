#include "minibot.h"
#include <QDebug>

MiniBot::MiniBot(QPoint& p, Matrix* posWorld): Personn(p)
{
    // set standad player size
    QSize BotSize (BOT_SIZE,BOT_SIZE);                  // for scale the good size of the label
    _XlengthHitBox = BOT_SIZE;
    _YlengthHitBox = BOT_SIZE;

    /***********************************************************************
     * set  a map with label and states, and set the movie in the labels
     * *********************************************************************/
    std::vector<QMovie*> _allMovie;

    //set the file name of all gif
    std::vector<QString> FileNames;
    FileNames.push_back(":/texture/personn/minibotMarche.gif");
    FileNames.push_back(":/texture/personn/minibotMarcheBack.gif");
    FileNames.push_back(":/texture/personn/botDead.gif");

    // create all state vector
    std::vector<stateOfPersonn> states = { walkRight, walkLeft,deadSate};

    //set the movies
    for (int i (0);i<BOT_STATES;++i){
        QMovie* movie = new QMovie(FileNames[i]);
        movie->setScaledSize(BotSize);
        movie->setSpeed(200);
        _allMovie.push_back(movie);
    }

    // insert the movies in the labels
    for (int i (0);i<BOT_STATES;++i){
        QLabel* label = new QLabel();
        label->setFixedSize(BotSize);
        label->setMovie(_allMovie[i]);
        //label->setStyleSheet("QLabel { background-color : blue }");
        _labelStates->insert(states[i],label);

    }
    /*******************************************
    ************* variables init*****************
    ***********************************************/
    _state =  walkRight;
    _isJumping = false;
    _isOnFloor = false;
    _life = 1;
    _moveRight = true;
    _posWorld = posWorld;

}



QLabel* MiniBot::getLabel()
{
    this->closeAndHide();
    return (*_labelStates)[_state];
}

bool MiniBot::getMoveRight()
{
    return _moveRight;
}

void MiniBot::setMoveRight(bool b)
{
    _moveRight=b;
}

bool MiniBot::thereIsHole(direction dir)
{
    int matrixPosX = this->getPosition().x()/50;        //return the position into the matrix
    int matrixPosY = this->getPosition().y()/50 ;
    if(matrixPosX <1){
        return true;
    }else if (matrixPosX > 999){
       return true;
    }
    if (dir==UtilityGame::right){
        if ((*_posWorld)[matrixPosX][matrixPosY+1]==0){
            return true;
        }else{
            return false;
        }
    }
    if (dir==UtilityGame::left){
        if ((*_posWorld)[matrixPosX-1][matrixPosY+1]==0){
            return true;
        }else{
            return false;
        }
    }
}

element MiniBot::getId()
{
    return Bot;
}

