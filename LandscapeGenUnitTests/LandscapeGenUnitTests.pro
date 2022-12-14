TEMPLATE = subdirs

SUBDIRS += \
    ../LandscapeGenLib \
    BaseControllerTest \
    CanvasRepositoryTest \
    ModeratorCanvasesControllerTest \
    ParamsRepositoryTest \
    UserControllerTest \
    UsersRepositoryTest

HEADERS += \
    common/CanvasBLBuilder.h

SOURCES += \
    common/CanvasBLBuilder.cpp

