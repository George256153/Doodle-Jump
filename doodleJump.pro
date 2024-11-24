QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    detections/detection.cpp \
    detections/detection_enter_window.cpp \
    detections/detection_landing.cpp \
    detections/detection_touching.cpp \
    detections/detection_touching_without_landing.cpp \
    detector.cpp \
    gameobject.cpp \
    main.cpp \
    mainwindow.cpp \
    mover.cpp \
    player.cpp \
    reactions/reaction.cpp \
    reactions/reaction_change_image.cpp \
    reactions/reaction_disappear.cpp \
    reactions/reaction_gameover.cpp \
    reactions/reaction_make_sound.cpp \
    reactions/reaction_player_be_attacked.cpp \
    reactions/reaction_player_buffed_jump_height.cpp \
    reactions/reaction_player_jump.cpp \
    reactions/reaction_player_set_flying_state.cpp \
    reactions/reaction_player_shielded.cpp \
    stair_manager.cpp

HEADERS += \
    bullet.h \
    constants.h \
    detections/detection.h \
    detections/detection_enter_window.h \
    detections/detection_landing.h \
    detections/detection_touching.h \
    detections/detection_touching_without_landing.h \
    detector.h \
    gameobject.h \
    mainwindow.h \
    mover.h \
    player.h \
    reactions/reaction.h \
    reactions/reaction_change_image.h \
    reactions/reaction_disappear.h \
    reactions/reaction_gameover.h \
    reactions/reaction_make_sound.h \
    reactions/reaction_player_be_attacked.h \
    reactions/reaction_player_buffed_jump_height.h \
    reactions/reaction_player_jump.h \
    reactions/reaction_player_set_flying_state.h \
    reactions/reaction_player_shielded.h \
    rule_instances.h \
    stair_manager.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
