using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebLandscape.Models;// пространство имен класса User
using WebLandscape.ViewModels; // пространство имен моделей RegisterModel и LoginModel
using System.Security.Claims;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;

namespace WebLandscape.Controllers
{
  [ApiController]
  [Route("api/v1")]
  public class UserController : ControllerBase
  {
    [HttpPost("login")]
    public async Task<IActionResult> Login(LoginModel model)
    //public User Login(LoginModel model)
    {
      User user = LandscapeService.login(model.Login, model.Password);
      if (user != null)
      {
        await Authenticate(user);

        //return user;
        return NoContent();
        //return RedirectToAction("AddNumbers");
      }
      ModelState.AddModelError("", "Некорректные логин и(или) пароль");
      //return user;
      return NoContent();
    }

    [HttpPost("register")]
    public async Task<IActionResult> Register(RegisterModel model)
    {
      User user = LandscapeService.register(model.Login, model.Password, model.Role);
      if (user != null)
      {
        await Authenticate(user);

        return NoContent();
      }
      ModelState.AddModelError("", "Некорректные логин и(или) пароль");
      return NoContent();
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

    [HttpPost("logout")]
    public async Task<IActionResult> Logout()
    {
      await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
      return NoContent();
      //return RedirectToAction("Login", "Account");
    }
  }
}
