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
      UserBL* new_user = new UserBL(-1, login, password, role, -1);
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

  void deleteChar(char* pChar)
  {
    delete[] pChar;
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
}

