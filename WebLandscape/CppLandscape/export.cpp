#include "export.h"
#include "Essensities/UserBL.h"
#include "Repositorys/UsersRepository.h"

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
}

extern "C"
{
  int loginBaseController(char* login, char* password)
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
        return -1; //No such role
    }
    catch (BaseError& er)
    {
      return -2; //Error
    }
    catch (...)
    {
      return -3; //Unexpected Error
    }
  }
}