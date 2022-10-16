using System.ComponentModel.DataAnnotations;

namespace WebLandscape.RequestSchemas
{
  public class AddUserSchema
  {
    [Required(ErrorMessage = "Не указан user_id")]
    public int user_id { get; set; }
    [Required(ErrorMessage = "Не указан moderator_id")]
    public int moderator_id { get; set; }
  }
}
