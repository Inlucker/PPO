TEMPLATE = app
CONFIG += console c++19
CONFIG -= app_bundle

SOURCES += \
        Array/AbstractArray.cpp \
        BaseConsole.cpp \
        CanvasUserConsole.cpp \
        Controllers/BaseController.cpp \
        Controllers/BaseControllerTest.cpp \
        Controllers/ModeratorController.cpp \
        Controllers/UserControllerTest.cpp \
        Controllers/usercontroller.cpp \
        Essensities/CanvasBL.cpp \
        Essensities/UserBL.cpp \
        HeightsMap/HeightsMap.cpp \
        HeightsMap/HeightsMapPoints.cpp \
        HeightsMap/Point.cpp \
        Iterator/AbstractIterator.cpp \
        LandscapeCanvas/LandscapeCanvas.cpp \
        Matrix/AbstractMtrx.cpp \
        ModeratorConsole.cpp \
        Repositorys/CanvasRepository.cpp \
        Repositorys/CanvasRepositoryTest.cpp \
        Repositorys/ICanvasRepository.cpp \
        Repositorys/IUsersRepository.cpp \
        Repositorys/UsersRepository.cpp \
        Triangles/TriPolArray.cpp \
        Triangles/TriangularPolygon.cpp \
        Vector/AbstractVector.cpp \
        ZBuffer/FrameBuffer.cpp \
        ZBuffer/ZBuffer.cpp \
        ZBuffer/ZBufferAlg.cpp \
        main.cpp

HEADERS += \
    Array/AbstractArray.h \
    Array/BaseArray.h \
    Array/BaseArray.hpp \
    BaseConsole.h \
    CanvasUserConsole.h \
    Controllers/BaseController.h \
    Controllers/BaseControllerTest.h \
    Controllers/ModeratorController.h \
    Controllers/UserControllerTest.h \
    Controllers/usercontroller.h \
    Errors/ArrayErrors.h \
    Errors/BaseError.h \
    Errors/HeightsMapErrors.h \
    Errors/HeightsMapPointsErrors.h \
    Errors/IteratorErrors.h \
    Errors/MtrxErrors.h \
    Errors/RepositoryErrors.h \
    Errors/VectorErrors.h \
    Essensities/CanvasBL.h \
    Essensities/UserBL.h \
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
    Matrix/AbstractMtrx.h \
    Matrix/BaseMtrx.h \
    Matrix/BaseMtrx.hpp \
    ModeratorConsole.h \
    Repositorys/CanvasRepository.h \
    Repositorys/CanvasRepositoryTest.h \
    Repositorys/ICanvasRepository.h \
    Repositorys/IUsersRepository.h \
    Repositorys/UsersRepository.h \
    Triangles/TriPolArray.h \
    Triangles/TriangularPolygon.h \
    Vector/AbstractVector.h \
    Vector/Vector.h \
    Vector/Vector.hpp \
    ZBuffer/FrameBuffer.h \
    ZBuffer/ZBuffer.h \
    ZBuffer/ZBufferAlg.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/13/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/13/include'
