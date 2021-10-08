#include "WatchMockupWidget.h"

#include <cstdint>
#include <string.h>
#include <QtCore>
#include <QtWidgets>

#include "lvgl.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/DefaultScreenGraph.h"
#include "components/ComponentContainer.h"
#include "BootloaderVersion.h"


#define SCREEN_WIDTH           240
#define SCREEN_HEIGHT          240
#define SCREEN_LEFT            66
#define SCREEN_TOP             74

#define BUTTON_WIDTH           40
#define BUTTON_HEIGHT          100
#define BUTTON_LEFT            0
#define BUTTON_TOP             150

#define SWIPE_THRESHOLD        0.3
#define LONG_TAP_THRESHOLD     800
#define DOUBLE_TAP_THRESHOLD   200



WatchMockupWidget *WatchMockupWidget::_mainWidget = nullptr;


WatchMockupWidget::~WatchMockupWidget()
{
        // clean up
        delete _screenGraph;
        delete[] _lvglDrawBuffer;
        delete _backgroundPixmap;
        delete _screenImage;
        delete _components;
}


WatchMockupWidget *WatchMockupWidget::create(QWidget *parent)
{
        if (!_mainWidget)
                _mainWidget = new WatchMockupWidget(parent);
        return _mainWidget;
}


void WatchMockupWidget::setSizeMode(SizeMode value)
{
        if (value != _sizeMode)
        {
                _sizeMode = value;
                resizeWatch();
        }
}


void WatchMockupWidget::setFullRefreshDirection(FullRefreshDirection value)
{
        (void)value;
}


void WatchMockupWidget::resizeEvent(QResizeEvent *event)
{
        QWidget::resizeEvent(event);
        resizeWatch();
}


void WatchMockupWidget::paintEvent(QPaintEvent *event)
{
        // make sure that the current screen is updated
        Screen *screen = _screenGraph->currentScreen();
        if (screen)
                screen->refresh();

        // draw the background
        QPainter painter(this);
        painter.fillRect(this->rect(), QColor(128, 128, 128));
        painter.drawPixmap(_backgroundRect, *_backgroundPixmap, _backgroundPixmap->rect());

        // draw the current screen's content
        painter.drawImage(_screenRect, *_screenImage, _screenImage->rect());

        // done
        event->accept();
}


void WatchMockupWidget::mousePressEvent(QMouseEvent *event)
{
        // only consider it a tap when it's inside the screen area
        if (_screenRect.contains(event->pos()))
        {
                _mouseButtonDown = true;
                _mouseButtonDownPos = mapScreenPosToDisplayPos(event->pos());
                _mouseButtonDownTimer.start();
        }
        else if (_buttonRect.contains(event->pos()))
                _screenGraph->handleButtonPress();
        QWidget::mousePressEvent(event);
}


void WatchMockupWidget::mouseMoveEvent(QMouseEvent *event)
{
        // if the mouse button is down but the cursor leaves the screen, it's considered a release event
        if (_mouseButtonDown && !_screenRect.contains(event->pos()))
        {
                _mouseButtonDown = false;
                checkForSwipe(mapScreenPosToDisplayPos(event->pos()));
        }
        QWidget::mouseMoveEvent(event);
}


void WatchMockupWidget::mouseReleaseEvent(QMouseEvent *event)
{
        if (_mouseButtonDown)
        {
                _mouseButtonDown = false;
                QPoint releasePos = mapScreenPosToDisplayPos(event->pos());
                if (checkForSwipe(releasePos))
                        _lastClickTimer = QElapsedTimer();
                else
                {
                        // long tap?
                        if (_mouseButtonDownTimer.elapsed() >= LONG_TAP_THRESHOLD)
                        {
                                _screenGraph->handleLongTap();
                                _lastClickTimer = QElapsedTimer();
                        }
                        else
                        {
                                // double tap?
                                if (_lastClickTimer.isValid() && (_lastClickTimer.elapsed() <= DOUBLE_TAP_THRESHOLD))
                                {
                                        _screenGraph->handleDoubleTap();
                                        _lastClickTimer = QElapsedTimer();
                                }
                                else
                                {
                                        // just a single tap
                                        _screenGraph->handleTap();
                                        _lastClickTimer.start();
                                }
                        }
                }
        }
        QWidget::mouseReleaseEvent(event);
}


