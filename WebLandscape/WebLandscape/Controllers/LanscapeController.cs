using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices; //for Marshall
using System.Text; //for StringBuilder

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1")]
  public class LanscapeController : ControllerBase
  {
    private static readonly string[] Summaries = new[]
    {
            "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
        };

    private readonly ILogger<LanscapeController> _logger;

    public LanscapeController(ILogger<LanscapeController> logger)
    {
      _logger = logger;
    }

    [HttpGet("WeatherForecast")]
    public IEnumerable<WeatherForecast> Get()
    {
      Console.WriteLine("Called GetWeatherForecast");
      var rng = new Random();
      return Enumerable.Range(1, 5).Select(index => new WeatherForecast
      {
        Date = DateTime.Now.AddDays(index),
        TemperatureC = rng.Next(-20, 55),
        Summary = Summaries[rng.Next(Summaries.Length)]
      })
      .ToArray();
    }

    [HttpPost("AddNumbers")]
    public int Login(int a, int b)
    {
      try
      {
        return Program.AddNumbers(a, b); ;
      }
      catch (DllNotFoundException e)
      {
        Console.WriteLine(e.Data);
        Console.WriteLine(e.Message);
        Console.WriteLine(e.Source);
        Console.WriteLine(e.TargetSite);
        Console.WriteLine(e.TypeName);
      }
      return -1;
    }

    [HttpGet("GenLandscape")]
    public void GenLandscape()
    {
      IntPtr pLandscapeCanvas = Program.CreateLandscapeCanvas();
      Program.generateLandscapeLandscapeCanvas(pLandscapeCanvas, 33);

      IntPtr pHeightMap = Program.getHeightsMapPtr(pLandscapeCanvas);
      Program.writeToFileHeightsMap(pHeightMap, "HeightsMapGen322.txt");
      pHeightMap = IntPtr.Zero;

      Program.DeleteTest(pLandscapeCanvas);
      pLandscapeCanvas = IntPtr.Zero;
    }
    [HttpGet("GetLandscape/{id}")]
    public CanvasBL GetLandscape(int id)
    {
      //create canvasBL
      CanvasBL canvasBL = new CanvasBL();
      IntPtr pCanvasBl = Program.getCanvasBL(id);

      //canvas id
      int canvasId = Program.getIdCanvasBL(pCanvasBl);
      //Console.WriteLine(canvasId);
      canvasBL.id = canvasId;

      //canvas user_id
      canvasBL.user_id = Program.getUserIdCanvasBL(pCanvasBl);

      //canvas name
      //1
      IntPtr pChar = Program.myconvertmethod(pCanvasBl, id);
      String canvasName = Marshal.PtrToStringAnsi(pChar);
      //Console.WriteLine(canvasName);
      canvasBL.name = canvasName;
      Program.deleteChar(pChar);
      pChar = IntPtr.Zero;

      //2
      /*StringBuilder sb = new StringBuilder("Vasya was here");
      Program.MyConvert(sb);
      Console.WriteLine(sb.ToString());*/

      //3 Doesn't work with big strings
      /*StringBuilder sb2 = new StringBuilder("");
      Program.getNameCanvasBL(pCanvasBl, sb2);
      String canvasName = sb2.ToString();
      //Console.WriteLine(canvasName);
      canvasBL.name = canvasName;*/

      //canvas heights_map
      //1 Doesn't work with big strings
      /*Program.getHeightsMapCanvasBL(pCanvasBl, sb2);
      String heightsMap = sb2.ToString();
      Console.WriteLine(heightsMap);*/

      //2
      IntPtr pHeightsMapChar = Program.getHeightsMapCanvasBL(pCanvasBl);
      String heightsMapStr = Marshal.PtrToStringAnsi(pHeightsMapChar);
      //Console.WriteLine(heightsMapStr);
      canvasBL.heights_map = heightsMapStr;
      Program.deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas heights_map_points
      IntPtr pHeightsMapPointsChar = Program.getHeightsMapPointsCanvasBL(pCanvasBl);
      canvasBL.heights_map_points = Marshal.PtrToStringAnsi(pHeightsMapPointsChar);
      Program.deleteChar(pHeightsMapChar);
      pHeightsMapChar = IntPtr.Zero;

      //canvas color
      int r = 0, g = 0, b = 0;
      Program.getColorCanvasBL(pCanvasBl, ref r, ref g, ref b);
      canvasBL.red = r;
      canvasBL.green = g;
      canvasBL.blue = b;

      //delete canvasBL
      Program.deleteCanvasBL(pCanvasBl);
      pCanvasBl = IntPtr.Zero;

      return canvasBL;
    }

    [HttpGet("GetLandscapesByUserId/{user_id}")]
    public List<CanvasIdName> GetLandscapesByUserId(int user_id)
    {
      List<CanvasIdName> lst = new List<CanvasIdName>();

      //Testing
      /*double[,] array = new double[4096, 4096];
      for (int i = 0; i < 4096; i++)
        for (int j = 0; j < 4096; j++)
          array[i, j] = 0;
      Program.SetInput(array);*/

      int size = Program.getLandscapesNumberByUserId(user_id);

      int[] idArray = new int[size];
      int[,] nameArray = new int[size, 256];
      Program.getLandscapesByUserId(user_id, idArray, nameArray);
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

    [HttpPost("Login")]
    public int Login(String login, String password)
    {
      try
      {
        return Program.loginBaseController(login, password);
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
      }
      return 0;
    }
  }
}
