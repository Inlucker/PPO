using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Text;

namespace WebLandscape
{
  public class Program
  {
    //public const string CppFunctionsDLL = @"C:\Users\arsen\source\repos\WebLandscape\x64\Debug\CppLandscape.dll";
    public const string CppFunctionsDLL = @"..\x64\Debug\CppLandscape.dll"; //Main
    //public const string CppFunctionsDLL = @"C:\Users\arsen\source\repos\CppInCs\x64\Debug\Cpp.dll"; //Cpp
    //public const string CppFunctionsDLL = @"C:\Users\arsen\source\repos\CppInCs\x64\Debug\QtCppLibrary.dll"; //Qt

    //Testing funcs
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    //[DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int AddNumbers(int a, int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int SubNumbers(int a, int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void WriteToFile(String file_name, String file_text);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr myconvertmethod(IntPtr pCanvasBL, int id);
    [DllImport(CppFunctionsDLL, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern void MyConvert(StringBuilder sb);
    [DllImport(CppFunctionsDLL, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.LPStr)]
    public static extern string MyConvert2(string source, string dest);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetInput(double[,] arrayData);

    //Testing class funcs
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateTest();
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int TestVal(IntPtr value);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int TestMethod(IntPtr value, int param);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DeleteTest(IntPtr value);


    //Landscape funcs
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateLandscapeCanvas();
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int generateLandscapeLandscapeCanvas(IntPtr value, int size);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DeleteLandscapeCanvas(IntPtr value);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr getHeightsMapPtr(IntPtr pLandscapeCanvas);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr writeToFileHeightsMap(IntPtr pHeightsMap, String file_name);

    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int loginBaseController(String login, String password);

    //CanvasBl
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr getCanvasBL(int id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int getIdCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int getUserIdCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void getNameCanvasBL(IntPtr pCanvasBL, StringBuilder sb);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr getHeightsMapCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr getHeightsMapPointsCanvasBL(IntPtr pCanvasBL);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void getColorCanvasBL(IntPtr pChar, ref int r, ref int g, ref int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void deleteChar(IntPtr pChar);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void deleteCanvasBL(IntPtr pCanvasBL);

    //List<CanvasBL>
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int getLandscapesNumberByUserId(int user_id);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void getLandscapesByUserId(int user_id, int[] idArray, int[,] strArray);

    public static void Main(string[] args)
    {
      CreateHostBuilder(args).Build().Run();
    }

    public static IHostBuilder CreateHostBuilder(string[] args) =>
        Host.CreateDefaultBuilder(args)
            .ConfigureWebHostDefaults(webBuilder =>
            {
              webBuilder.UseStartup<Startup>();
            });
  }
}
