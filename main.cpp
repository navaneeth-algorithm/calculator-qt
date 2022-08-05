#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculator calculator;



    calculator.setWindowTitle("Calculator");
    calculator.setMinimumSize(QSize(220,260));
    calculator.setMaximumSize(QSize(220,260));


    //show calculator gui
    calculator.show();
    return a.exec();
}
