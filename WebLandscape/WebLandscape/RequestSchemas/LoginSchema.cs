using System.ComponentModel.DataAnnotations;

namespace WebLandscape.RequestSchemas
{
  public class LoginSchema
  {
    [Required(ErrorMessage = "Не указан Login")]
    public string Login { get; set; }

    [Required(ErrorMessage = "Не указан пароль")]
    [DataType(DataType.Password)]
    public string Password { get; set; }
  }
}
