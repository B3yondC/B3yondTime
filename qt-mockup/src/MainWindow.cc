#include "MainWindow.h"

#include <QtCore>
#include <QtWidgets>

#include "WatchMockupWidget.h"

#include "components/ComponentContainer.h"



MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
        // create the watch mockup
        _watchWidget = WatchMockupWidget::create();

        // create the manipulation tab widget
        QTabWidget *tabWidget = new QTabWidget();
        tabWidget->setTabPosition(QTabWidget::East);

        // create the main tab
        QVBoxLayout *mainTabLayout = new QVBoxLayout();
        mainTabLayout->addWidget(_watchWidget->components()->battery()->mockup_createWidget());
        mainTabLayout->addSpacing(16);
        mainTabLayout->addWidget(_watchWidget->components()->ble()->mockup_createWidget());
        mainTabLayout->addWidget(_watchWidget->components()->firmwareValidator()->mockup_createWidget());
        mainTabLayout->addSpacing(16);
        mainTabLayout->addWidget(_watchWidget->components()->dateTime()->mockup_createWidget());
        mainTabLayout->addSpacing(16);
        mainTabLayout->addWidget(_watchWidget->components()->motion()->mockup_createWidget());
        mainTabLayout->addStretch(1);
        QWidget *mainTab = new QWidget();
        mainTab->setLayout(mainTabLayout);
        tabWidget->addTab(mainTab, "Main");

        // create the settings tab
        QVBoxLayout *settingsLayout = new QVBoxLayout();
        settingsLayout->addWidget(_watchWidget->components()->settings()->mockup_createWidget());
        settingsLayout->addStretch(1);
        QWidget *settingsTab = new QWidget();
        settingsTab->setLayout(settingsLayout);
        tabWidget->addTab(settingsTab, "Settings");

        // create the main layout
        QHBoxLayout *mainLayout = new QHBoxLayout();
        mainLayout->addWidget(_watchWidget, 1);
        mainLayout->addWidget(tabWidget);
        QWidget *mainWidget = new QWidget();
        mainWidget->setLayout(mainLayout);
        setCentralWidget(mainWidget);
}
