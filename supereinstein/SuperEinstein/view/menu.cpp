#include "menu.h"
#include <cmath>

Menu::Menu(QWidget* parent) : View(800,300,parent)
{

    QFont* fLabel = new QFont( "Arial", 10);
    _menuIsShow = true;

    /*********************************************
     * start button settings
     * *******************************************/
    _start = new QPushButton(this);
    _start->setFont(*fLabel);
    _start->setText("Start");
    _start->setFixedSize(600,50);
    _start->move(100,0);
    _start->setStyleSheet("background-color: rgb(0, 255, 0)");

    /*********************************************
     * sound slider settings
     * *******************************************/
    _sound = new QSlider(Qt::Horizontal,this);
    _sound->setFont(*fLabel);
    _sound->setFixedSize(600,50);
    _sound->move(100,100);
    _sound->setMinimum(0);
    _sound->setMaximum(100);
    _sound->setTickPosition(QSlider::TicksRight);
    _sound->setSliderPosition(100);
    _sound->setStyleSheet("background-color: rgb(255, 255, 255)");

    /*********************************************
     * show command button settings
     * *******************************************/
    _showCommand = new QPushButton(this);
    _showCommand->setFont(*fLabel);
    _showCommand->setText("Command");
    _showCommand->move(100,200);
    _showCommand->setFixedSize(600,50);
    _showCommand->setStyleSheet("background-color: rgb(0, 255, 255)");

    /*********************************************
     * difficulty command  settings
     * *******************************************/
    _difLab = new QLabel(this);
    _difLab->setFixedSize(90,150);
    _difLab->setStyleSheet("background-color:lightgrey;qproperty-alignment: AlignTop AlignLeft");
    _difLab->move(0,0);
    _difLab->setText("\t Choose only one difficulty (you must choose for start the game)");

    /*********************************************
     * reset button settings
     * *******************************************/
    _reset = new QPushButton(this);
    _reset->setFont(*fLabel);
    _reset->setText("Reset");
    _reset->setFixedSize(600,50);
    _reset->move(100,300);
    _reset->setStyleSheet("background-color: rgb(0, 0, 255)");



     _easy = new QCheckBox("easy",_difLab);
     _medium = new QCheckBox("medium",_difLab);
     _hard = new QCheckBox("hard",_difLab);

     /***********************************************
      *  END menu
      * *********************************************/
     _endLab = new QLabel();
     QMovie* movie = new QMovie(":/texture/menu/end.gif");
     _endLab->setMovie(movie);
     _endLab->setFixedSize(400,400);
     _endLab->move(200,150);
     _endLab->setWindowIcon(QIcon(":/texture/icon.png"));

    /*********************************************
     * display command settings
     * *******************************************/

    QFont* fLabel2 = new QFont( "Arial", 20,QFont::Bold);
   _listCommand = new QLabel();
   _listCommand->setFont(*fLabel2);
   _listCommand->setFixedSize(400,400);
   _listCommand->move(200,150);
   _listCommand->setAlignment(Qt::AlignHCenter);
   _listCommand->setStyleSheet("background-image: url(:/texture/menu/CommandMenu.png)");
   _listCommand->setWindowIcon(QIcon(":/texture/icon.png"));

   QString commands = "\n\n a : walk left \n d : walk right \n space : jump \n Shift : run \n Bot are dangerous \n jump on them for kill";
   _listCommand->setText(commands);


    /*******************************************************************************
     * connections
     * ****************************************************************************/
    QObject::connect(_start,SIGNAL(clicked()),this,SLOT(sloStart()));
    QObject::connect(_sound,&QSlider::valueChanged,this,&Menu::volumeChanged);
    QObject::connect(_showCommand,&QPushButton::clicked,_listCommand,&QLabel::show);
    QObject::connect(_easy,SIGNAL(clicked()),this,SLOT(easy()));
    QObject::connect(_medium,SIGNAL(clicked()),this,SLOT(medium()));
    QObject::connect(_hard,SIGNAL(clicked()),this,SLOT(hard()));
    QObject::connect(_reset,SIGNAL(clicked()),this,SLOT(sloReset()));


    delete  fLabel;
    delete fLabel2;

}

