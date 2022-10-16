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
using WebLandscape.RequestSchemas;
using Microsoft.AspNetCore.Authorization;

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1")]
  [Authorize(Roles = "canvas_user")]
  public class LandscapeController : ControllerBase
  {
    private static readonly string[] Summaries = new[]
    {
      "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
    };

    private readonly ILogger<LandscapeController> _logger;

    public LandscapeController(ILogger<LandscapeController> logger)
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

    [Authorize(Roles = "canvas_user,moderator")]
    [HttpGet("Landscapes/{id}")]
    public async Task<ActionResult<Landscape>> GetLandscape(int id)
    {
      Landscape landscape = LandscapeService.GetLandscape(id, out int ret);

      if (ret == 0)
        return Ok(landscape);
      else
        return BadRequest(landscape);
    }

    [Authorize(Roles = "canvas_user,moderator")]
    [HttpGet("Landscapes")]
    //public List<CanvasIdName> GetLandscapesByUserId(int user_id = -1)
    public async Task<IActionResult> GetLandscapesByUserId(int? user_id, int? size, bool? smoothing, String name = "Name", int? red = 20, int? green = 150, int? blue = 20)
    {
      //Get Landscapes list by user_id
      if (user_id.HasValue && user_id >= 0)
      {
        List<CanvasIdName> lst = LandscapeService.GetLandscapesByUserId((int)user_id, out int ret);
        if (ret == 0)
          return Ok(lst);
        else
          return BadRequest(lst);
      }
      //Generate HeightsMap
      else if (size.HasValue && smoothing.HasValue && size > 0)
      {
        //String heightMap = LandscapeService.GenHeightsMap(new GenHeightsMapModel { Size = (int)size, Smoothing = (bool)smoothing });
        Landscape landscape = LandscapeService.GenLandscape((int)size, (bool)smoothing, name, red, green, blue);

        if (landscape != null)
          return Ok(landscape);
        else
          return BadRequest(landscape);
      }
      return BadRequest();
    }

    /*[HttpPost("GenLandscape")]
    public async Task<IActionResult> GenHeightsMap(GenHeightsMapModel model)
    {
      String heightMap = LandscapeService.GenHeightsMap(model);

      if (heightMap != null)
        return Ok(heightMap);
      else
        return BadRequest(heightMap);
    }*/

    [HttpPost("Landscapes")]
    public async Task<IActionResult> SendLandscape(CreateLandscapeSchema schema)
    {
      int ret = LandscapeService.SendLandscape(schema);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You created Landscape in DataBase", Ok().StatusCode));
      else
        return BadRequest(new Status(0, "BadRequest", "You couldn't created Landscape in DataBase", BadRequest().StatusCode));
    }

    [HttpPut("Landscapes")]
    public async Task<IActionResult> UpdateLandscape(UpdateLandscapeSchema schema)
    {
      int ret = LandscapeService.UpdateLandscape(schema);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You updated Landscape in DataBase", Ok().StatusCode));
      else
        return BadRequest(new Status(0, "BadRequest", "You couldn't updated Landscape in DataBase", BadRequest().StatusCode));
    }

    [HttpDelete("Landscapes/{id}")]
    public async Task<IActionResult> DeleteLandscape(int id)
    {
      int ret = LandscapeService.DeleteLandscape(id);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You deleted Landscape in DataBase", Ok().StatusCode));
      else
        return BadRequest(new Status(0, "BadRequest", "You couldn't delete Landscape in DataBase", BadRequest().StatusCode));
    }
  }
}
