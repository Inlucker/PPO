#pragma once

#define FILENAME "./config/default.cfg"
#define USER_REP UsersRepository
#define CANVAS_REP CanvasRepository
#define PARAMS_REP ParamsRepository

#define EXPORT _declspec(dllexport)

#include "Essensities/UserBL.h"
#include "Essensities/CanvasBl.h"
#include "Essensities/ParamsBL.h"
#include "Repositorys/UsersRepository.h"
#include "Repositorys/CanvasRepository.h"
#include "Repositorys/ParamsRepository.h"

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
  //UserBL
  EXPORT UserBL* getUserBL(char* login, char* password, int& ret_code);
  EXPORT UserBL* registerUser(char* login, char* password, char* role, int& ret_code);
  EXPORT int deleteUser(char* login, char* password);
  EXPORT int getUserId(UserBL* pUserBL);
  EXPORT char* getUserLogin(UserBL* pUserBL);
  EXPORT char* getUserPassword(UserBL* pUserBL);
  EXPORT char* getUserRole(UserBL* pUserBL);
  EXPORT int getUserModeratorId(UserBL* pUserBL);
  EXPORT void deleteUserBL(UserBL* pUserBL);

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

  //List<CanvasBL>
  EXPORT int getLandscapesNumberByUserId(int user_id);
  EXPORT int getLandscapesByUserId(int user_id, int idArray[], int strArray[][256]);

  //Generation
  EXPORT char* genHeightsMap(int size, bool smooth, int& ret_code);
  EXPORT CanvasBL* genCanvasBL(int size, bool smooth, int& ret_code);

  //Landscape
  EXPORT int sendLandscape(int user_id, char* name, char* heights_map, char* heights_map_points, int r, int g, int b);
  EXPORT int updateLandscape(int id, char* name, char* heights_map, char* heights_map_points, int r, int g, int b);
  EXPORT int deleteLandscape(int id);

  //Moderator Actions
  EXPORT int addUser(int user_id, int moderator_id);
  EXPORT int addUserByName(char* user_name, int moderator_id);
  EXPORT int removeUser(int user_id);
  EXPORT int removeUserByName(char* user_name);
  EXPORT int getFreeCanvasUsersNumber();
  EXPORT int getFreeCanvasUsers(char* free_canvas_users[]);
  EXPORT int getCanvasUsersNumber(int moderator_id);
  EXPORT int getCanvasUsers(int moderator_id, char* canvas_users[]);

  //Params
  EXPORT int getParams(int canvas_id, int& width, int& height, double& range, bool& smooth, int& mult, int& red, int& green, int& blue, int& size);
}