void WatchMockupWidget::onFlushDisplay(const lv_area_t *area, lv_color_t *pixels)
{
        // copy the pixels of the given area into the screen image
        lv_color_t *src = pixels;
        int ppl = area->x2 - area->x1 + 1;
        for (int y = area->y1; y <= area->y2; y++)
        {
                uchar *dst = _screenImage->scanLine(y) + 2 * area->x1;
                memcpy(dst, src, static_cast<size_t>(2 * ppl));
                src += ppl;
        }

        // notify lvgl that the copying's done
        lv_disp_flush_ready(&_lvglDisplayDriverDesc);

        // the widget needs to be redrawn
        update();
}


void WatchMockupWidget::onTouchpadRead(lv_indev_data_t *data)
{
        if (_mouseButtonDown)
        {
                data->state = LV_INDEV_STATE_PR;
                data->point.x = static_cast<lv_coord_t>(_mouseButtonDownPos.x());
                data->point.y = static_cast<lv_coord_t>(_mouseButtonDownPos.y());
        }
        else
                data->state = LV_INDEV_STATE_REL;
}


void WatchMockupWidget::resizeWatch()
{
        // the scale depends on the selected size mode
        double scale;
        switch (_sizeMode)
        {
        case SizeMode::Fixed2x:
                scale = 2.0;
                break;
        case SizeMode::StretchToFit:
                {
                        double scaleX = static_cast<double>(this->width()) / static_cast<double>(_backgroundPixmap->width());
                        double scaleY = static_cast<double>(this->height()) / static_cast<double>(_backgroundPixmap->height());
                        scale = (scaleX < scaleY) ? scaleX : scaleY;
                }
                break;
        default:
                scale = 1.0;
                break;
        }

        // get the new size and position of the background image
        int newBgWidth = static_cast<int>(scale * static_cast<double>(_backgroundPixmap->width()));
        int newBgHeight = static_cast<int>(scale * static_cast<double>(_backgroundPixmap->height()));
        int newBgX = (this->width() - newBgWidth) / 2;
        int newBgY = (this->height() - newBgHeight) / 2;
        _backgroundRect = QRect(newBgX, newBgY, newBgWidth, newBgHeight);

        // get the new display area
        _screenRect = QRect(newBgX + static_cast<int>(scale * SCREEN_LEFT),
                            newBgY + static_cast<int>(scale * SCREEN_TOP),
                            static_cast<int>(scale * SCREEN_WIDTH),
                            static_cast<int>(scale * SCREEN_HEIGHT));

        // get the new button area
        _buttonRect = QRect(newBgX + static_cast<int>(scale * BUTTON_LEFT),
                            newBgY + static_cast<int>(scale * BUTTON_TOP),
                            static_cast<int>(scale * BUTTON_WIDTH),
                            static_cast<int>(scale * BUTTON_HEIGHT));

        // make sure to redraw the widget with these new settings
        update();
}


QPoint WatchMockupWidget::mapScreenPosToDisplayPos(const QPoint &pos)
{
        double sx = static_cast<double>(SCREEN_WIDTH) / static_cast<double>(_screenRect.width());
        double sy = static_cast<double>(SCREEN_HEIGHT) / static_cast<double>(_screenRect.height());
        return QPoint(static_cast<int>(static_cast<double>(pos.x() - _screenRect.x()) * sx),
                      static_cast<int>(static_cast<double>(pos.y() - _screenRect.y()) * sy));
}


