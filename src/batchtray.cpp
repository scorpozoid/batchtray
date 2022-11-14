#include "batchtraymainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BatchTrayMainWindow w;
    w.setCommand("C:\\home\\ark\\devel\\nig\\dfpost\\db.git\\src\\utils\\herzutils\\herzprog\\pgsql\\herzprog-pgsql.bat");
    w.show();
    return a.exec();
}
