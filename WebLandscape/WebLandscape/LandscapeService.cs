﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Text;

namespace WebLandscape
{
  public class LandscapeService
  {
    public const string CppFunctionsDLL = @"..\x64\Debug\CppLandscape.dll";

    //Landscape funcs
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

    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int getUserId(String login, String password);


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
    static extern void getLandscapesByUserId(int user_id, int[] idArray, int[,] strArray);

    public static void genLandscape()
    {
      IntPtr pLandscapeCanvas = createLandscapeCanvas();
      generateLandscapeLandscapeCanvas(pLandscapeCanvas, 33);

      IntPtr pHeightMap = getHeightsMapPtr(pLandscapeCanvas);
      writeToFileHeightsMap(pHeightMap, "HeightsMapGen322.txt");
      pHeightMap = IntPtr.Zero;

      Program.DeleteTest(pLandscapeCanvas);
      pLandscapeCanvas = IntPtr.Zero;
    }

    public static Landscape getLandscape(int id )
    {
      Landscape canvasBL = new Landscape();

      //create canvasBL
      IntPtr pCanvasBl = LandscapeService.getCanvasBL(id);

      //canvas id
      int canvasId = LandscapeService.getIdCanvasBL(pCanvasBl);
      if (canvasId == -1)
      {
        return null; //Вернуть ошибку
      }
      canvasBL.id = canvasId;

      //canvas user_id
      canvasBL.user_id = LandscapeService.getUserIdCanvasBL(pCanvasBl);

      //canvas name
      IntPtr pChar = LandscapeService.getNameCanvasBL(pCanvasBl);
      String canvasName = Marshal.PtrToStringAnsi(pChar);
      canvasBL.name = canvasName;
      LandscapeService.deleteChar(pChar);
      pChar = IntPtr.Zero;

      //canvas heights_map
      IntPtr pHeightsMapChar = LandscapeService.getHeightsMapCanvasBL(pCanvasBl);
      String heightsMapStr = Marshal.PtrToStringAnsi(pHeightsMapChar);
      canvasBL.heights_map = heightsMapStr;
      LandscapeService.deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas heights_map_points
      IntPtr pHeightsMapPointsChar = LandscapeService.getHeightsMapPointsCanvasBL(pCanvasBl);
      canvasBL.heights_map_points = Marshal.PtrToStringAnsi(pHeightsMapPointsChar);
      LandscapeService.deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas color
      int r = 0, g = 0, b = 0;
      LandscapeService.getColorCanvasBL(pCanvasBl, ref r, ref g, ref b);
      canvasBL.red = r;
      canvasBL.green = g;
      canvasBL.blue = b;

      //delete canvasBL
      LandscapeService.deleteCanvasBL(pCanvasBl);
      pCanvasBl = IntPtr.Zero;

      return canvasBL;
    }

    public static List<CanvasIdName> GetLandscapesByUserId(int user_id)
    {
      List<CanvasIdName> lst = new List<CanvasIdName>();
      if (user_id < 0)
        return lst;

      int size = LandscapeService.getLandscapesNumberByUserId((int)user_id);

      int[] idArray = new int[size];
      int[,] nameArray = new int[size, 256];
      LandscapeService.getLandscapesByUserId((int)user_id, idArray, nameArray);
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

    public static int login(String login, String password)
    {
      return getUserId(login, password);
      /*try
      {
        return LandscapeService.loginBaseController(login, password);
      }
      catch (System.Runtime.InteropServices.SEHException e)
      {
        Console.WriteLine(e.Data);
        Console.WriteLine(e.ErrorCode);
        Console.WriteLine(e.HelpLink);
        Console.WriteLine(e.HResult);
        Console.WriteLine(e.Message);
        Console.WriteLine(e.Source);
        Console.WriteLine(e.StackTrace);
        Console.WriteLine(e.TargetSite);
      }*/
    }
  }
}
