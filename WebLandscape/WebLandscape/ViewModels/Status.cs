using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebLandscape.ViewModels
{
  public class Status
  {
    public Status(int c, string m, string d, int s)
    {
      code = c;
            message = m;
            description = d;
      status = s;
    }
    public int code { get; set; }
    public string message { get; set; }
    public string description { get; set; }
    public int status { get; set; }
  }
}
