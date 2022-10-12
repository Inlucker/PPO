using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WebLandscape
{
  public class Program
  {
    //public const string CppFunctionsDLL = @"C:\Users\arsen\source\repos\WebLandscape\x64\Debug\CppLandscape.dll";
    public const string CppFunctionsDLL = @"..\x64\Debug\CppLandscape.dll";

    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    //[DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int AddNumbers(int a, int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int SubNumbers(int a, int b);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void WriteToFile(String file_name, String file_text);


    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateTest();
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int TestVal(IntPtr value);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern int TestMethod(IntPtr value, int param);
    [DllImport(CppFunctionsDLL, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DeleteTest(IntPtr value);


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
