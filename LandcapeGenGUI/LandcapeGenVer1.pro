QT       += core gui #core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++19

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Array/AbstractArray.cpp \
    BaseWindow.cpp \
    Canvas.cpp \
    Controllers/BaseController.cpp \
    Controllers/BaseControllerTest.cpp \
    Controllers/ModeratorController.cpp \
    Controllers/UserControllerTest.cpp \
    Essensities/UserBL.cpp \
    Controllers/UserController.cpp \
    HeightsMap/HeightsMap.cpp \
    HeightsMap/HeightsMapPoints.cpp \
    HeightsMap/Point.cpp \
    Iterator/AbstractIterator.cpp \
    LandscapeCanvas/LandscapeCanvas.cpp \
    LoggingCategories.cpp \
    Matrix/AbstractMtrx.cpp \
    Essensities/CanvasBL.cpp \
    ModeratorWindow.cpp \
    Repositorys/CanvasRepository.cpp \
    Repositorys/CanvasRepositoryTest.cpp \
    Repositorys/ICanvasRepository.cpp \
    Repositorys/IUsersRepository.cpp \
    Repositorys/UsersRepository.cpp \
    Settings.cpp \
    Triangles/TriPolArray.cpp \
    Triangles/TriangularPolygon.cpp \
    UnitTestsWindow.cpp \
    Vector/AbstractVector.cpp \
    ZBuffer/FrameBuffer.cpp \
    ZBuffer/ZBuffer.cpp \
    ZBuffer/ZBufferAlg.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Array/AbstractArray.h \
    Array/BaseArray.h \
    Array/BaseArray.hpp \
    BaseWindow.h \
    Canvas.h \
    Controllers/BaseController.h \
    Controllers/BaseControllerTest.h \
    Controllers/ModeratorController.h \
    Controllers/UserControllerTest.h \
    Errors/RepositoryErrors.h \
    Essensities/UserBL.h \
    Controllers/UserController.h \
    Errors/ArrayErrors.h \
    Errors/BaseError.h \
    Errors/HeightsMapErrors.h \
    Errors/HeightsMapPointsErrors.h \
    Errors/IteratorErrors.h \
    Errors/MtrxErrors.h \
    Errors/VectorErrors.h \
    HeightsMap/HeightsMap.h \
    HeightsMap/HeightsMapPoints.h \
    HeightsMap/Point.h \
    Iterator/AbstractIterator.h \
    Iterator/BaseIterator.h \
    Iterator/BaseIterator.hpp \
    Iterator/ConstIterator.h \
    Iterator/ConstIterator.hpp \
    Iterator/Iterator.h \
    Iterator/Iterator.hpp \
    LandscapeCanvas/LandscapeCanvas.h \
    LoggingCategories.h \
    Matrix/AbstractMtrx.h \
    Matrix/BaseMtrx.h \
    Matrix/BaseMtrx.hpp \
    Essensities/CanvasBL.h \
    ModeratorWindow.h \
    Repositorys/CanvasRepository.h \
    Repositorys/CanvasRepositoryTest.h \
    Repositorys/ICanvasRepository.h \
    Repositorys/IUsersRepository.h \
    Repositorys/UsersRepository.h \
    Settings.h \
    Triangles/TriPolArray.h \
    Triangles/TriangularPolygon.h \
    UnitTestsWindow.h \
    Vector/AbstractVector.h \
    Vector/Vector.h \
    Vector/Vector.hpp \
    ZBuffer/FrameBuffer.h \
    ZBuffer/ZBuffer.h \
    ZBuffer/ZBufferAlg.h \
    mainwindow.h

FORMS += \
    BaseWindow.ui \
    ModeratorWindow.ui \
    UnitTestsWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/13/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/13/include'
