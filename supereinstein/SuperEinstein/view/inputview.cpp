#include "inputview.h"
#include <QDebug>

static int dpress = 0;
static int drele = 0;

InputView::InputView(QWidget* parent) : View(0,0,parent)
{
    this-> setFocusPolicy(Qt :: StrongFocus);
    this->setFixedSize(100,100);
    this->move(0,0);

    this->setAttribute(Qt::WA_KeyCompression);
}

void InputView::keyPressEvent(QKeyEvent* e)
{
    QString _debMessage;
    QString onKey =e->text();
    if (onKey=='a'){
        emit UpPushed(UiEvent::a);
    }
    if (onKey=='d'){
       emit UpPushed(UiEvent::d);
        dpress++;
    }
    if ((onKey==' ')&&!(e->isAutoRepeat())){
       emit UpPushed(UiEvent::space);
    }
    if (onKey=='A'){
       emit UpPushed(UiEvent::A);
    }
    if (onKey=='D'){
       emit UpPushed(UiEvent::D);
    }
    if(e->key()==Qt::Key_Escape){
        emit UpPushed(UiEvent::esc);
    }

    QWidget::keyPressEvent(e);
}

void InputView::keyReleaseEvent(QKeyEvent* e)
{
    QString _debMessage;
    emit UpPushed(no);
    QString onKey =e->text();
    if (onKey=='d'){
        drele++;
    }
}



InputView::~InputView()
{

}

void InputView::sloKeyPressed(QKeyEvent* e)
{
    this->keyPressEvent(e);
}

void InputView::sloKeyReleased(QKeyEvent* e)
{
    this->keyReleaseEvent(e);
}


