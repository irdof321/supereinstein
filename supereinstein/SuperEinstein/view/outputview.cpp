#include "outputview.h"
#include <QDir>
#include <QTimer>

int loop = 0;

OutputView::OutputView(Data* data, QWidget* parent): View(SCREEN_X_SIZE,SCREEN_Y_SIZE,parent), _data(data)
{

    this->setGeometry(500,150,_XLength,_YLength);

    _heart = new QPixmap(":/texture/personn/heart.png");
    _gameOverPixmap = new QPixmap(":/texture/menu/GameOver.png");
    _touch = new QLabel(this);
    _touch->setFixedSize(50,50);
    _touch->setMovie(new QMovie(":/texture/personn/excla.gif"));
    _onMenu = true;
    _showgameOver = false;
    _timer = new QTimer();
    this->setWindowIcon(QIcon(":/texture/icon.png"));
    _scaleXFromBeg = double(this->width())/double(SCREEN_X_SIZE);
    _scaleYFromBeg =  double(this->height())/double(SCREEN_Y_SIZE);


    /******************************************************
     * font png for the font
     * ****************************************************/
     _Font = new QPixmap(":/texture/fontObject/font.png");
     /*******************************************************
      * Menu
      * ******************************************************/
      _menu = new Menu(this);
      _menu->move(100,100);
      _menu->setFixedSize(800,300);
      _menu->show();

      /*************************************************************************
       * connections
       * ***********************************************************************/
      QObject::connect(_menu,&Menu::sigStart,this,&OutputView::sloStart);
      QObject::connect(_menu,SIGNAL(volume(int)),this,SIGNAL(volume(int)));
      QObject::connect(_menu,SIGNAL(sigReset()),this,SLOT(showMenu()));
      QObject::connect(_menu,SIGNAL(sigReset()),this,SIGNAL(sigReset()));
      QObject::connect(this,SIGNAL(sigShowMenu()),_menu,SLOT(showMenu()));
      QObject::connect(this,SIGNAL(sigEnd()),_menu,SLOT(end()));
      QObject::connect(_timer,SIGNAL(timeout()),this,SLOT(showMenu()));
      QObject::connect(_menu,SIGNAL(sigDiff(UtilityGame::difficulty)),this,SIGNAL(sigDiff(UtilityGame::difficulty)));
}

OutputView::~OutputView()
{

}

void OutputView::keyPressEvent(QKeyEvent* e)
{
    emit sigKeyPressed(e);
}

void OutputView::keyReleaseEvent(QKeyEvent* e)
{
    emit sigKeyRleased(e);
}

void OutputView::sloStart()
{
    emit sigStart();
    _onMenu = false;
}

void OutputView::showMenu()
{
    _timer->stop();
    _menu->raise();
    emit sigShowMenu();
    _menu->update(_scaleXFromBeg,_scaleYFromBeg);
    _onMenu = true;
    _showgameOver = false;
}

void OutputView::gameOver()
{
    _timer->start(5000);
    _menu->setDiffIsChoose(false);
    _showgameOver = true;
}


