#include "oblivion.hpp"
#include "qcontainerfwd.h"

int main (int argc, char **argv) {

    QApplication a(argc, argv);
    Oblivion ob(argc, argv);
    a.exec();
}
