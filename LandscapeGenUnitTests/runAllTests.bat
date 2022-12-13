@echo off
set report=unitTestsReport.txt
break > %report%
cd  .\BaseControllerTest\release
BaseControllerTest.exe >> "..\..\%report%"
echo: >> "..\..\%report%"
cd ..\..

cd .\CanvasRepositoryTest\release
CanvasRepositoryTest.exe >> "..\..\%report%"
echo: >> "..\..\%report%"
cd ..\..

cd .\ModeratorCanvasesControllerTest\release
ModeratorCanvasesControllerTest.exe >> "..\..\%report%"
echo: >> "..\..\%report%"
cd ..\..

cd .\ParamsRepositoryTest\release
ParamsRepositoryTest.exe >> "..\..\%report%"
echo: >> "..\..\%report%"
cd ..\..

cd .\UserControllerTest\release
UserControllerTest.exe >> "..\..\%report%"
echo: >> "..\..\%report%"
cd ..\..

cd .\UsersRepositoryTest\release
UsersRepositoryTest.exe >> "..\..\%report%"
echo: >> "..\..\%report%"
cd ..\..

clear
type %report%

pause