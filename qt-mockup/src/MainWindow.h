#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class WatchMockupWidget;



class MainWindow : public QMainWindow
{
        Q_OBJECT

public:

        MainWindow(QWidget *parent = nullptr);

private:

        WatchMockupWidget *_watchWidget;
};

#endif // MAINWINDOW_H
