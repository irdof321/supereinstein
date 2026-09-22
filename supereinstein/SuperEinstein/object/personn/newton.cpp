#include "newton.h"

Newton::Newton(QPoint& p, Matrix* posWorld) : MiniBot(p,posWorld), _initPoint(p)
{
    _XlengthHitBox = 50;
    _YlengthHitBox = 100;
}

element Newton::getId()
{
    return UtilityGame::element::newton;
}

bool Newton::thereIsHole(direction dir)
{
    if(_initPoint.x()<10000 &&(dir==direction::left)){return true;}
    if(this->getPosition().x()>=11000&& dir == direction::right){return true;}
    return MiniBot::thereIsHole(dir);
}

void Newton::setNewtonGif()
{
    /***********************************************************************
     * set  a map with label and states, and set the movie in the labels
     * *********************************************************************/
    std::vector<QMovie*> _allMovie;

    //set the file name of all gif
    std::vector<QString> FileNames;
    FileNames.push_back(":/texture/personn/newtonRight.gif");
    FileNames.push_back(":/texture/personn/newtonLeft.gif");
    FileNames.push_back(":/texture/personn/NewtonFace.gif");

    // create all state vector
    std::vector<stateOfPersonn> states = { walkRight, walkLeft,deadSate};

    //set the movies
    for (int i (0);i<BOT_STATES;++i){
        QMovie* movie = new QMovie(FileNames[i]);
        movie->setScaledSize({int(X_SIZE_PLAYER),int(Y_SIZE_PLAYER)});
        movie->setSpeed(200);
        _allMovie.push_back(movie);
    }

    // insert the movies in the labels
    for (int i (0);i<BOT_STATES;++i){
        QLabel* label = new QLabel();
        label->setFixedSize({int(X_SIZE_PLAYER),int(Y_SIZE_PLAYER)});
        label->setMovie(_allMovie[i]);
        //label->setStyleSheet("QLabel { background-color : blue }");
        _labelStates->insert(states[i],label);
    }

    setLife(3);
}


