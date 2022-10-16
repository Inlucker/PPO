using System.ComponentModel.DataAnnotations;

namespace WebLandscape.RequestSchemas
{
  public class GenHeightsMapSchema
  {
    [Required(ErrorMessage = "Не указан Size")]
    public int Size { get; set; }
    [Required(ErrorMessage = "Не указан Smoothing")]
    public bool Smoothing { get; set; }
  }
}
