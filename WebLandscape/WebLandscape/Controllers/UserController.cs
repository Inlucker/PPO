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
      int ret = LandscapeService.GetFreeCanvasUsers(out List<String> canvasUsers);
      if (ret != 0)
        return BadRequest(canvasUsers);
      return Ok(canvasUsers);
    }

    [Authorize(Roles = "moderator")]
    [HttpGet("users/{moderator_id}")]
    public async Task<IActionResult> getCanvasUsers(int moderator_id)
    {
      //List<User> canvasUser = new List<User>();
      int ret = LandscapeService.GetCanvasUsers(moderator_id, out List<String> canvasUsers);
      if (ret != 0)
        return BadRequest(canvasUsers);
      return Ok(canvasUsers);
    }

    [HttpPost("login")]
    public async Task<IActionResult> Login(LoginSchema schema)
    //public User Login(LoginModel model)
    {
      User user = LandscapeService.Login(schema.Login, schema.Password);
      if (user != null)
      {
        await Authenticate(user);

        return Ok(new Status(0, "Ok", "You logged in", Ok().StatusCode));
        //return user;
        //return CreatedAtAction("Login", new { id = model.Login }, model);
        //return NoContent();
        //return RedirectToAction("AddNumbers");
      }
      ModelState.AddModelError("", "Некорректные логин и(или) пароль");
      return BadRequest(new Status(1, "BadRequest", "You couldn't log in", BadRequest().StatusCode));
      //return user;
      //return NoContent();
      //return BadRequest();
      //return CreatedAtAction("Login", new { id = model.Login }, model);
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
                new Claim(ClaimTypes.Name, user.Login),
                new Claim(ClaimTypes.Role, user.Role)
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
      //return NoContent();
      //return RedirectToAction("Login", "Account");
    }

    [Authorize(Roles = "moderator")]
    [HttpPatch("users/add")]
    public async Task<IActionResult> AddUser(AddUserSchema schema)
    {
      int ret = LandscapeService.AddUser(schema.user_id, schema.moderator_id);
      if (ret != 0)
        return BadRequest(new Status(0, "BadRequest", "You couldn't add user", BadRequest().StatusCode));
      return Ok(new Status(0, "Ok", "You added user ", Ok().StatusCode));
    }

    [Authorize(Roles = "moderator")]
    [HttpPatch("users/remove/{user_id}")]
    public async Task<IActionResult> RemoveUser(int user_id)
    {
      int ret = LandscapeService.RemoveUser(user_id);
      if (ret != 0)
        return BadRequest(new Status(0, "BadRequest", "You couldn't remove user", BadRequest().StatusCode));
      return Ok(new Status(0, "Ok", "You removed user ", Ok().StatusCode));
    }

    [Authorize]
    [HttpPost("delete")]
    public async Task<IActionResult> Delete(LoginSchema schema)
    {
      int ret = LandscapeService.DeleteUser(schema.Login, schema.Password);
      if (ret != 0)
        return BadRequest(new Status(0, "BadRequest", "You couldn't delete account", BadRequest().StatusCode));
      await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
      return Ok(new Status(0, "Ok", "You deleted account and logged out", Ok().StatusCode));
      //return NoContent();
      //return RedirectToAction("Login", "Account");
    }
  }
}