void OutputView::paintEvent(QPaintEvent* event)
{

    /**********************************************************
     *                    variables
     * ********************************************************/
    Player* _player = _data->getPlayer();
    std::vector<BaseElem*> _objects = _data->getBaseElem();

    _scaleXFromBeg = double(this->width())/double(SCREEN_X_SIZE);
    _scaleYFromBeg =  double(this->height())/double(SCREEN_Y_SIZE);

    _menu->update(_scaleXFromBeg,_scaleYFromBeg);



    if(_player!=nullptr){

        /***************************************************************
         * maxDisplay and minDisplay is used for know wich part of the font
         * and wich object should be on the screen
         * the screen is long of _Xlength and the player is always
         * at x = 150 (relative to the outputview)
         * **************************************************************/
        int xplacePlayer = 150;
        int maxDisplayX =(_player->getPosition()).x()+_XLength-xplacePlayer;
        int minDisplayX = (_player->getPosition()).x()-xplacePlayer;

        if(minDisplayX<=64){                                //the screen can display the empty font
            minDisplayX = 64;
            xplacePlayer = (_player->getPosition()).x()-64;
            maxDisplayX-=64;
        }
        if(maxDisplayX>=11000){                             //the screen can display the empty font
            maxDisplayX = 11000;
            minDisplayX = maxDisplayX -_XLength;

          xplacePlayer = 1000-(11000-(_player->getPosition()).x());
        }

        /************************** Font *******************************/
        QPainter* paintFont = new QPainter(this);
        paintFont->scale(_scaleXFromBeg,0.8* _scaleYFromBeg );
        paintFont->drawPixmap(-minDisplayX,0,*_Font);
        delete paintFont;
        /***************************************************************/


        /******************************************************************
         *          draw all the lements and personns
         * ****************************************************************/
       QPainter* painter = new QPainter(this);
       painter->scale(_scaleXFromBeg,_scaleYFromBeg);

       /***************draw baseElem **************************************/
        for (std::size_t i (0); i<_objects.size();++i) {
            if((_objects[i]->getPosition().x()>minDisplayX)||
            (_objects[i]->getPosition().x()<maxDisplayX)){
                QPixmap* PixFloor = _objects[i]->getPixmap();
                painter->drawPixmap((_objects[i]->getPosition().x()-minDisplayX),(_objects[i]->getPosition().y()),*PixFloor);
            }

        }

        /************************* draw Player ****************************************/
        QLabel* labePlayer = _player->getLabel();
        labePlayer->setParent(this);


        if ((labePlayer->movie()->state()!=QMovie::Running)&&!(_onMenu)){                           // be sure that player is not turning if the menu os on
           labePlayer->movie()->start();
        }else if((labePlayer->movie()->state()!=QMovie::Paused)&&(_onMenu)){
            labePlayer->movie()->stop();
        }
        _player->setScaledSize({int(_scaleXFromBeg*X_SIZE_PLAYER),int(_scaleYFromBeg*Y_SIZE_PLAYER)});  // change size of player if the size of screen changed
        labePlayer->show();
        labePlayer->move(_scaleXFromBeg*xplacePlayer,_scaleYFromBeg * _player->getPosition().y());



        /***************************** draw bots ******************************************/
        for(auto elem : _data->getBot()){
            int y = elem->getYlength(); int x = elem->getXlength();
            elem->setScaledSize({int(_scaleXFromBeg*x),int(_scaleYFromBeg*y)});
            QLabel* labelBot = elem->getLabel();
            labelBot->setParent(this);
            labelBot->movie()->start();
            labelBot->move(_scaleXFromBeg*(elem->getPosition().x()-minDisplayX),_scaleYFromBeg*elem->getPosition().y());
            labelBot->show();
            labelBot = nullptr;
            delete  labelBot;
        }

        /********** draw lifes ****************************/
        for (int i(0); i<_player->getLife();i++){
            painter->drawPixmap(20*(i),10,*_heart);
        }
        if(_showgameOver){
            painter->drawPixmap(xplacePlayer+50,100,*_gameOverPixmap);
        }
        delete painter;
        /******************************************************************
         *  draw an eclamation point when the player is touched by an ennemy
         * and if he can t be touched
         * *******************************************************************/
        if(_player->getIsTouch()){
                if(_touch->movie()->isValid()){
                    _touch->movie()->start();
                    _touch->move(xplacePlayer,_player->getPosition().y()-50);
                    _touch->show();
                    _touch->raise();
                }
        }else if(!_player->getIsTouch()){
                _touch->movie()->stop();
                _touch->close();
            }

        }

    // draw grid
       /* QPainter* p = new QPainter(this);
        QPen* b = new QPen();
        b->setColor(QColor(0,0,0));
        b->setWidth(5);
        p->setPen(*b);
        for (int l(0);l<30;l++)
        {

            p->drawLine(0,l*50,1000,l*50);
            p->drawLine(l*50,0,l*50,1500);
        }*/

}



