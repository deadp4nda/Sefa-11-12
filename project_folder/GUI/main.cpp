#include <QDebug>
#include <QApplication>
#include <Mongolib>
#include <QMainWindow>
#include <achim.h>

using namespace Mongo;

int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    MngThManager mgr;
    MngFileManager fMgr;
    Achim Fensta;
    Fensta.show();
    return app.exec();
}
