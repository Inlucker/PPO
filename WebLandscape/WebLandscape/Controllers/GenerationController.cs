using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
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
  [Route("api/v1")]
  [ApiController]
  public class GenerationController : ControllerBase
  {
    [AllowAnonymous]
    [HttpGet("generation")]
    public async Task<IActionResult> GenLandscape(int size = 9, double range = 24.0, bool smoothing = true, String name = "Name", int? red = 20, int? green = 150, int? blue = 20)
    {
      if (size > 0)
      {
        Landscape landscape = LandscapeService.GenLandscape((int)size, range, (bool)smoothing, name, red, green, blue);

        if (landscape != null)
          return Ok(landscape);
        else
          return BadRequest(landscape);
      }
      return BadRequest();
    }
  }
}
