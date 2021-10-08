#include "DigitalWatchFace.h"

#include <lvgl/lvgl.h>

#include "displayapp/fonts/FontBoldDigits96.h"
#include "displayapp/fonts/font_dvs_ascii_16.h"
#include "displayapp/fonts/FontAwesomeSolid24.h"


#define TIME_OFFSET_X   0
#define TIME_OFFSET_Y   -64

#define TIME_COLOR      0x005000


LV_IMG_DECLARE(image_digital_watchface_bg);


using namespace Pinetime::Controllers;



DigitalWatchFace::DigitalWatchFace(ScreenGraph *screenGraph, ComponentContainer *components)
        : WatchFace(screenGraph, components)
{
        // set the watch's background image
        lv_obj_t* backgroundImage = lv_img_create(lv_scr_act(), nullptr);
        lv_img_set_src(backgroundImage, &image_digital_watchface_bg);
        lv_obj_align(backgroundImage, nullptr, LV_ALIGN_CENTER, 0, 0);

        // start with the colon label
        _colonLabel = createLabel(&FontBoldDigits96, lv_color_hex(TIME_COLOR), LV_LABEL_ALIGN_CENTER, false);
        lv_label_set_text_static(_colonLabel, ":");
        lv_obj_align(_colonLabel, nullptr, LV_ALIGN_CENTER, TIME_OFFSET_X, TIME_OFFSET_Y);

        // create the hour label
        _hourLabel = createLabel(&FontBoldDigits96, lv_color_hex(TIME_COLOR), LV_LABEL_ALIGN_RIGHT, false);
        lv_label_set_text_static(_hourLabel, "00");
        lv_obj_align(_hourLabel, _colonLabel, LV_ALIGN_OUT_LEFT_MID, -2, 0);

        // create the minute label
        _minuteLabel = createLabel(&FontBoldDigits96, lv_color_hex(TIME_COLOR), LV_LABEL_ALIGN_LEFT, false);
        lv_label_set_text_static(_minuteLabel, "00");
        lv_obj_align(_minuteLabel, _colonLabel, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

        // create the date label
        _dateLabel = createLabel(&font_dvs_ascii_16, lv_color_hex(TIME_COLOR), LV_LABEL_ALIGN_CENTER, true);
        lv_obj_align(_dateLabel, _colonLabel, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);

        // create the lock symbol
        _lockSymbol = createLabel(&FontAwesomeSolid24, lv_color_hex(0x606060), LV_LABEL_ALIGN_CENTER, false);

        // update everything
        dayChanged(true, true);
        timeChanged(true, true);
        lockedStateChanged();
}


void DigitalWatchFace::dayChanged(bool yearChanged, bool monthChanged)
{
        (void)yearChanged;
        (void)monthChanged;

        lv_label_set_text_fmt(_dateLabel, "%s,\n%d. %s %d",
                              DateTime::DayOfWeekToStringLow(dayOfWeek()),
                              dayOfMonth(),
                              DateTime::MonthToStringLow(month()),
                              year());
}


void DigitalWatchFace::timeChanged(bool hourChanged, bool minuteChanged)
{
        if (second() & 1)
                lv_label_set_text_static(_colonLabel, ":");
        else
                lv_label_set_text_static(_colonLabel, "");

        if (hourChanged)
                lv_label_set_text_fmt(_hourLabel, "%02d", hour());
        if (minuteChanged)
                lv_label_set_text_fmt(_minuteLabel, "%02d", minute());
}


void DigitalWatchFace::lockedStateChanged()
{
        lv_label_set_text_static(_lockSymbol, locked() ? SYMBOL_LOCK : "");
        lv_obj_align(_lockSymbol, nullptr, LV_ALIGN_IN_TOP_MID, 0, 4);
}
