﻿using System.ComponentModel.DataAnnotations;

namespace WebLandscape.ViewModels
{
  public class RegisterModel
  {
    [Required(ErrorMessage = "Не указан Login")]
    public string Login { get; set; }

    [Required(ErrorMessage = "Не указан пароль")]
    [DataType(DataType.Password)]
    public string Password { get; set; }
    [Required(ErrorMessage = "Не указана роль")]
    public string Role { get; set; }
  }
}