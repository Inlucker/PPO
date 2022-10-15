using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Text;
using WebLandscape.Models;
using WebLandscape.ViewModels;

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


    //List<CanvasBL>
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getLandscapesNumberByUserId(int user_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getLandscapesByUserId(int user_id, int[] idArray, int[,] strArray);


    //HeightsMap
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr genHeightsMap(int size, bool smooth);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr genCanvasBL(int size, bool smooth, ref int returnCode); //returns canvasBL pointer


    //Landscape
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int sendLandscape(int user_id, String name, String heights_map, String heights_map_points, int r, int g, int b);

    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int updateLandscape(int id, String name, String heights_map, String heights_map_points, int r, int g, int b);


    public static String GenHeightsMap(GenHeightsMapModel model)
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
    public static Landscape GenLandscape(int size, bool smoothing, String name, int? red, int? green, int? blue)
    {
      Landscape canvasBL = new Landscape();

      //create canvasBL
      int ret = -1;
      IntPtr pCanvasBl = genCanvasBL(size, smoothing, ref ret);
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

    public static Landscape GetLandscape(int id, out int ret_code)
    {
      ret_code = 0;
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

    public static List<CanvasIdName> GetLandscapesByUserId(int user_id, out int ret_code)
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

    public static int SendLandscape(Landscape landscape)
    {
      int res = 0;
      res = sendLandscape(landscape.user_id, landscape.name, landscape.heights_map, landscape.heights_map_points, landscape.red, landscape.green, landscape.blue);

      return res;
    }

    public static int UpdateLandscape(Landscape landscape)
    {
      int res = 0;
      res = updateLandscape(landscape.id, landscape.name, landscape.heights_map, landscape.heights_map_points, landscape.red, landscape.green, landscape.blue);

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

    public static int Delete(String login, String password)
    {
      int res = deleteUser(login, password);
      return res;
    }
  }
}
