QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Array/AbstractArray.cpp \
    Controllers/BaseController.cpp \
    Controllers/BaseControllerTest.cpp \
    Controllers/ModeratorCanvasesController.cpp \
    Controllers/ModeratorController.cpp \
    Controllers/UserControllerTest.cpp \
    Controllers/usercontroller.cpp \
    Essensities/CanvasBL.cpp \
    Essensities/ParamsBL.cpp \
    Essensities/UserBL.cpp \
    HeightsMap/HeightsMap.cpp \
    HeightsMap/HeightsMapPoints.cpp \
    HeightsMap/Point.cpp \
    Iterator/AbstractIterator.cpp \
    LandscapeCanvas/LandscapeCanvas.cpp \
    LandscapeGenLib.cpp \
    LoggingCategories.cpp \
    Matrix/AbstractMtrx.cpp \
    MyColor/MyColor.cpp \
    Repositorys/CanvasRepository.cpp \
    Repositorys/CanvasRepositoryTest.cpp \
    Repositorys/ICanvasRepository.cpp \
    Repositorys/IParamsRepository.cpp \
    Repositorys/IUsersRepository.cpp \
    Repositorys/ParamsRepository.cpp \
    Repositorys/UsersRepository.cpp \
    Settings.cpp \
    Triangles/TriPolArray.cpp \
    Triangles/TriangularPolygon.cpp \
    Vector/AbstractVector.cpp \
    ZBuffer/FrameBuffer.cpp \
    ZBuffer/ZBuffer.cpp \
    ZBuffer/ZBufferAlg.cpp

HEADERS += \
    Array/AbstractArray.h \
    Array/BaseArray.h \
    Array/BaseArray.hpp \
    Controllers/BaseController.h \
    Controllers/BaseControllerTest.h \
    Controllers/ModeratorCanvasesController.h \
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
    Essensities/ParamsBL.h \
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
    LandscapeGenLib.h \
    LoggingCategories.h \
    Matrix/AbstractMtrx.h \
    Matrix/BaseMtrx.h \
    Matrix/BaseMtrx.hpp \
    MyColor/MyColor.h \
    Repositorys/CanvasRepository.h \
    Repositorys/CanvasRepositoryTest.h \
    Repositorys/ICanvasRepository.h \
    Repositorys/IParamsRepository.h \
    Repositorys/IUsersRepository.h \
    Repositorys/ParamsRepository.h \
    Repositorys/UsersRepository.h \
    Settings.h \
    Triangles/TriPolArray.h \
    Triangles/TriangularPolygon.h \
    Vector/AbstractVector.h \
    Vector/Vector.h \
    Vector/Vector.hpp \
    ZBuffer/FrameBuffer.h \
    ZBuffer/ZBuffer.h \
    ZBuffer/ZBufferAlg.h \
    defines.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

#libpq
win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -llibpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/13/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/13/include'
