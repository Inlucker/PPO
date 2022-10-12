#pragma once

#define FILENAME "./config/default.cfg"
#define USER_REP UsersRepository
#define CANVAS_REP CanvasRepository
#define PARAMS_REP ParamsRepository

#define EXPORT _declspec(dllexport)

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
  EXPORT int loginBaseController(char* login, char* password);
}