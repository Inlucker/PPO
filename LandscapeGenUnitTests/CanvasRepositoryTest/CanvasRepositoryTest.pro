QT += testlib sql
QT -= gui

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
win32:CONFIG(release, debug|release): LIBS += -L'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/release/' -lLandscapeGenLib
else:win32:CONFIG(debug, debug|release): LIBS += -L'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/debug/' -lLandscapeGenLib
else:unix: LIBS += -L'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/' -lLandscapeGenLib

INCLUDEPATH += 'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib'
DEPENDPATH += 'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib'

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += 'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/release/libLandscapeGenLib.a'
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += 'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/debug/libLandscapeGenLib.a'
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/release/LandscapeGenLib.lib'
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += 'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/debug/LandscapeGenLib.lib'
else:unix: PRE_TARGETDEPS += 'D:/GitRepositoryes/SOFT_TEST (PPO)/LandscapeGenLib/libLandscapeGenLib.a'
