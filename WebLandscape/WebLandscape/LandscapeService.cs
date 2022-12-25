using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Text;
using WebLandscape.Models;
using WebLandscape.ViewModels;
using WebLandscape.RequestSchemas;

namespace WebLandscape
{
  public class LandscapeService
  {
    public const string CppFunctionsDLL = @"..\x64\Debug\CppLandscape.dll";

    //Landscape funcs (tests)
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr createLandscapeCanvas();
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int generateLandscapeLandscapeCanvas(IntPtr value, int size);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void deleteLandscapeCanvas(IntPtr value);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getHeightsMapPtr(IntPtr pLandscapeCanvas);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr writeToFileHeightsMap(IntPtr pHeightsMap, String file_name);


    //UserBL
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getUserBL(String login, String password, ref int returnCode);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr registerUser(String login, String password, String role, ref int returnCode);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int deleteUser(String login, String password);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getUserId(IntPtr pUserBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getUserLogin(IntPtr pUserBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getUserPassword(IntPtr pUserBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getUserRole(IntPtr pUserBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getUserModeratorId(IntPtr pUserBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void deleteUserBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getCanvasUserId(String name, ref int ret);


    //CanvasBl
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getCanvasBL(int id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getIdCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getUserIdCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getNameCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getHeightsMapCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr getHeightsMapPointsCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void getColorCanvasBL(IntPtr pChar, ref int r, ref int g, ref int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void deleteChar(IntPtr pChar);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void deleteCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int checkCanvasByUserId(int canvas_id, int user_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int checkCanvasByModeratorId(int canvas_id, int moderator_id);


    //List<CanvasBL>
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getLandscapesNumberByUserId(int user_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getLandscapesByUserId(int user_id, int[] idArray, int[,] strArray);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int checkUserByModeratorId(int user_id, int moderator_id);


    //HeightsMap
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr genHeightsMap(int size, bool smooth);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr genCanvasBL(int size, double range, bool smooth, ref int returnCode); //returns canvasBL pointer


    //Landscape
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int sendLandscape(int user_id, String name, String heights_map, String heights_map_points, int r, int g, int b, ref int canvas_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int updateLandscape(int id, String name, String heights_map, String heights_map_points, int r, int g, int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int deleteLandscape(int id);

    //Moderator Actions
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int addUser(int user_id, int moderator_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int addUserByName(String user_name, int moderator_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int removeUser(int user_id, int moderator_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int removeUserByName(String user_name, int moderator_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getFreeCanvasUsersNumber();
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getFreeCanvasUsers(IntPtr[] freeCanvasUsers);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getCanvasUsersNumber(int moderator_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getCanvasUsers(int moderator_id, IntPtr[] freeCanvasUsers);


    //Params
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getParams(int canvas_id, ref int width, ref int height, ref double range, ref bool smooth, ref int mult, ref int red, ref int green, ref int blue, ref int size);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int createParams(int canvas_id, int width, int height, double range, bool smooth, int mult, int red, int green, int blue, int size);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int updateParams(int canvas_id, int width, int height, double range, bool smooth, int mult, int red, int green, int blue, int size);

    public static String GenHeightsMap(GenHeightsMapSchema model)
    {
      IntPtr pChar = genHeightsMap(model.Size, model.Smoothing);
      if (pChar == null)
        return null;
      String heightsMap = Marshal.PtrToStringAnsi(pChar);
      heightsMap = heightsMap.Remove(0, 1);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      return heightsMap;
    }
    public static Landscape GenLandscape(int size, double range, bool smoothing, String name, int? red, int? green, int? blue)
    {
      Landscape canvasBL = new Landscape();

      //create canvasBL
      int ret = -1;
      IntPtr pCanvasBl = genCanvasBL(size, range, smoothing, ref ret);
      if (ret != 0)
        return null;

      //canvas id
      int canvasId = getIdCanvasBL(pCanvasBl);
      canvasBL.id = canvasId;

      //canvas user_id
      canvasBL.user_id = getUserIdCanvasBL(pCanvasBl);

      //canvas name
      if (name != null)
        canvasBL.name = name;
      else
      {
        IntPtr pChar = getNameCanvasBL(pCanvasBl);
        String canvasName = Marshal.PtrToStringAnsi(pChar);
        canvasBL.name = canvasName;
        deleteChar(pChar);
        pChar = IntPtr.Zero;
      }

      //canvas heights_map
      IntPtr pHeightsMapChar = getHeightsMapCanvasBL(pCanvasBl);
      String heightsMapStr = Marshal.PtrToStringAnsi(pHeightsMapChar);
      canvasBL.heights_map = heightsMapStr;
      deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas heights_map_points
      IntPtr pHeightsMapPointsChar = getHeightsMapPointsCanvasBL(pCanvasBl);
      canvasBL.heights_map_points = Marshal.PtrToStringAnsi(pHeightsMapPointsChar);
      deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas color
      int r = 0, g = 0, b = 0;
      getColorCanvasBL(pCanvasBl, ref r, ref g, ref b);
      if (red.HasValue)
        canvasBL.red = (int)red;
      else
        canvasBL.red = r;
      if (red.HasValue)
        canvasBL.green = (int)green;
      else
        canvasBL.green = g;
      if (red.HasValue)
        canvasBL.blue = (int)blue;
      else
        canvasBL.blue = b;

      //delete canvasBL
      deleteCanvasBL(pCanvasBl);
      pCanvasBl = IntPtr.Zero;

      return canvasBL;
    }
    public static Landscape GetLandscapeForModerator(int id, int moderator_id, out int ret_code)
    {
      ret_code = checkCanvasByModeratorId(id, moderator_id);
      if (ret_code != 0)
        return null;

      Landscape canvasBL = new Landscape();

      //create canvasBL
      IntPtr pCanvasBl = getCanvasBL(id);

      //canvas id
      int canvasId = getIdCanvasBL(pCanvasBl);
      if (canvasId == -1)
      {
        ret_code = -1;
        return null; //Вернуть ошибку
      }
      canvasBL.id = canvasId;

      //canvas user_id
      canvasBL.user_id = getUserIdCanvasBL(pCanvasBl);

      //canvas name
      IntPtr pChar = getNameCanvasBL(pCanvasBl);
      String canvasName = Marshal.PtrToStringAnsi(pChar);
      canvasBL.name = canvasName;
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //canvas heights_map
      IntPtr pHeightsMapChar = getHeightsMapCanvasBL(pCanvasBl);
      String heightsMapStr = Marshal.PtrToStringAnsi(pHeightsMapChar);
      canvasBL.heights_map = heightsMapStr;
      deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas heights_map_points
      IntPtr pHeightsMapPointsChar = getHeightsMapPointsCanvasBL(pCanvasBl);
      canvasBL.heights_map_points = Marshal.PtrToStringAnsi(pHeightsMapPointsChar);
      deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas color
      int r = 0, g = 0, b = 0;
      getColorCanvasBL(pCanvasBl, ref r, ref g, ref b);
      canvasBL.red = r;
      canvasBL.green = g;
      canvasBL.blue = b;

      //delete canvasBL
      deleteCanvasBL(pCanvasBl);
      pCanvasBl = IntPtr.Zero;

      return canvasBL;
    }
    public static Landscape GetLandscapeForCanvasUser(int id, int user_id, out int ret_code)
    {
      ret_code = checkCanvasByUserId(id, user_id);
      if (ret_code != 0)
        return null;

      Landscape canvasBL = new Landscape();

      //create canvasBL
      IntPtr pCanvasBl = getCanvasBL(id);

      //canvas id
      int canvasId = getIdCanvasBL(pCanvasBl);
      if (canvasId == -1)
      {
        ret_code = -1;
        return null; //Вернуть ошибку
      }
      canvasBL.id = canvasId;

      //canvas user_id
      canvasBL.user_id = getUserIdCanvasBL(pCanvasBl);

      //canvas name
      IntPtr pChar = getNameCanvasBL(pCanvasBl);
      String canvasName = Marshal.PtrToStringAnsi(pChar);
      canvasBL.name = canvasName;
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //canvas heights_map
      IntPtr pHeightsMapChar = getHeightsMapCanvasBL(pCanvasBl);
      String heightsMapStr = Marshal.PtrToStringAnsi(pHeightsMapChar);
      canvasBL.heights_map = heightsMapStr;
      deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas heights_map_points
      IntPtr pHeightsMapPointsChar = getHeightsMapPointsCanvasBL(pCanvasBl);
      canvasBL.heights_map_points = Marshal.PtrToStringAnsi(pHeightsMapPointsChar);
      deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas color
      int r = 0, g = 0, b = 0;
      getColorCanvasBL(pCanvasBl, ref r, ref g, ref b);
      canvasBL.red = r;
      canvasBL.green = g;
      canvasBL.blue = b;

      //delete canvasBL
      deleteCanvasBL(pCanvasBl);
      pCanvasBl = IntPtr.Zero;

      return canvasBL;
    }
    public static List<CanvasIdName> GetLandscapesForModerator(int user_id, int moderator_id, out int ret_code)
    {
      ret_code = 0;
      List<CanvasIdName> lst = new List<CanvasIdName>();
      if (user_id < 0)
      {
        ret_code = -1;
        return lst;
      }

      int ret = checkUserByModeratorId(user_id, moderator_id);
      if (ret != 0)
      {
        ret_code = -2;
        return lst;
      }

      int size = getLandscapesNumberByUserId(user_id);
      if (size < 0)
      {
        ret_code = -3;
        return lst;
      }

      int[] idArray = new int[size];
      int[,] nameArray = new int[size, 256];
      ret = getLandscapesByUserId((int)user_id, idArray, nameArray);
      if (ret != 0)
      {
        ret_code = -4;
        return lst;
      }

      char[,] nameArray2 = new char[size, 256];
      for (int i = 0; i < size; i++)
        for (int j = 0; j < 256; j++)
          nameArray2[i, j] = (char)nameArray[i, j];

      string[] nameArray3 = new string[size];
      for (int i = 0; i < size; i++)
      {
        var builder = new StringBuilder();
        for (int j = 0; j < 256; j++)
        {
          if (nameArray2[i, j] == '\0')
            break;
          builder.Append(nameArray2[i, j]);
        }
        nameArray3[i] = builder.ToString();
      }

      for (int i = 0; i < size; i++)
        lst.Add(new CanvasIdName { id = idArray[i], name = nameArray3[i] });

      return lst;
    }
    public static List<CanvasIdName> GetLandscapesForCanvasUser(int user_id, out int ret_code)
    {
      ret_code = 0;
      List<CanvasIdName> lst = new List<CanvasIdName>();
      if (user_id < 0)
      {
        ret_code = -1;
        return lst;
      }

      int size = getLandscapesNumberByUserId((int)user_id);
      if (size < 0)
      {
        ret_code = -2;
        return lst;
      }

      int[] idArray = new int[size];
      int[,] nameArray = new int[size, 256];
      int ret = getLandscapesByUserId((int)user_id, idArray, nameArray);
      if (ret != 0)
      {
        ret_code = -3;
        return lst;
      }

      char[,] nameArray2 = new char[size, 256];
      for (int i = 0; i < size; i++)
        for (int j = 0; j < 256; j++)
          nameArray2[i, j] = (char)nameArray[i, j];

      string[] nameArray3 = new string[size];
      for (int i = 0; i < size; i++)
      {
        var builder = new StringBuilder();
        for (int j = 0; j < 256; j++)
        {
          if (nameArray2[i, j] == '\0')
            break;
          builder.Append(nameArray2[i, j]);
        }
        nameArray3[i] = builder.ToString();
      }

      for (int i = 0; i < size; i++)
        lst.Add(new CanvasIdName { id = idArray[i], name = nameArray3[i] });

      return lst;
    }

    public static int SendLandscape(CreateLandscapeSchema schema, int user_id, out int canvas_id)
    {
      int res = 0;
      canvas_id = 0;
      res = sendLandscape(user_id, schema.name, schema.heights_map, schema.heights_map_points, schema.red, schema.green, schema.blue, ref canvas_id);

      return res;
    }

    public static int UpdateLandscape(UpdateLandscapeSchema schema, int user_id)
    {
      int res = checkCanvasByUserId(schema.id, user_id);
      if (res != 0)
        return res;
      res = updateLandscape(schema.id, schema.name, schema.heights_map, schema.heights_map_points, schema.red, schema.green, schema.blue);

      return res;
    }
    public static int DeleteLandscape(int canvas_id, int user_id)
    {
      int res = checkCanvasByUserId(canvas_id, user_id);
      if (res != 0)
        return res;
      res = deleteLandscape(canvas_id);
      return res;
    }

    public static User Login(String login, String password)
    {
      User userBL = new User();

      //create userBL
      int ret = -1;
      IntPtr pUserBl = getUserBL(login, password, ref ret);
      if (ret != 0)
        return null;

      //ID
      userBL.Id = getUserId(pUserBl);

      //Login
      IntPtr pChar = getUserLogin(pUserBl);
      userBL.Login = Marshal.PtrToStringAnsi(pChar);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //Password
      pChar = getUserPassword(pUserBl);
      userBL.Password = Marshal.PtrToStringAnsi(pChar);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //Role
      pChar = getUserRole(pUserBl);
      userBL.Role = Marshal.PtrToStringAnsi(pChar);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //Modeartor ID
      userBL.ModeratorId = getUserModeratorId(pUserBl);

      //delete userBL
      deleteUserBL(pUserBl);
      pUserBl = IntPtr.Zero;

      return userBL;
    }

    public static User Register(String login, String password, String role)
    {
      //return_code = 0;
      User userBL = new User();

      //create userBL
      int ret = -1;
      IntPtr pUserBl = registerUser(login, password, role, ref ret);
      if (ret != 0)
      {
        //return_code = -1;
        return null;
      }

      //ID
      userBL.Id = getUserId(pUserBl);

      //Login
      IntPtr pChar = getUserLogin(pUserBl);
      userBL.Login = Marshal.PtrToStringAnsi(pChar);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //Password
      pChar = getUserPassword(pUserBl);
      userBL.Password = Marshal.PtrToStringAnsi(pChar);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //Role
      pChar = getUserRole(pUserBl);
      userBL.Role = Marshal.PtrToStringAnsi(pChar);
      deleteChar(pChar);
      pChar = IntPtr.Zero;

      //Modeartor ID
      userBL.ModeratorId = getUserModeratorId(pUserBl);

      //delete userBL
      deleteUserBL(pUserBl);
      pUserBl = IntPtr.Zero;

      return userBL;
    }

    public static int DeleteUser(String login, String password)
    {
      int res = deleteUser(login, password);
      return res;
    }

    public static int AddUser(int moderator_id, int? user_id, String user_name)
    {
      int res = -1;
      if (user_id.HasValue)
        res = addUser((int)user_id, moderator_id);
      else if (user_name != null)
        res = addUserByName(user_name, moderator_id);
      return res;
    }
    public static int RemoveUser(int? user_id, String user_name, int moderator_id)
    {
      int res = -1;
      if (user_id.HasValue)
        res = removeUser((int)user_id, moderator_id);
      else if (user_name != null)
        res = removeUserByName(user_name, moderator_id);
      return res;
    }

    public static int GetFreeCanvasUsers(out List<String> canvasUsers)
    {
      canvasUsers = new List<String>();
      int size = getFreeCanvasUsersNumber();
      if (size < 0)
        return -1; //error

      IntPtr[] namesPtrs = new IntPtr[size];
      int ret = getFreeCanvasUsers(namesPtrs);
      if (ret != size)
      {
        foreach (IntPtr pChar in namesPtrs)
          deleteChar(pChar);
        return -2; //different sizes
      }
      for (int i = 0; i < namesPtrs.Length; i++)
      {
        String canvasUser = Marshal.PtrToStringAnsi(namesPtrs[i]);
        deleteChar(namesPtrs[i]);
        namesPtrs[i] = IntPtr.Zero;
        canvasUsers.Add(canvasUser);
      }
      return 0;
    }
    public static int GetCanvasUsers(int moderator_id, out List<String> canvasUsers)
    {
      canvasUsers = new List<String>();
      int size = getCanvasUsersNumber(moderator_id);
      if (size < 0)
        return -1; //error

      IntPtr[] namesPtrs = new IntPtr[size];
      int ret = getCanvasUsers(moderator_id, namesPtrs);
      if (ret != size)
      {
        foreach (IntPtr pChar in namesPtrs)
          deleteChar(pChar);
        return -2; //different sizes
      }
      for (int i = 0; i < namesPtrs.Length; i++)
      {
        String canvasUser = Marshal.PtrToStringAnsi(namesPtrs[i]);
        deleteChar(namesPtrs[i]);
        namesPtrs[i] = IntPtr.Zero;
        canvasUsers.Add(canvasUser);
      }
      return 0;
    }

    public static int GetCanvasUserId(string name, out int ret)
    {
      ret = -1;
      int user_id = getCanvasUserId(name, ref ret);

      return user_id;
    }

    //Params
    public static Params GetParams(int canvas_id, int user_id, out int ret)
    {
      if (checkCanvasByUserId(canvas_id, user_id) != 0)
      {
        ret = -1;
        return null;
      }
      int w = -1, h = -1, m = -1, re = -1, g = -1, b = -1, siz = -1;
      double ran = -1;
      bool sm = false;

      ret = getParams(canvas_id, ref w, ref h, ref ran, ref sm, ref m, ref re, ref g, ref b, ref siz);
      Params p = new Params { canvas_id = canvas_id, width = w, height = h, range = ran, smooth = sm, mult = m, red = re, green = g, blue = b, size = siz};
      return p;
    }

    public static int CreateParams(Params par, int user_id)
    {
      if (checkCanvasByUserId(par.canvas_id, user_id) != 0)
        return -1;
      int ret = createParams(par.canvas_id, par.width, par.height, par.range, par.smooth, par.mult, par.red, par.green, par.blue, par.size);
      return ret;
    }
    public static int UpdateParams(Params par, int user_id)
    {
      if (checkCanvasByUserId(par.canvas_id, user_id) != 0)
        return -1;
      int ret = updateParams(par.canvas_id, par.width, par.height, par.range, par.smooth, par.mult, par.red, par.green, par.blue, par.size);
      return ret;
    }
  }
}
