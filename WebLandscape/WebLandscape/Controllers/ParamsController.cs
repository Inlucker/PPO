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
  [Route("api/v1/params")]
  [ApiController]
  [Authorize(Roles = "canvas_user")]
  public class ParamsController : ControllerBase
  {
    [HttpGet("{canvas_id}")]
    public async Task<ActionResult<Landscape>> GetParams(int canvas_id)
    {
      Params par = LandscapeService.GetParams(canvas_id, out int ret);

      if (ret == 0)
        return Ok(par);
      else
        return BadRequest(new Status(0, "BadRequest", "You couldn't get params", BadRequest().StatusCode));
    }


    [HttpPost("")]
    public async Task<ActionResult<Landscape>> GetParams(Params par)
    {
      int ret = LandscapeService.CreateParams(par);

      if (ret == 0)
        return Ok(new Status(0, "BadRequest", "You created params", BadRequest().StatusCode));
      else
        return BadRequest(new Status(0, "BadRequest", "You couldn't create params", BadRequest().StatusCode));
    }
  }
}
