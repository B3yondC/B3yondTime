#ifndef WATCHMOCKUPWIDGET_H
#define WATCHMOCKUPWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPoint>
#include <QRect>
#include <QElapsedTimer>

#include "lvgl.h"

#include "displayapp/SystemInterface.h"

class QImage;
class QPixmap;
class QResizeEvent;
class QPaintEvent;
class QMouseEvent;

class ComponentContainer;
class ScreenGraph;



class WatchMockupWidget : public QWidget, public SystemInterface
{
        Q_OBJECT

public:

        enum class SizeMode
        {
                Fixed1x,
                Fixed2x,
                StretchToFit
        };


        ~WatchMockupWidget() override;

        static WatchMockupWidget *create(QWidget *parent = nullptr);

        ComponentContainer *components() { return _components; }

        SizeMode sizeMode() const { return _sizeMode; }

        void setSizeMode(SizeMode value);

        void setFullRefreshDirection(FullRefreshDirection value) override;

protected:

        void resizeEvent(QResizeEvent *event) override;
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

private:

        lv_disp_buf_t _lvglDrawBufferDesc;
        lv_color_t *_lvglDrawBuffer;
        lv_disp_drv_t _lvglDisplayDriverDesc;
        lv_indev_drv_t _lvglInputDriverDesc;
        QTimer _lvglTimer;
        uint32_t _lastRefreshTicks;
        QPixmap *_backgroundPixmap;
        QRect _backgroundRect;
        QRect _screenRect;
        QRect _buttonRect;
        QImage *_screenImage;
        bool _mouseButtonDown;
        QPoint _mouseButtonDownPos;
        QElapsedTimer _mouseButtonDownTimer;
        QElapsedTimer _lastClickTimer;
        ScreenGraph *_screenGraph;
        ComponentContainer *_components;

        SizeMode _sizeMode;

        void onFlushDisplay(const lv_area_t *area, lv_color_t *pixels);
        void onTouchpadRead(lv_indev_data_t *data);

        void resizeWatch();
        QPoint mapScreenPosToDisplayPos(const QPoint &pos);
        bool checkForSwipe(const QPoint &releasePos);

        static WatchMockupWidget *_mainWidget;

        explicit WatchMockupWidget(QWidget *parent);

        static void lvglFlushDisplay(lv_disp_drv_t *driverDesc, const lv_area_t *area, lv_color_t *pixels);
        static bool lvglTouchpadRead(lv_indev_drv_t *driverDesc, lv_indev_data_t *data);

private slots:

        void lvglTimerTriggered();
};

#endif // WATCHMOCKUPWIDGET_H
