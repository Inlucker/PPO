using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebLandscape.ViewModels
{
  public class Landscape
  {
    public int id { get; set; }
    public int user_id { get; set; }
    public String name { get; set; }
    public String heights_map { get; set; }
    public String heights_map_points { get; set; }
    public int red { get; set; }
    public int green { get; set; }
    public int blue { get; set; }
  }
}
