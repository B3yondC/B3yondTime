#ifndef DIGITALWATCHFACE_H
#define DIGITALWATCHFACE_H


#include "WatchFace.h"



class DigitalWatchFace : public WatchFace
{
public:

        DigitalWatchFace(ScreenGraph *screenGraph, ComponentContainer *components);

protected:

        ScreenGraph::ScreenTag screenTag() const override { return ScreenGraph::ScreenTag::DigitalWatchFace; }

        void dayChanged(bool yearChanged, bool monthChanged) override;
        void timeChanged(bool hourChanged, bool minuteChanged) override;

        void lockedStateChanged() override;
        //void batteryPercentChanged() override;
        //void powerPresentChanged() override;
        //void bleConnectedChanged() override;

private:

        lv_obj_t *_hourLabel;
        lv_obj_t *_colonLabel;
        lv_obj_t *_minuteLabel;
        lv_obj_t *_dateLabel;
        lv_obj_t *_lockSymbol;
};

#endif // DIGITALWATCHFACE_H
