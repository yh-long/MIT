#include "simple_musicplayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simple_musicplayer w;
    w.show();
    return a.exec();
}
