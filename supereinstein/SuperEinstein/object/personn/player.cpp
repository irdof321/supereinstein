#include "player.h"

#include <QDir>
#include<QString>
#include <math.h>



Player::Player(QPoint& position) : Personn (position)
{
    // set standad player size
    QSize PlayerSize (X_SIZE_PLAYER,Y_SIZE_PLAYER);                     // size for scale the movie and the label
    _XlengthHitBox = X_SIZE_PLAYER;
    _YlengthHitBox = Y_SIZE_PLAYER;

    /***********************************************************************
     * set  a map with label and states, and set the movie in the labels
     * *********************************************************************/
    std::vector<QMovie*> _allMovie;

    //set the file name of all gif
    std::vector<QString> FileNames;
    FileNames.push_back(":/texture/personn/SuperEinsteinFace.gif");
    FileNames.push_back(":/texture/personn/SuperEinsteinmarche.gif");
    FileNames.push_back(":/texture/personn/marcheback.gif");
    FileNames.push_back(":/texture/personn/SuperEinsteinSaut.gif");
    FileNames.push_back(":/texture/personn/SuperEinsteinSautBack.gif");
    FileNames.push_back(":/texture/personn/SuperEinsteinSautFace.gif");

    // create all state vector
    std::vector<stateOfPersonn> states = {stay , walkRight, walkLeft, jumpRight, jumpLeft,jumpFace};

    //set the movies
    for (int i (0);i<NB_STATES;++i){
        QMovie* movie = new QMovie(FileNames[i]);
        movie->setScaledSize(PlayerSize);
        movie->setSpeed(200);
        _allMovie.push_back(movie);
    }

    // set the labels
    for (int i (0);i<NB_STATES;++i){
        QLabel* label = new QLabel();
        label->setFixedSize(PlayerSize);
        label->setMovie(_allMovie[i]);
       // label->setStyleSheet("QLabel { background-color : red }");
        _labelStates->insert(states[i],label);

    }
    QPixmap* img = new QPixmap(":/object/texture/heart.png");
    _labelLife = new QLabel();
    _labelLife->setPixmap(*img);

    /****************************************************************
     *                          init
     * *************************************************************/
    _state =  stay;
    _isJumping = false;
    _isOnFloor = true;
    _life = 10;
    _isTouch = false;

    delete img;
}



Player::~Player()
{
    delete[]  _labelStates;
}


bool Player::isDead()
{
    if(_life==0){return true;}
    return false;
}



QLabel* Player::getHeart()
{
    return _labelLife;
}

element Player::getId()
{
    return UtilityGame::Einstein;
}

void Player::setIsTouch(bool b)
{
    _isTouch = b;
}



QLabel* Player::getLabel()
{
    this->closeAndHide();
    return (*_labelStates)[_state];
}











