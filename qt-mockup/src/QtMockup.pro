QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QT_CONFIG -= no-pkg-config
#CONFIG += link_pkgconfig
#PKGCONFIG += libcurl

INCLUDEPATH += \
        mockup \
        lvgl/src \
        ../../src

SOURCES += \
    ../../src/BootloaderVersion.cpp \
    ../../src/displayapp/SystemInterface.cc \
    ../../src/displayapp/fonts/FontAwesomeBrands24.c \
    ../../src/displayapp/fonts/FontAwesomeRegular24.c \
    ../../src/displayapp/fonts/FontAwesomeSolid24.c \
    ../../src/displayapp/fonts/FontBoldDigits96.c \
    ../../src/displayapp/fonts/font_dvs_ascii_12.c \
    ../../src/displayapp/fonts/font_dvs_ascii_14.c \
    ../../src/displayapp/fonts/font_dvs_ascii_16.c \
    ../../src/displayapp/fonts/font_dvsb_ascii_18.c \
    ../../src/displayapp/fonts/font_symbols_14.c \
    ../../src/displayapp/images/image_binary_watchface_bg.c \
    ../../src/displayapp/images/image_digital_watchface_bg.c \
    ../../src/displayapp/screens/BinaryWatchFace.cc \
    ../../src/displayapp/screens/BrightnessScreen.cc \
    ../../src/displayapp/screens/DigitalWatchFace.cc \
    ../../src/displayapp/screens/FirmwareUpdateScreen.cc \
    ../../src/displayapp/screens/FirmwareValidationScreen.cc \
    ../../src/displayapp/screens/SettingsScreen.cc \
    ../../src/displayapp/screens/StepsGoalScreen.cc \
    ../../src/displayapp/screens/SystemInfoScreen.cc \
    ../../src/displayapp/screens/WakeUpModeScreen.cc \
    ../../src/displayapp/screens/WatchFace.cc \
    MainWindow.cc \
    WatchMockupWidget.cc \
    ../../src/displayapp/screens/AnalogWatchFace.cc \
    ../../src/displayapp/screens/DefaultScreenGraph.cc \
    ../../src/displayapp/screens/Screen.cc \
    ../../src/displayapp/screens/ScreenGraph.cc \
    ../../src/displayapp/fonts/font_dvs_digits_20.c \
    ../../src/displayapp/fonts/font_dvs_digits_24.c \
    ../../src/displayapp/fonts/font_dvsb_caps_16.c \
    ../../src/displayapp/fonts/font_symbols_32.c \
    ../../src/displayapp/images/image_analog_watchface_bg.c \
    lvgl/src/lv_core/lv_disp.c \
    lvgl/src/lv_core/lv_group.c \
    lvgl/src/lv_core/lv_indev.c \
    lvgl/src/lv_core/lv_obj.c \
    lvgl/src/lv_core/lv_refr.c \
    lvgl/src/lv_core/lv_style.c \
    lvgl/src/lv_draw/lv_draw_arc.c \
    lvgl/src/lv_draw/lv_draw_blend.c \
    lvgl/src/lv_draw/lv_draw_img.c \
    lvgl/src/lv_draw/lv_draw_label.c \
    lvgl/src/lv_draw/lv_draw_line.c \
    lvgl/src/lv_draw/lv_draw_mask.c \
    lvgl/src/lv_draw/lv_draw_rect.c \
    lvgl/src/lv_draw/lv_draw_triangle.c \
    lvgl/src/lv_draw/lv_img_buf.c \
    lvgl/src/lv_draw/lv_img_cache.c \
    lvgl/src/lv_draw/lv_img_decoder.c \
    lvgl/src/lv_font/lv_font.c \
    lvgl/src/lv_font/lv_font_fmt_txt.c \
    lvgl/src/lv_font/lv_font_loader.c \
    lvgl/src/lv_font/lv_font_montserrat_14.c \
    lvgl/src/lv_gpu/lv_gpu_nxp_pxp.c \
    lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.c \
    lvgl/src/lv_gpu/lv_gpu_nxp_vglite.c \
    lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c \
    lvgl/src/lv_hal/lv_hal_disp.c \
    lvgl/src/lv_hal/lv_hal_indev.c \
    lvgl/src/lv_hal/lv_hal_tick.c \
    lvgl/src/lv_misc/lv_anim.c \
    lvgl/src/lv_misc/lv_area.c \
    lvgl/src/lv_misc/lv_async.c \
    lvgl/src/lv_misc/lv_bidi.c \
    lvgl/src/lv_misc/lv_color.c \
    lvgl/src/lv_misc/lv_debug.c \
    lvgl/src/lv_misc/lv_fs.c \
    lvgl/src/lv_misc/lv_gc.c \
    lvgl/src/lv_misc/lv_ll.c \
    lvgl/src/lv_misc/lv_log.c \
    lvgl/src/lv_misc/lv_math.c \
    lvgl/src/lv_misc/lv_mem.c \
    lvgl/src/lv_misc/lv_printf.c \
    lvgl/src/lv_misc/lv_task.c \
    lvgl/src/lv_misc/lv_templ.c \
    lvgl/src/lv_misc/lv_txt.c \
    lvgl/src/lv_misc/lv_txt_ap.c \
    lvgl/src/lv_misc/lv_utils.c \
    lvgl/src/lv_themes/lv_theme.c \
    lvgl/src/lv_themes/lv_theme_empty.c \
    lvgl/src/lv_themes/lv_theme_material.c \
    lvgl/src/lv_themes/lv_theme_mono.c \
    lvgl/src/lv_themes/lv_theme_template.c \
    lvgl/src/lv_widgets/lv_arc.c \
    lvgl/src/lv_widgets/lv_bar.c \
    lvgl/src/lv_widgets/lv_btn.c \
    lvgl/src/lv_widgets/lv_btnmatrix.c \
    lvgl/src/lv_widgets/lv_calendar.c \
    lvgl/src/lv_widgets/lv_canvas.c \
    lvgl/src/lv_widgets/lv_chart.c \
    lvgl/src/lv_widgets/lv_checkbox.c \
    lvgl/src/lv_widgets/lv_cont.c \
    lvgl/src/lv_widgets/lv_cpicker.c \
    lvgl/src/lv_widgets/lv_dropdown.c \
    lvgl/src/lv_widgets/lv_gauge.c \
    lvgl/src/lv_widgets/lv_img.c \
    lvgl/src/lv_widgets/lv_imgbtn.c \
    lvgl/src/lv_widgets/lv_keyboard.c \
    lvgl/src/lv_widgets/lv_label.c \
    lvgl/src/lv_widgets/lv_led.c \
    lvgl/src/lv_widgets/lv_line.c \
    lvgl/src/lv_widgets/lv_linemeter.c \
    lvgl/src/lv_widgets/lv_list.c \
    lvgl/src/lv_widgets/lv_msgbox.c \
    lvgl/src/lv_widgets/lv_objmask.c \
    lvgl/src/lv_widgets/lv_objx_templ.c \
    lvgl/src/lv_widgets/lv_page.c \
    lvgl/src/lv_widgets/lv_roller.c \
    lvgl/src/lv_widgets/lv_slider.c \
    lvgl/src/lv_widgets/lv_spinbox.c \
    lvgl/src/lv_widgets/lv_spinner.c \
    lvgl/src/lv_widgets/lv_switch.c \
    lvgl/src/lv_widgets/lv_table.c \
    lvgl/src/lv_widgets/lv_tabview.c \
    lvgl/src/lv_widgets/lv_textarea.c \
    lvgl/src/lv_widgets/lv_tileview.c \
    lvgl/src/lv_widgets/lv_win.c \
    main.cc \
    mockup/components/ComponentContainer.cc \
    mockup/components/battery/BatteryController.cc \
    mockup/components/ble/BleController.cc \
    mockup/components/brightness/BrightnessController.cc \
    mockup/components/datetime/DateTimeController.cc \
    mockup/components/firmwarevalidator/FirmwareValidator.cc \
    mockup/components/motion/MotionController.cc \
    mockup/components/settings/Settings.cc \
    mockup/drivers/Watchdog.cc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        ../../src/BootloaderVersion.h \
        ../../src/Version.h \
        ../../src/displayapp/SystemInterface.h \
        ../../src/displayapp/fonts/FontAwesomeBrands24.h \
        ../../src/displayapp/fonts/FontAwesomeRegular24.h \
        ../../src/displayapp/fonts/FontAwesomeSolid24.h \
        ../../src/displayapp/fonts/FontBoldDigits96.h \
        ../../src/displayapp/fonts/font_dvs_ascii_12.h \
        ../../src/displayapp/fonts/font_dvs_ascii_14.h \
        ../../src/displayapp/fonts/font_dvs_ascii_16.h \
        ../../src/displayapp/fonts/font_dvsb_ascii_18.h \
        ../../src/displayapp/fonts/font_symbols_14.h \
        ../../src/displayapp/screens/BinaryWatchFace.h \
        ../../src/displayapp/screens/BrightnessScreen.h \
        ../../src/displayapp/screens/DigitalWatchFace.h \
        ../../src/displayapp/screens/FirmwareUpdateScreen.h \
        ../../src/displayapp/screens/FirmwareValidationScreen.h \
        ../../src/displayapp/screens/SettingsScreen.h \
        ../../src/displayapp/screens/StepsGoalScreen.h \
        ../../src/displayapp/screens/SystemInfoScreen.h \
        ../../src/displayapp/screens/WakeUpModeScreen.h \
        ../../src/displayapp/screens/WatchFace.h \
        MainWindow.h \
        WatchMockupWidget.h \
        ../../src/displayapp/screens/AnalogWatchFace.h \
        ../../src/displayapp/screens/DefaultScreenGraph.h \
        ../../src/displayapp/screens/Screen.h \
        ../../src/displayapp/screens/ScreenGraph.h \
        ../../src/displayapp/fonts/font_dvs_digits_20.h \
        ../../src/displayapp/fonts/font_dvs_digits_24.h \
        ../../src/displayapp/fonts/font_dvsb_caps_16.h \
        ../../src/displayapp/fonts/font_symbols_32.h \
        lv_conf.h \
        lvgl/lvgl.h \
        lvgl/src/lv_api_map.h \
        lvgl/src/lv_conf_internal.h \
        lvgl/src/lv_conf_kconfig.h \
        lvgl/src/lv_conf_zephyr.h \
        lvgl/src/lv_core/lv_disp.h \
        lvgl/src/lv_core/lv_group.h \
        lvgl/src/lv_core/lv_indev.h \
        lvgl/src/lv_core/lv_obj.h \
        lvgl/src/lv_core/lv_obj_style_dec.h \
        lvgl/src/lv_core/lv_refr.h \
        lvgl/src/lv_core/lv_style.h \
        lvgl/src/lv_draw/lv_draw.h \
        lvgl/src/lv_draw/lv_draw_arc.h \
        lvgl/src/lv_draw/lv_draw_blend.h \
        lvgl/src/lv_draw/lv_draw_img.h \
        lvgl/src/lv_draw/lv_draw_label.h \
        lvgl/src/lv_draw/lv_draw_line.h \
        lvgl/src/lv_draw/lv_draw_mask.h \
        lvgl/src/lv_draw/lv_draw_rect.h \
        lvgl/src/lv_draw/lv_draw_triangle.h \
        lvgl/src/lv_draw/lv_img_buf.h \
        lvgl/src/lv_draw/lv_img_cache.h \
        lvgl/src/lv_draw/lv_img_decoder.h \
        lvgl/src/lv_font/lv_font.h \
        lvgl/src/lv_font/lv_font_fmt_txt.h \
        lvgl/src/lv_font/lv_font_loader.h \
        lvgl/src/lv_font/lv_symbol_def.h \
        lvgl/src/lv_gpu/lv_gpu_nxp_pxp.h \
        lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.h \
        lvgl/src/lv_gpu/lv_gpu_nxp_vglite.h \
        lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.h \
        lvgl/src/lv_hal/lv_hal.h \
        lvgl/src/lv_hal/lv_hal_disp.h \
        lvgl/src/lv_hal/lv_hal_indev.h \
        lvgl/src/lv_hal/lv_hal_tick.h \
        lvgl/src/lv_misc/lv_anim.h \
        lvgl/src/lv_misc/lv_area.h \
        lvgl/src/lv_misc/lv_async.h \
        lvgl/src/lv_misc/lv_bidi.h \
        lvgl/src/lv_misc/lv_color.h \
        lvgl/src/lv_misc/lv_debug.h \
        lvgl/src/lv_misc/lv_fs.h \
        lvgl/src/lv_misc/lv_gc.h \
        lvgl/src/lv_misc/lv_ll.h \
        lvgl/src/lv_misc/lv_log.h \
        lvgl/src/lv_misc/lv_math.h \
        lvgl/src/lv_misc/lv_mem.h \
        lvgl/src/lv_misc/lv_printf.h \
        lvgl/src/lv_misc/lv_task.h \
        lvgl/src/lv_misc/lv_templ.h \
        lvgl/src/lv_misc/lv_txt.h \
        lvgl/src/lv_misc/lv_txt_ap.h \
        lvgl/src/lv_misc/lv_types.h \
        lvgl/src/lv_misc/lv_utils.h \
        lvgl/src/lv_themes/lv_theme.h \
        lvgl/src/lv_themes/lv_theme_empty.h \
        lvgl/src/lv_themes/lv_theme_material.h \
        lvgl/src/lv_themes/lv_theme_mono.h \
        lvgl/src/lv_themes/lv_theme_template.h \
        lvgl/src/lv_widgets/lv_arc.h \
        lvgl/src/lv_widgets/lv_bar.h \
        lvgl/src/lv_widgets/lv_btn.h \
        lvgl/src/lv_widgets/lv_btnmatrix.h \
        lvgl/src/lv_widgets/lv_calendar.h \
        lvgl/src/lv_widgets/lv_canvas.h \
        lvgl/src/lv_widgets/lv_chart.h \
        lvgl/src/lv_widgets/lv_checkbox.h \
        lvgl/src/lv_widgets/lv_cont.h \
        lvgl/src/lv_widgets/lv_cpicker.h \
        lvgl/src/lv_widgets/lv_dropdown.h \
        lvgl/src/lv_widgets/lv_gauge.h \
        lvgl/src/lv_widgets/lv_img.h \
        lvgl/src/lv_widgets/lv_imgbtn.h \
        lvgl/src/lv_widgets/lv_keyboard.h \
        lvgl/src/lv_widgets/lv_label.h \
        lvgl/src/lv_widgets/lv_led.h \
        lvgl/src/lv_widgets/lv_line.h \
        lvgl/src/lv_widgets/lv_linemeter.h \
        lvgl/src/lv_widgets/lv_list.h \
        lvgl/src/lv_widgets/lv_msgbox.h \
        lvgl/src/lv_widgets/lv_objmask.h \
        lvgl/src/lv_widgets/lv_objx_templ.h \
        lvgl/src/lv_widgets/lv_page.h \
        lvgl/src/lv_widgets/lv_roller.h \
        lvgl/src/lv_widgets/lv_slider.h \
        lvgl/src/lv_widgets/lv_spinbox.h \
        lvgl/src/lv_widgets/lv_spinner.h \
        lvgl/src/lv_widgets/lv_switch.h \
        lvgl/src/lv_widgets/lv_table.h \
        lvgl/src/lv_widgets/lv_tabview.h \
        lvgl/src/lv_widgets/lv_textarea.h \
        lvgl/src/lv_widgets/lv_tileview.h \
        lvgl/src/lv_widgets/lv_win.h \
        lvgl/src/lvgl.h \
        mockup/components/ComponentContainer.h \
        mockup/components/battery/BatteryController.h \
        mockup/components/ble/BleController.h \
        mockup/components/brightness/BrightnessController.h \
        mockup/components/datetime/DateTimeController.h \
        mockup/components/firmwarevalidator/FirmwareValidator.h \
        mockup/components/motion/MotionController.h \
        mockup/components/settings/Settings.h \
        mockup/drivers/Watchdog.h

RESOURCES += \
        Resources.qrc
