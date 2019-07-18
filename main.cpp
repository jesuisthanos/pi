#include <QApplication>
#include "led.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    LED led;
    led.show();

    return app.exec();
}
