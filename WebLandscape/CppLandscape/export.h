#pragma once

#define FILENAME "./config/default.cfg"
#define USER_REP UsersRepository
#define CANVAS_REP CanvasRepository
#define PARAMS_REP ParamsRepository

#define EXPORT _declspec(dllexport)

#include "Essensities/UserBL.h"
#include "Essensities/CanvasBl.h"
#include "Repositorys/UsersRepository.h"
#include "Repositorys/CanvasRepository.h"

#include <iostream>
#include <fstream>

using namespace std;

//Testing funsc and classes
extern "C"
{
  EXPORT int AddNumbers(int a, int b);
  EXPORT int SubNumbers(int a, int b);
  EXPORT void WriteToFile(char* file_name, char* file_text);

  class Test
  {
  public:
	Test();

	int val = 3;

	int method(int param);
  };
}

extern "C"
{
  EXPORT int getUserId(char* login, char* password);

  EXPORT void deleteChar(char* pChar);

  //CanvasBL
  EXPORT CanvasBL* getCanvasBL(int id);
  EXPORT int getIdCanvasBL(CanvasBL* pCanvasBL);
  EXPORT int getUserIdCanvasBL(CanvasBL* pCanvasBL);
  //EXPORT void getNameCanvasBL(CanvasBL* pCanvasBL, char* pChar);
  EXPORT char* getNameCanvasBL(CanvasBL* pCanvasBL);
  //EXPORT void getHeightsMapCanvasBL(CanvasBL* pCanvasBL, char* str);
  EXPORT char* getHeightsMapCanvasBL(CanvasBL* pCanvasBL);
  EXPORT char* getHeightsMapPointsCanvasBL(CanvasBL* pCanvasBL);
  EXPORT void getColorCanvasBL(CanvasBL* pCanvasBL, int& r, int& g, int& b);
  EXPORT void deleteCanvasBL (CanvasBL* pCanvasBL);


}