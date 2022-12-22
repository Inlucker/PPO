using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebLandscape.Models;// пространство имен класса User
using WebLandscape.ViewModels; // пространство имен моделей RegisterModel и LoginModel
using WebLandscape.RequestSchemas;
using System.Security.Claims;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using System.Web;

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1")]
  public class UserController : ControllerBase
  {
    [Authorize(Roles = "moderator")]
    [HttpGet("users/free")]
    public async Task<IActionResult> getFreeCanvasUsers()
    {
      ClaimsPrincipal currentUser = this.User;
      if (null != currentUser)
      {
        foreach (Claim claim in currentUser.Claims)
        {
          Console.WriteLine("CLAIM TYPE: " + claim.Type + "; CLAIM VALUE: " + claim.Value + "</br>");
        }
      }

      int ret = LandscapeService.GetFreeCanvasUsers(out List<String> canvasUsers);
      if (ret != 0)
        return BadRequest(canvasUsers);
      return Ok(canvasUsers);
    }

    [Authorize(Roles = "moderator")]
    [HttpGet("users")]
    public async Task<IActionResult> getCanvasUsers()
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest(new Status(1, "BadRequest", "You didn't log in", BadRequest().StatusCode));
      int ret = LandscapeService.GetCanvasUsers(user.Id, out List<String> canvasUsers);
      if (ret != 0)
        return BadRequest(canvasUsers);
      return Ok(canvasUsers);
    }

    [HttpPost("login")]
    public async Task<IActionResult> Login(LoginSchema schema)
    {
      User user = LandscapeService.Login(schema.Login, schema.Password);
      if (user != null)
      {
        await Authenticate(user);

        //return Ok(new String(user.Role));
        return Ok(new Status(0, "Ok", user.Role, Ok().StatusCode));
      }
      ModelState.AddModelError("", "Некорректные логин и(или) пароль");
      return BadRequest(new Status(1, "BadRequest", "You couldn't log in", BadRequest().StatusCode));
    }

    [HttpPost("register")]
    public async Task<IActionResult> Register(RegisterSchema schema)
    {
      User user = LandscapeService.Register(schema.Login, schema.Password, schema.Role);
      if (user != null)
      {
        await Authenticate(user);

        return Ok(new Status(0, "Ok", "You registered", Ok().StatusCode));
      }
      ModelState.AddModelError("", "Некорректные логин и(или) пароль");
      return BadRequest(new Status(2, "BadRequest", "You couldn't register", BadRequest().StatusCode));
    }

    private async Task Authenticate(User user)
    {
      var claims = new List<Claim>
            {
                new Claim("id", user.Id.ToString()),
                new Claim(ClaimTypes.Name, user.Login),
                new Claim("password", user.Password),
                new Claim(ClaimTypes.Role, user.Role),
                new Claim("moderator_id", user.ModeratorId.ToString())
            };
      var claimsIdentity = new ClaimsIdentity(
          claims, CookieAuthenticationDefaults.AuthenticationScheme);

      var authProperties = new AuthenticationProperties
      {
        //AllowRefresh = <bool>,
        // Refreshing the authentication session should be allowed.

        //ExpiresUtc = DateTimeOffset.UtcNow.AddMinutes(10),
        // The time at which the authentication ticket expires. A 
        // value set here overrides the ExpireTimeSpan option of 
        // CookieAuthenticationOptions set with AddCookie.

        //IsPersistent = true,
        // Whether the authentication session is persisted across 
        // multiple requests. When used with cookies, controls
        // whether the cookie's lifetime is absolute (matching the
        // lifetime of the authentication ticket) or session-based.

        //IssuedUtc = <DateTimeOffset>,
        // The time at which the authentication ticket was issued.

        //RedirectUri = <string>
        // The full path or absolute URI to be used as an http 
        // redirect response value.
      };

      await HttpContext.SignInAsync(
          CookieAuthenticationDefaults.AuthenticationScheme,
          new ClaimsPrincipal(claimsIdentity),
          authProperties);
    }

    [Authorize]
    [HttpPost("logout")]
    public async Task<IActionResult> Logout()
    {
      await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
      return Ok(new Status(0, "Ok", "You logged out", Ok().StatusCode));
    }

    [Authorize(Roles = "moderator")]
    [HttpPatch("users/moderator/add")]
    public async Task<IActionResult> AddUser(int? user_id, String user_name)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest(new Status(1, "BadRequest", "You didn't log in", BadRequest().StatusCode));
      int ret = LandscapeService.AddUser(user.Id, user_id, user_name);
      if (ret != 0)
        return BadRequest(new Status(1, "BadRequest", "You couldn't add user", BadRequest().StatusCode));
      return Ok(new Status(0, "Ok", "You added user ", Ok().StatusCode));
    }

    [Authorize(Roles = "moderator")]
    [HttpPatch("users/moderator/remove")]
    public async Task<IActionResult> RemoveUser(int? user_id, String user_name)
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest(new Status(1, "BadRequest", "You didn't log in", BadRequest().StatusCode));
      int ret = LandscapeService.RemoveUser(user_id, user_name, user.Id);
      if (ret != 0)
        return BadRequest(new Status(1, "BadRequest", "You couldn't remove user", BadRequest().StatusCode));
      return Ok(new Status(0, "Ok", "You removed user ", Ok().StatusCode));
    }

    [Authorize]
    [HttpDelete("me")]
    public async Task<IActionResult> Delete()
    {
      User user = getUser();
      if (!user.isOk())
        return BadRequest(new Status(1, "BadRequest", "You didn't log in", BadRequest().StatusCode));
      int ret = LandscapeService.DeleteUser(user.Login, user.Password);
      if (ret != 0)
        return BadRequest(new Status(1, "BadRequest", "You couldn't delete account", BadRequest().StatusCode));
      await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
      return Ok(new Status(0, "Ok", "You deleted account and logged out", Ok().StatusCode));
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
