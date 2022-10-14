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
      LandscapeService.genLandscape();
    }

    [HttpGet("Landscapes/{id}")]
    public Landscape GetLandscape(int id)
    {
      Landscape landscape = LandscapeService.getLandscape(id);

      return landscape;
    }

    [HttpGet("Landscapes/")]
    public List<CanvasIdName> GetLandscapesByUserId(int user_id = -1)
    {
      List<CanvasIdName> lst = LandscapeService.GetLandscapesByUserId(user_id);

      return lst;
    }

    [HttpPost("Login")]
    public int Login(String login, String password)
    {
      return LandscapeService.login(login, password);
    }
  }
}
