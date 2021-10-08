#include "DefaultScreenGraph.h"

#include "components/ComponentContainer.h"

#include "Screen.h"



DefaultScreenGraph::DefaultScreenGraph(SystemInterface *system, ComponentContainer *components)
        : ScreenGraph(system, components)
{
        // set initial screen
        switchScreen(ScreenTag::DefaultWatchFace, 1, TransitionEffect::None);

        // transitions from AnalogWatchFace
        addSwipeTransition(ScreenTag::AnalogWatchFace, ScreenTag::Settings, Screen::SwipeDirection::Up);
        addSwipeTransition(ScreenTag::AnalogWatchFace, ScreenTag::DigitalWatchFace, Screen::SwipeDirection::Left);

        // transitions from DigitalWatchFace
        addSwipeTransition(ScreenTag::DigitalWatchFace, ScreenTag::Settings, Screen::SwipeDirection::Up);
        addSwipeTransition(ScreenTag::DigitalWatchFace, ScreenTag::BinaryWatchFace, Screen::SwipeDirection::Left);

        // transitions from BinaryWatchFace
        addSwipeTransition(ScreenTag::BinaryWatchFace, ScreenTag::Settings, Screen::SwipeDirection::Up);
        addSwipeTransition(ScreenTag::BinaryWatchFace, ScreenTag::AnalogWatchFace, Screen::SwipeDirection::Left);

        // transitions from FirmwareValidation
        addButtonTransition(ScreenTag::FirmwareValidation, ScreenTag::DefaultWatchFace);
        addSwipeTransition(ScreenTag::FirmwareValidation, ScreenTag::Previous, Screen::SwipeDirection::Right);

        // transitions from SystemInfo
        addButtonTransition(ScreenTag::SystemInfo, ScreenTag::DefaultWatchFace);
        addSwipeTransition(ScreenTag::SystemInfo, ScreenTag::Previous, Screen::SwipeDirection::Right);

        // transitions from Settings
        addButtonTransition(ScreenTag::Settings, ScreenTag::DefaultWatchFace);
        addSwipeTransition(ScreenTag::Settings, ScreenTag::DefaultWatchFace, Screen::SwipeDirection::Down);

        // transitions from Brightness
        addButtonTransition(ScreenTag::Brightness, ScreenTag::DefaultWatchFace);
        addSwipeTransition(ScreenTag::Brightness, ScreenTag::Previous, Screen::SwipeDirection::Right);

        // transitions from WakeUpMode
        addButtonTransition(ScreenTag::WakeUpMode, ScreenTag::DefaultWatchFace);
        addSwipeTransition(ScreenTag::WakeUpMode, ScreenTag::Previous, Screen::SwipeDirection::Right);

        // transitions from StepsGoal
        addButtonTransition(ScreenTag::StepsGoal, ScreenTag::DefaultWatchFace);
        addSwipeTransition(ScreenTag::StepsGoal, ScreenTag::Previous, Screen::SwipeDirection::Right);
}


ScreenGraph::ScreenTag DefaultScreenGraph::watchFaceScreenTagByIndex(uint8_t watchFaceIndex)
{
        switch (watchFaceIndex)
        {
        case 1:
                return ScreenTag::DigitalWatchFace;
        case 2:
                return ScreenTag::BinaryWatchFace;
        default:
                return ScreenTag::AnalogWatchFace;
        }
}
