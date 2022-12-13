QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++19

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseWindow.cpp \
    Canvas.cpp \
    ModeratorCanvasWindow.cpp \
    ModeratorWindow.cpp \
    UnitTestsWindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BaseWindow.h \
    Canvas.h \
    ModeratorCanvasWindow.h \
    ModeratorWindow.h \
    UnitTestsWindow.h \
    defines.h \
    mainwindow.h

FORMS += \
    BaseWindow.ui \
    ModeratorCanvasWindow.ui \
    ModeratorWindow.ui \
    UnitTestsWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#libpq
win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/14/lib/' -llibpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/14/lib/' -llibpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/14/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/14/include'

#LandscapeGenLib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LandscapeGenLib/release/ -lLandscapeGenLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LandscapeGenLib/debug/ -lLandscapeGenLib
else:unix: LIBS += -L$$PWD/../LandscapeGenLib/ -lLandscapeGenLib

INCLUDEPATH += $$PWD/../LandscapeGenLib
DEPENDPATH += $$PWD/../LandscapeGenLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../LandscapeGenLib/release/libLandscapeGenLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../LandscapeGenLib/debug/libLandscapeGenLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../LandscapeGenLib/release/LandscapeGenLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../LandscapeGenLib/debug/LandscapeGenLib.lib
else:unix: PRE_TARGETDEPS += $$PWD/../LandscapeGenLib/libLandscapeGenLib.a
