QT += testlib sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_canvasrepositorytest.cpp

#libpq
win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/13/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/13/include'

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
