#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

class View : public QWidget
{
        Q_OBJECT
    protected:
        int _XLength;
        int _YLength;

    public:
        View(int x = 0,int y = 0,QWidget *parent = nullptr);
        ~View();


};

#endif // VIEW_H
