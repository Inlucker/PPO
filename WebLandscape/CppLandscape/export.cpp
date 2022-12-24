#include "export.h"

//Testing funsc and classes
extern "C"
{
  int AddNumbers(int a, int b)
  {
    return a + b;
  }

  int SubNumbers(int a, int b)
  {
    return a - b;
  }

  void WriteToFile(char* file_name, char* file_text)
  {
    ofstream file(file_name, ios::out);
    file << file_text << endl;
    file.close();
  }

  Test::Test()
  {
    val = 4;
  }

  int Test::method(int param)
  {
    return param * param;
  }

  EXPORT Test* CreateTest() { return new Test(); }
  EXPORT int TestVal(Test* pTest) { return pTest->val; }
  EXPORT int TestMethod(Test* pTest, int param) { return pTest->method(param); }
  EXPORT void DeleteTest(Test* pTest) { delete pTest; }

  EXPORT char* myconvertmethod(CanvasBL* pCanvasBL, int id)
  {
    //string  res = "vasya=" + string(in);
    string res = pCanvasBL->getName();
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  EXPORT void MyConvert(char* str)
  {
    string s = "Petya was here";
    strcpy(str, s.c_str());
  }

  EXPORT char* MyConvert2(const char* source, char* dest)
  {
    std::string s(source);
    s += " and Petya was here";
    strcpy(dest, s.c_str());
    return dest;
  }

  EXPORT void SetInput(double arrayData[][4096])
  {
    arrayData[0][6] = 5.1;
  }
}

extern "C"
{
  UserBL* getUserBL(char* login, char* password, int& ret_code)
  {
    try
    {
      ret_code = 0;
      string _login = "";
      string _password = "";
      if (login != NULL)
        _login = login;
      if (password != NULL)
        _password = password;
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      shared_ptr<UserBL> user_bl = user_repository->getUser(_login, _password);
      UserBL* res = new UserBL(*(user_bl.get()));
      if (res->getRole() == "canvas_user" || user_bl->getRole() == "moderator")
        return res;
      else
      {
        ret_code = -3;
        return NULL; //No such role
      }
    }
    catch (BaseError& er)
    {
      ret_code = -1;
      return NULL; //Error
    }
    catch (...)
    {
      ret_code = -2;
      return NULL; //Unexpected Error
    }
  }

  UserBL* registerUser(char* login, char* password, char* role, int& ret_code)
  {
    try
    {
      ret_code = 0;
      string _login = "";
      string _password = "";
      string _role = "";
      if (login != NULL)
        _login = login;
      if (password != NULL)
        _password = password;
      if (role != NULL)
        _role = role;

      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      UserBL* new_user = new UserBL(-1, _login, _password, _role, -1);
      user_repository->addUser(*new_user);

      return new_user;
    }
    catch (BaseError& er)
    {
      ret_code = -1;
      return NULL; //Error
    }
    catch (...)
    {
      ret_code = -2;
      return NULL; //Unexpected Error
    }
  }

  int deleteUser(char* login, char* password)
  {
    try
    {
      string _login = "";
      string _password = "";
      if (login != NULL)
        _login = login;
      if (password != NULL)
        _password = password;

      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      shared_ptr<UserBL> user_bl = user_repository->getUser(_login, _password);
      user_repository->updateConfig(user_bl->getRole(), user_bl->getRole());
      user_repository->deleteUser(user_bl->getId());

      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }


  int getUserId(UserBL* pUserBL)
  {
    return pUserBL->getId();
  }

  char* getUserLogin(UserBL* pUserBL)
  {
    string res = pUserBL->getLogin();
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  char* getUserPassword(UserBL* pUserBL)
  {
    string res = pUserBL->getPassword();
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  char* getUserRole(UserBL* pUserBL)
  {
    string res = pUserBL->getRole();
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  int getUserModeratorId(UserBL* pUserBL)
  {
    return pUserBL->getModeratorId();
  }

  void deleteUserBL(UserBL* pUserBL)
  {
    delete pUserBL;
  }

  int getCanvasUserId(char* name, int& ret_code)
  {
      try
      {
          string _name = "";
          if (name != NULL)
              _name = name;

          shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
          shared_ptr<UserBL> user_bl = user_repository->getCanvasUser(_name);

          ret_code = 0;
          return user_bl->getId();
      }
      catch (BaseError& er)
      {
          ret_code = -1;
          return 0; //Error
      }
      catch (...)
      {
          ret_code = -2;
          return 0; //Unexpected Error
      }
  }

  void deleteChar(char* pChar)
  {
    delete[] pChar;
  }

  int checkCanvasByUserId(int canvas_id, int user_id)
  {
    try
    {
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("canvas_user", "canvas_user");
      shared_ptr<CanvasBL> canvasBL = canvas_repository->getCanvas(canvas_id);
      if (canvasBL->getUserId() == user_id)
        return 0;
      else
        return -3;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int checkCanvasByModeratorId(int canvas_id, int moderator_id)
  {
    try
    {
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("moderator", "moderator");
      shared_ptr<CanvasBL> canvasBL = canvas_repository->getCanvas(canvas_id);
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      string user_name = user_repository->getUser(canvasBL->getUserId())->getLogin();
      vector<string> users = user_repository->getCanvasUsersByMid(moderator_id);
      for (const string& user : users)
      {
        if (user == user_name)
          return 0;
      }
      return -3;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  //CanvasBL
  CanvasBL* getCanvasBL(int id)
  {
    try
    {
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("canvas_user", "canvas_user");
      shared_ptr<CanvasBL> canvas_bl = canvas_repository->getCanvas(id);
      CanvasBL* res = new CanvasBL(*(canvas_bl.get()));
      return res;
    }
    catch (BaseError& er)
    {
      string msg = er.what();
      //cout << msg << endl;
      HeightsMap hm = HeightsMap();
      HeightsMapPoints hmp = HeightsMapPoints();
      CanvasBL* res = new CanvasBL(-1, -1, msg, hm, hmp, 0, 0, 0);
      return res; //Error
    }
    catch (...)
    {
      string msg = "Unexpected Error";
      //cout << msg << endl;
      HeightsMap hm = HeightsMap();
      HeightsMapPoints hmp = HeightsMapPoints();
      CanvasBL* res = new CanvasBL(-1, -1, msg, hm, hmp, 0, 0, 0);
      return res; //Unexpected Error
    }
  }

  int getIdCanvasBL(CanvasBL* pCanvasBL)
  {
    return pCanvasBL->getId();
  }

  int getUserIdCanvasBL(CanvasBL* pCanvasBL)
  {
    return pCanvasBL->getUserId();
  }

  char* getNameCanvasBL(CanvasBL* pCanvasBL)
  {
    string res = pCanvasBL->getName();
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  //Doesn't work with big strings
  /*void getNameCanvasBL(CanvasBL* pCanvasBL, char* str)
  {
    string res = pCanvasBL->getName();
    strcpy(str, res.c_str());
  }*/

  //Doesn't work with big strings
  /*void getHeightsMapCanvasBL(CanvasBL* pCanvasBL, char* str)
  {
    string res;
    pCanvasBL->getHeightsMap().toStr(res);
    strcpy(str, res.c_str());
  }*/

  char* getHeightsMapCanvasBL(CanvasBL* pCanvasBL)
  {
    string res;
    pCanvasBL->getHeightsMap().toStr(res);
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  char* getHeightsMapPointsCanvasBL(CanvasBL* pCanvasBL)
  {
    string res;
    pCanvasBL->getHeightsMapPoints().toStr(res);
    char* cstr = new char[res.length() + 1];
    strcpy_s(cstr, res.length() + 1, res.c_str());

    return cstr;
  }

  void getColorCanvasBL(CanvasBL* pCanvasBL, int& r, int& g, int& b)
  {
    pCanvasBL->getColor(r, g, b);
  }

  void deleteCanvasBL(CanvasBL* pCanvasBL)
  {
    delete pCanvasBL;
  }

  //List<CanvasBL>
  int getLandscapesNumberByUserId(int user_id)
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      shared_ptr<UserBL> user_bl = user_repository->getUser(user_id);
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>(user_bl->getRole(), user_bl->getRole());
      vector<pair<int, string>> vec = canvas_repository->getCanvasesByUid(user_id);

      return vec.size();
    }
    catch (BaseError& er)
    {
      string msg = er.what();
      //cout << msg << endl;
      return -1; //Error
    }
    catch (...)
    {
      string msg = "Unexpected Error";
      //cout << msg << endl;
      return -2; //Unexpected Error
    }
  }

  int getLandscapesByUserId(int user_id, int idArray[], int strArray[][256])
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      shared_ptr<UserBL> user_bl = user_repository->getUser(user_id);
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>(user_bl->getRole(), user_bl->getRole());
      vector<pair<int, string>> vec = canvas_repository->getCanvasesByUid(user_id);

      for (int i = 0; i < vec.size(); i++)
      {
        idArray[i] = vec[i].first;
        string str = vec[i].second;
        for (int j = 0; j < str.length(); j++)
        {
          strArray[i][j] = str[j];
        }
      }
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int checkUserByModeratorId(int user_id, int moderator_id)
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      shared_ptr<UserBL> user_bl = user_repository->getUser(user_id);
      if (user_bl->getModeratorId() == moderator_id)
        return 0;
      else
        return -3;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  //Generation
  char* genHeightsMap(int size, bool smooth, int& ret_code)
  {
    ret_code = 0;
    try
    {
      HeightsMap hm = HeightsMap(size);
      hm.diamondSquare(size, smooth);

      string res = "";
      hm.toStr(res);
      char* cstr = new char[res.length() + 2];
      strcpy_s(cstr+1, res.length() + 1, res.c_str());

      return cstr;
    }
    catch (...)
    {
      ret_code = -2;
      return NULL; //Unexpected Error
    }
  }

  CanvasBL* genCanvasBL(int size, bool smooth, int& ret_code)
  {
    ret_code = 0;
    try
    {
      HeightsMap hm = HeightsMap(size);
      hm.diamondSquare(size, smooth);
      shared_ptr<HeightsMapPoints> hmp_pointer = hm.createPoints();
      HeightsMapPoints& hmp = *(hmp_pointer.get());
      CanvasBL* canvasBL = new CanvasBL(-1, -1, "Name", hm, hmp, 20, 150, 20);

      return canvasBL;
    }
    catch (...)
    {
      ret_code = -2;
      return NULL; //Unexpected Error
    }
  }

  //Landscape
  int sendLandscape(int user_id, char* name, char* heights_map, char* heights_map_points, int r, int g, int b)
  {
    try
    {
      string _name = "";
      string _heights_map = "";
      string _heights_map_points = "";
      if (name != NULL)
        _name = name;
      if (heights_map != NULL)
        _heights_map = heights_map;
      if (heights_map_points != NULL)
        _heights_map_points = heights_map_points;

      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      shared_ptr<UserBL> user_bl = user_repository->getUser(user_id);
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>(user_bl->getRole(), user_bl->getRole());
      CanvasBL canvasBL = CanvasBL(-1, user_id, _name, _heights_map, _heights_map_points, r, g, b);
      canvas_repository->addCanvas(canvasBL);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }
  int updateLandscape(int id, char* name, char* heights_map, char* heights_map_points, int r, int g, int b)
  {
    try
    {
      string _name = "";
      string _heights_map = "";
      string _heights_map_points = "";
      if (name != NULL)
        _name = name;
      if (heights_map != NULL)
        _heights_map = heights_map;
      if (heights_map_points != NULL)
        _heights_map_points = heights_map_points;

      //shared_ptr<USER_REP> user_repository = make_shared<USER_REP>();
      //shared_ptr<UserBL> user_bl = user_repository->getUser(user_id);
      //shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>(user_bl->getRole(), user_bl->getRole());
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("canvas_user", "canvas_user");
      CanvasBL canvasBL = CanvasBL(id, -1, _name, _heights_map, _heights_map_points, r, g, b);
      canvas_repository->updateCanvas(canvasBL, id);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int deleteLandscape(int id)
  {
    try
    {
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("canvas_user", "canvas_user");
      canvas_repository->deleteCanvas(id);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  //Moderator Actions
  int addUser(int user_id, int moderator_id)
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      shared_ptr<UserBL> userBL = user_repository->getUser(user_id);

      if (userBL->getRole() != "canvas_user")
        return -3; //user is not canvas_user
      if (userBL->getModeratorId() > 0)
        return -4; //user already has moderator
      shared_ptr<UserBL> moderatorBL = user_repository->getUser(moderator_id);
      if (moderatorBL->getRole() != "moderator")
        return -5; //moderator_id user is not moderator

      UserBL newUserBl = UserBL(userBL->getId(), userBL->getLogin(), userBL->getPassword(), userBL->getRole(), moderator_id);
      user_repository->updateUser(newUserBl, user_id);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int addUserByName(char* user_name, int moderator_id)
  {
    try
    {
      string _user_name = "";
      if (user_name != NULL)
        _user_name = user_name;
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      shared_ptr<UserBL> userBL = user_repository->getCanvasUser(_user_name);

      if (userBL->getRole() != "canvas_user")
        return -3; //user is not canvas_user
      if (userBL->getModeratorId() > 0)
        return -4; //user already has moderator

      shared_ptr<UserBL> moderatorBL = user_repository->getUser(moderator_id);
      if (moderatorBL->getRole() != "moderator")
        return -5; //moderator_id user is not moderator

      UserBL newUserBl = UserBL(userBL->getId(), userBL->getLogin(), userBL->getPassword(), userBL->getRole(), moderator_id);
      user_repository->updateUser(newUserBl, userBL->getId());
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int removeUser(int user_id, int moderator_id)
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      shared_ptr<UserBL> userBL = user_repository->getUser(user_id);

      if (userBL->getRole() != "canvas_user")
        return -3; //user is not canvas_user
      if (userBL->getModeratorId() <= 0)
        return -4; //user has no moderator
      if (userBL->getModeratorId() != moderator_id)
        return -5; //It's not your canvas_user

      UserBL newUserBl = UserBL(userBL->getId(), userBL->getLogin(), userBL->getPassword(), userBL->getRole(), -1);
      user_repository->updateUser(newUserBl, user_id);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int removeUserByName(char* user_name, int moderator_id)
  {
    try
    {
      string _user_name = "";
      if (user_name != NULL)
        _user_name = user_name;
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      shared_ptr<UserBL> userBL = user_repository->getCanvasUser(_user_name);

      if (userBL->getRole() != "canvas_user")
        return -3; //user is not canvas_user
      if (userBL->getModeratorId() <= 0)
        return -4; //user has no moderator
      if (userBL->getModeratorId() != moderator_id)
        return -5; //It's not your canvas_user

      UserBL newUserBl = UserBL(userBL->getId(), userBL->getLogin(), userBL->getPassword(), userBL->getRole(), -1);
      user_repository->updateUser(newUserBl, userBL->getId());
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int getFreeCanvasUsersNumber()
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      vector<string> vec = user_repository->getFreeCanvasUsers();
      int size = vec.size();
      return size;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int getFreeCanvasUsers(char* free_canvas_users[])
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");
      vector<string> vec = user_repository->getFreeCanvasUsers();
      int size = vec.size();
      for (int i = 0; i < size; i++)
      {
        rsize_t len = vec[i].length();
        free_canvas_users[i] = new char[len+1];
        strcpy_s(free_canvas_users[i], len + 1, vec[i].c_str());
      }
      return size;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int getCanvasUsersNumber(int moderator_id)
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");

      shared_ptr<UserBL> moderatorBL = user_repository->getUser(moderator_id);
      if (moderatorBL->getRole() != "moderator")
        return -3; //moderator_id user is not moderator

      vector<string> vec = user_repository->getCanvasUsersByMid(moderator_id);
      int size = vec.size();
      return size;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  int getCanvasUsers(int moderator_id, char* canvas_users[])
  {
    try
    {
      shared_ptr<USER_REP> user_repository = make_shared<USER_REP>("moderator", "moderator");

      shared_ptr<UserBL> moderatorBL = user_repository->getUser(moderator_id);
      if (moderatorBL->getRole() != "moderator")
        return -3; //moderator_id user is not moderator

      vector<string> vec = user_repository->getCanvasUsersByMid(moderator_id);
      int size = vec.size();
      for (int i = 0; i < size; i++)
      {
        rsize_t len = vec[i].length();
        canvas_users[i] = new char[len + 1];
        strcpy_s(canvas_users[i], len + 1, vec[i].c_str());
      }
      return size;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }

  //Params
  int getParams(int canvas_id, int& width, int& height, double& range, bool& smooth, int& mult, int& red, int& green, int& blue, int& size)
  {
    try
    {
      shared_ptr<PARAMS_REP> params_repository = make_shared<PARAMS_REP>("canvas_user", "canvas_user");

      shared_ptr<ParamsBL> paramsBL = params_repository->getParams(canvas_id);
      width = paramsBL->getWidth();
      height = paramsBL->getHeight();
      range = paramsBL->getRange();
      smooth = paramsBL->getSmooth();
      mult = paramsBL->getMult();
      red = paramsBL->getRed();
      green = paramsBL->getGreen();
      blue = paramsBL->getBlue();
      size = paramsBL->getSize();
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }
  int createParams(int canvas_id, int width, int height, double range, bool smooth, int mult, int red, int green, int blue, int size)
  {
    try
    {
      ParamsBL paramsBL = ParamsBL(canvas_id, width, height, range, smooth, mult, red, green, blue, size);
      shared_ptr<PARAMS_REP> params_repository = make_shared<PARAMS_REP>("canvas_user", "canvas_user");

      params_repository->addParams(paramsBL);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }
  int updateParams(int canvas_id, int width, int height, double range, bool smooth, int mult, int red, int green, int blue, int size)
  {
    try
    {
      ParamsBL paramsBL = ParamsBL(canvas_id, width, height, range, smooth, mult, red, green, blue, size);
      shared_ptr<PARAMS_REP> params_repository = make_shared<PARAMS_REP>("canvas_user", "canvas_user");

      params_repository->updateParams(paramsBL, canvas_id);
      return 0;
    }
    catch (BaseError& er)
    {
      return -1; //Error
    }
    catch (...)
    {
      return -2; //Unexpected Error
    }
  }
}

