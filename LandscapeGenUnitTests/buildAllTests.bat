copy .\CanvasRepositoryTest\CanvasRepositoryTest.cfg .\CanvasRepositoryTest\release\CanvasRepositoryTest.cfg /y
copy .\ParamsRepositoryTest\ParamsRepositoryTest.cfg .\ParamsRepositoryTest\release\ParamsRepositoryTest.cfg /y
copy .\UsersRepositoryTest\UsersRepositoryTest.cfg .\UsersRepositoryTest\release\UsersRepositoryTest.cfg /y

windeployqt --compiler-runtime .\BaseControllerTest\release
windeployqt --compiler-runtime .\CanvasRepositoryTest\release
windeployqt --compiler-runtime .\ModeratorCanvasesControllerTest\release
windeployqt --compiler-runtime .\ParamsRepositoryTest\release
windeployqt --compiler-runtime .\UsersRepositoryTest\release

pause