using System;
using System.ComponentModel.DataAnnotations;

namespace WebLandscape.RequestSchemas
{
  public class UpdateLandscapeSchema
  {
    [Required(ErrorMessage = "Не указан id")]
    public int id { get; set; }
    [Required(ErrorMessage = "Не указан name")]
    public String name { get; set; }
    [Required(ErrorMessage = "Не указан heights_map")]
    public String heights_map { get; set; }
    [Required(ErrorMessage = "Не указан heights_map_points")]
    public String heights_map_points { get; set; }
    [Required(ErrorMessage = "Не указан red")]
    public int red { get; set; }
    [Required(ErrorMessage = "Не указан green")]
    public int green { get; set; }
    [Required(ErrorMessage = "Не указан blue")]
    public int blue { get; set; }
  }
}
