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
using System.Security.Claims;

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1/landscapes")]
  public class LandscapeController : ControllerBase
  {
    /*private static readonly string[] Summaries = new[]
    {
      "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
    };*/

    private readonly ILogger<LandscapeController> _logger;

    public LandscapeController(ILogger<LandscapeController> logger)
    {
      _logger = logger;
    }

    /*[AllowAnonymous]
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
    }*/

    /*[HttpPost("AddNumbers")]
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
    }*/

    [Authorize(Roles = "canvas_user,moderator")]
    [HttpGet("{id}")]
    public async Task<ActionResult<Landscape>> GetLandscape(int id)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      int ret = -10;
      Landscape landscape = null;
      if (user.Role == "canvas_user")
        landscape = LandscapeService.GetLandscapeForCanvasUser(id, user.Id, out ret);
      else if (user.Role == "moderator")
        landscape = LandscapeService.GetLandscapeForModerator(id, user.Id, out ret);

      if (ret == 0)
        return Ok(landscape);
      else
        return BadRequest();
    }

    [Authorize(Roles = "canvas_user,moderator")]
    [HttpGet("")]
    public async Task<IActionResult> GetLandscapes(int? user_id)
    {
      int ret = -1;
      List<CanvasIdName> lst = new List<CanvasIdName>();
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      if (user_id.HasValue && user.Role == "moderator")
        lst = LandscapeService.GetLandscapesForModerator((int)user_id, user.Id, out ret);
      else if (user.Id >= 0 && user.Role == "canvas_user")
        lst = LandscapeService.GetLandscapesForCanvasUser(user.Id, out ret);
      if (ret == 0)
        return Ok(lst);
      else
        return BadRequest();
    }

    [Authorize(Roles = "canvas_user")]
    [HttpPost("")]
    public async Task<IActionResult> SendLandscape(CreateLandscapeSchema schema)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      int ret = LandscapeService.SendLandscape(schema, user.Id, out int canvas_id);

      if (ret == 0)
        return Ok(canvas_id);
        //return Ok(new Status(0, "Ok", "You created Landscape in DataBase", Ok().StatusCode));
      else
        return BadRequest(new Status(1, "BadRequest", "You couldn't created Landscape in DataBase", BadRequest().StatusCode));
    }

    [Authorize(Roles = "canvas_user")]
    [HttpPut("")]
    public async Task<IActionResult> UpdateLandscape(UpdateLandscapeSchema schema)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      int ret = LandscapeService.UpdateLandscape(schema, user.Id);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You updated Landscape in DataBase", Ok().StatusCode));
      else
        return BadRequest(new Status(1, "BadRequest", "You couldn't update Landscape in DataBase", BadRequest().StatusCode));
    }

    [Authorize(Roles = "canvas_user")]
    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteLandscape(int id)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      int ret = LandscapeService.DeleteLandscape(id, user.Id);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You deleted Landscape in DataBase", Ok().StatusCode));
      else
        return BadRequest(new Status(1, "BadRequest", "You couldn't delete Landscape in DataBase", BadRequest().StatusCode));
    }

    private User getUser()
    {
      User user = new User();
      ClaimsPrincipal currentUser = this.User;
      if (null != currentUser)
      {
        foreach (Claim claim in currentUser.Claims)
        {
          if (claim.Type == "id")
            user.Id = int.Parse(claim.Value);
          if (claim.Type == ClaimTypes.Name)
            user.Login = claim.Value;
          if (claim.Type == "password")
            user.Password = claim.Value;
          if (claim.Type == ClaimTypes.Role)
            user.Role = claim.Value;
          if (claim.Type == "moderator_id")
            user.ModeratorId = int.Parse(claim.Value);
        }
      }
      return user;
    }
  }
}
