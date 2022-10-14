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
    //public const string CppFunctionsDLL = @"..\x64\Debug\CppLandscape.dll"; //Main
    //public const string CppFunctionsDLL = @"C:\Users\arsen\source\repos\CppInCs\x64\Debug\Cpp.dll"; //Cpp
    //public const string CppFunctionsDLL = @"C:\Users\arsen\source\repos\CppInCs\x64\Debug\QtCppLibrary.dll"; //Qt
    const string CppFunctionsDLL = LandscapeService.CppFunctionsDLL;

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
