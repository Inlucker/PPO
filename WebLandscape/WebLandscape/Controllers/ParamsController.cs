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
using System.Security.Claims;

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
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      Params par = LandscapeService.GetParams(canvas_id, user.Id, out int ret);

      if (ret == 0)
        return Ok(par);
      else
        return BadRequest(new Status(1, "BadRequest", "You couldn't get params", BadRequest().StatusCode));
    }


    [HttpPost("")]
    public async Task<ActionResult<Landscape>> CreateParams(Params par)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      int ret = LandscapeService.CreateParams(par, user.Id);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You created params", Ok().StatusCode));
      else
        return BadRequest(new Status(1, "BadRequest", "You couldn't create params", BadRequest().StatusCode));
    }

    [HttpPut("")]
    public async Task<ActionResult<Landscape>> UpdateParams(Params par)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest();
      int ret = LandscapeService.UpdateParams(par, user.Id);

      if (ret == 0)
        return Ok(new Status(0, "Ok", "You updated params", Ok().StatusCode));
      else
        return BadRequest(new Status(1, "BadRequest", "You couldn't update params", BadRequest().StatusCode));
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
