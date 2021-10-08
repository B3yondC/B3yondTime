#include <QApplication>

#include "lvgl.h"
#include "MainWindow.h"



int main(int argc, char **argv)
{
        QApplication app(argc, argv);
        lv_init();

        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
}
