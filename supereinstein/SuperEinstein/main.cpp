#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    Controller w;
    w.show();
    return a.exec();
}