void Menu::setDiffIsChoose(bool b)
{
 _diffIsChoose = b;
}

void Menu::sloStart()
{

    /***************************************
     * hide buttons but still display the
     * sound slider when the game is
     * working
     * **************************************/
    if(_diffIsChoose){
        emit sigStart();
        _start->hide();
        _showCommand->hide();
        _reset->hide();
        _menuIsShow = false;
        _endLab->movie()->stop();
        _endLab->hide();
        }
    this->update();

}

void Menu::volumeChanged()
{
    emit volume(_sound->sliderPosition());
}

void Menu::showMenu()
{
    _menuIsShow = true;


    /*********************************************
     * start button settings
     * *******************************************/
    _start->show();

    /*********************************************
     * sound slider settings
     * *******************************************/
    _sound->setFixedSize(600, 50);

    /*********************************************
     * show command button settings
     * *******************************************/
    _showCommand->show();

    /*********************************************
     * show reset button settings
     * *******************************************/
    _reset->show();

    /*******************************************************************
     * Show difficulty menu choice
     * *****************************************************************/
    if(!_diffIsChoose){
        _difLab->show();
        _easy->setChecked(false );
        _medium->setChecked(false );
        _hard->setChecked(false );
    }
    this->update();
    this->raise();
}

void Menu::diffIschoose(UtilityGame::difficulty d)
{
    emit sigDiff(d);
    _difLab->hide();
    _diffIsChoose = true;
}

void Menu::easy()
{
    diffIschoose(UtilityGame::easy);
}

void Menu::medium()
{
    diffIschoose(UtilityGame::medium);
}

void Menu::hard()
{
    diffIschoose(UtilityGame::hard);
}

void Menu::update(double sx , double sy )
{

    if(_menuIsShow){
         this->setFixedSize(sx*800,sy*500);
        this->move(int((sx * 100.0)),int ((sy * 100.0)));
    }else{
        this->move(sx * 900,0);
        this->setFixedSize(sx * 100,sy * 50);
    }

    QFont* fLabel = new QFont( "Arial",sx * 10);



    /*********************************************
     * start button settings
     * *******************************************/
    _start->move(100*sx,0);
    _start->setFixedSize(sx*600,sy*50);
    _start->setFont(*fLabel);

    /*********************************************
     * sound slider settings
     * *******************************************/
    if(_menuIsShow){
        _sound->setFixedSize(sx*600,sy* 50);
        _sound->move(sx* 100,sy* 100);
        _sound->setSliderPosition(_sound->sliderPosition());
        _sound->setStyleSheet("background-color: rgb(255, 255, 255)");
    }else{
        _sound->setFixedSize(sx * 90,sy * 40);
        _sound->move(sx * 5,sy * 5);
    }

    /*********************************************
     * show command button settings
     * *******************************************/
    _showCommand->setFixedSize(sx*600,sy*50);
    _showCommand->move(sx*100,sy*200);
    _showCommand->setFont(*fLabel);

    /*********************************************
     * reset button settings
     * *******************************************/
    _reset->move(100*sx,300);
    _reset->setFixedSize(sx*600,sy*50);
    _reset->setFont(*fLabel);


    /*******************************************************************
     * Show difficulty menu choice
     * *****************************************************************/
    _difLab->setFixedSize(sx*600,sy*50);
    _difLab->move(100*sx,400);
    _difLab->setFont(*fLabel);

    QSize nSize (sx*70,sy*30);
    _easy->setFixedSize(nSize);
    _medium->setFixedSize(nSize);
    _hard->setFixedSize(nSize);

    _easy->move(10,sy*20);
    _medium->move(sx*110,sy*20);
    _hard->move(sx*210,sy*20);

    _easy->setFont(*fLabel);
    _medium->setFont(*fLabel);
    _hard->setFont(*fLabel);

    View::update();
}

void Menu::sloReset()
{
    _diffIsChoose = false;
    _difLab->show();
    _easy->setChecked(false );
    _medium->setChecked(false );
    _hard->setChecked(false );
    emit sigReset();
}

void Menu::end()
{
    _endLab->show();
    _endLab->movie()->start();
    sloReset();

}

