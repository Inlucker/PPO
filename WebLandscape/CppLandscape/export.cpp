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
  int getUserId(char* login, char* password)
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
      if (user_bl->getRole() == "canvas_user" || user_bl->getRole() == "moderator")
        return user_bl->getId();
      else
        return -3; //No such role
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

  void deleteChar(char* pChar)
  {
    delete pChar;
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
  EXPORT int getLandscapesNumberByUserId(int user_id)
  {

    try
    {
      shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("canvas_user", "canvas_user");
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

  EXPORT void getLandscapesByUserId(int user_id, int idArray[], int strArray[][256])
  {
    shared_ptr<CANVAS_REP> canvas_repository = make_shared<CANVAS_REP>("canvas_user", "canvas_user");
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
  }
}

