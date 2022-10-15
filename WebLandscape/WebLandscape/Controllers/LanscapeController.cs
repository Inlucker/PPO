using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices; //for Marshall
using System.Text; //for StringBuilder
using WebLandscape.ViewModels;
using WebLandscape.Models;
using Microsoft.AspNetCore.Authorization;

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1")]
  [Authorize(Roles = "canvas_user")]
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

    [AllowAnonymous]
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
    public async Task<IActionResult> Add(int a, int b)
    {
      try
      {
        return Ok(Program.AddNumbers(a, b));
      }
      catch (DllNotFoundException e)
      {
        Console.WriteLine(e.Data);
        Console.WriteLine(e.Message);
        Console.WriteLine(e.Source);
        Console.WriteLine(e.TargetSite);
        Console.WriteLine(e.TypeName);
      }
      return BadRequest();
    }

    [HttpGet("GenLandscape")]
    public void GenLandscape()
    {
      LandscapeService.genLandscape();
    }

    [HttpGet("Landscapes/{id}")]
    public async Task<IActionResult> GetLandscape(int id)
    {
      Landscape landscape = LandscapeService.getLandscape(id, out int ret);

      if (ret == 0)
        return Ok(landscape);
      else
        return BadRequest(landscape);
    }

    [HttpGet("Landscapes/")]
    //public List<CanvasIdName> GetLandscapesByUserId(int user_id = -1)
    public async Task<IActionResult> GetLandscapesByUserId(int user_id = -1)
    {
      List<CanvasIdName> lst = LandscapeService.GetLandscapesByUserId(user_id, out int ret);
      if (ret == 0)
        return Ok(lst);
      else
        return BadRequest(lst);
    }
  }
}
