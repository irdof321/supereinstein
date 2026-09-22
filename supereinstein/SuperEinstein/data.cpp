#include "data.h"
#include <ctime>
#include <QFile>

Data::Data(QObject* parent) : QObject(parent)
{
    _inGame = new std::vector<BaseElem*>();
    _bots = new std::vector<MiniBot*>();
    QPoint p (100,-50);
    _player = new Player(p);
    _element = new Matrix(1000,16);
}

Data::~Data()
{
    delete [] _inGame;
    delete  _player;
}

Player* Data::getPlayer()
{
    return _player;
}

std::vector<BaseElem*> Data::getBaseElem()
{
    return *_inGame;
}

std::vector<MiniBot*> Data::getBot()
{
    return *_bots;
}

void Data::reset()
{
    for (auto bot : *_bots){
        bot->setPosition({1000,1000});
    }
    for (auto elem : *_inGame){
        elem->setPosition({1000,1000});
    }
    _player->setPosition({220,250});
    _player->setLife(3);

}

void Data::init(UtilityGame::difficulty d)
{
    int distBetweenBots = 0;
    switch (d) {
        case easy :{
            _element->setMatrixFromTxt(":/level/easy.txt");
            distBetweenBots = 1000;
            //_element->setMatrixFromTxt(":/level/testMode.txt");
            break;
        }
        case medium :{
            distBetweenBots = 750 ;
            _element->setMatrixFromTxt(":/level/medium.txt");
            break;
        }
        case hard:{
            distBetweenBots = 500;
            _element->setMatrixFromTxt(":/level/hard.txt");
            break;
        }
    }


    /*********************************************************************************************
     * World generator from matrix _element
     * The matrix contains a number between 0 an 3 who relat to an element in enum element
     * and each element in the matrix represents an object of 50 x 50, because it is the default
     * size of the objects
     * *******************************************************************************************/
    for (int l(0);l<_inGame->size();l++){
        BaseElem* elem = (*_inGame)[l];
        elem = nullptr;
    }
    _bots->clear();

    for(int i(0);i<L_MATRIX;i++){
        for (int j(0);j<H_MATRIX;j++){
            switch ((*_element)[i][j]) {
                case underFloorElem :{
                    QPoint Point (50*(i-1),50*j-ZERO_Y_REL);
                    UnderFloor* uf = new UnderFloor(Point);
                    _inGame->push_back(uf);
                    break;
                }
                case FloorElem :{
                    QPoint Point (50*(i-1),50*j-ZERO_Y_REL);
                    Floor* f = new Floor(Point);
                    _inGame->push_back(f);
                    break;
                }
                case BoxElem:{
                    QPoint Point (50*(i-1),50*(j)-ZERO_Y_REL);
                    Box* b = new Box(Point);
                    _inGame->push_back(b);
                    break;
                }
            }
        }
    }

    /******************************************************************
     * Bot Generator
     * *****************************************************************/

    for (int k(0);k<_bots->size();k++){
        //_bots[k] = nullptr;
    }
    _bots->clear();
   for (int i(1000);i<9001;i+=distBetweenBots){
        QPoint p(i,200);
        MiniBot* b = new MiniBot(p,_element);
        b->setIsOnFloor(true);
        _bots->push_back(b);
    }
    QPoint p(500,200);
    MiniBot* b = new MiniBot(p,_element);
    b->setIsOnFloor(true);
    _bots->push_back(b);
    b = nullptr;
    delete b;
    QPoint p2(10300,300);
    Newton* botNewton = new Newton(p2,_element);
    botNewton->setNewtonGif();
    _bots->push_back(botNewton);
}

void Data::playerFall()
{
    _player->setPosition({_player->getPosition().x()-150,200});
}

bool Data::BotIsDead(int i)
{
    bool retval;
    if((*_bots)[i]->getId()==newton)
    {
        retval = true;
    }
    std::vector<MiniBot*> tmp = *_bots;
    _bots->clear();
    for(int j(0);j<tmp.size();j++){
        if(j!=i){
            _bots->push_back(tmp[j]);
        }else{
            delete tmp[j];
        }
    }
    return retval;
}

 void Data::dataUpdate()
{
    SigUpdate();
}