bool WatchMockupWidget::checkForSwipe(const QPoint &releasePos)
{
        // calculate the movement, relative to the screen size
        double dx = static_cast<double>(releasePos.x() - _mouseButtonDownPos.x()) / static_cast<double>(_screenRect.width());
        double dy = static_cast<double>(releasePos.y() - _mouseButtonDownPos.y()) / static_cast<double>(_screenRect.height());

        // check for a swipe
        Screen::SwipeDirection direction = Screen::SwipeDirection::None;
        if (dx > SWIPE_THRESHOLD)
                direction = Screen::SwipeDirection::Right;
        else if (dx < -SWIPE_THRESHOLD)
                direction = Screen::SwipeDirection::Left;
        else
        {
                if (dy > SWIPE_THRESHOLD)
                        direction = Screen::SwipeDirection::Down;
                else if (dy < -SWIPE_THRESHOLD)
                        direction = Screen::SwipeDirection::Up;
        }

        // notify the screen graph
        bool swipe = (direction != Screen::SwipeDirection::None);
        if (swipe)
                _screenGraph->handleSwipe(direction);

        // done
        return swipe;
}


WatchMockupWidget::WatchMockupWidget(QWidget *parent)
        : QWidget(parent)
{
        // load the background image from the resources
        _backgroundPixmap = new QPixmap(":/images/watch-background");

        // make sure that the background pixmap can be displayed in full
        setMinimumSize(_backgroundPixmap->width(), _backgroundPixmap->height());

        // create the buffer image that lvgl flushes to
        _screenImage = new QImage(SCREEN_WIDTH, SCREEN_HEIGHT, QImage::Format_RGB16);
        _screenImage->fill(0);

        // create the draw buffer for lvgl
        _lvglDrawBuffer = new lv_color_t[SCREEN_WIDTH * SCREEN_HEIGHT / 10];
        lv_disp_buf_init(&_lvglDrawBufferDesc, _lvglDrawBuffer, nullptr, SCREEN_WIDTH * SCREEN_HEIGHT / 10);

        // init the display driver
        lv_disp_drv_init(&_lvglDisplayDriverDesc);
        _lvglDisplayDriverDesc.flush_cb = lvglFlushDisplay;
        _lvglDisplayDriverDesc.buffer = &_lvglDrawBufferDesc;
        _lvglDisplayDriverDesc.hor_res = SCREEN_WIDTH;
        _lvglDisplayDriverDesc.ver_res = SCREEN_HEIGHT;
        if (!lv_disp_drv_register(&_lvglDisplayDriverDesc))
                qWarning("Unable to register display driver.");

        // init the input device driver
        lv_indev_drv_init(&_lvglInputDriverDesc);
        _lvglInputDriverDesc.type = LV_INDEV_TYPE_POINTER;
        _lvglInputDriverDesc.read_cb = lvglTouchpadRead;
        if (!lv_indev_drv_register(&_lvglInputDriverDesc))
                qWarning("Unable to register input device driver.");

        // init current status
        _mouseButtonDown = false;
        _lastRefreshTicks = 0;
        _sizeMode = SizeMode::Fixed1x;

        // create the component container
        _components = new ComponentContainer();

        // set the bootloader version
        Pinetime::BootloaderVersion::SetVersion(0x00010000);

        // create the screen graph
        _screenGraph = new DefaultScreenGraph(this, _components);

        // start the tick timer
        connect(&_lvglTimer, SIGNAL(timeout()), this, SLOT(lvglTimerTriggered()));
        _lvglTimer.start(5);
}


void WatchMockupWidget::lvglFlushDisplay(lv_disp_drv_t *driverDesc, const lv_area_t *area, lv_color_t *pixels)
{
        (void)driverDesc;
        if (_mainWidget)
                _mainWidget->onFlushDisplay(area, pixels);
}


bool WatchMockupWidget::lvglTouchpadRead(lv_indev_drv_t *driverDesc, lv_indev_data_t *data)
{
        (void)driverDesc;
        if (_mainWidget)
                _mainWidget->onTouchpadRead(data);
        return false;
}


void WatchMockupWidget::lvglTimerTriggered()
{
        // give lvgl some processing time
        lv_task_handler();
        lv_tick_inc(5);

        // refresh twice a second
        uint32_t ticks = lv_tick_get();
        if ((ticks - _lastRefreshTicks) >= 500)
        {
                _components->dateTime()->UpdateTime(0);
                _screenGraph->handleRefresh();
                _lastRefreshTicks = ticks;
        }
}
