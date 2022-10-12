using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1")]
  public class WeatherForecastController : ControllerBase
  {
    private static readonly string[] Summaries = new[]
    {
            "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
        };

    private readonly ILogger<WeatherForecastController> _logger;

    public WeatherForecastController(ILogger<WeatherForecastController> logger)
    {
      _logger = logger;
    }

    [HttpGet("WeatherForecast")]
    public IEnumerable<WeatherForecast> Get()
    {
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
      return 0;
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
