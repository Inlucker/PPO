namespace WebLandscape.Models
{
  public class User
  {
    public int Id { get; set; } = -1;
    public string Login { get; set; } = null;
    public string Password { get; set; } = null;
    public string Role { get; set; } = null;
    public int ModeratorId { get; set; } = -1;
    public bool isOk()
    {
      return (Id != -1 && Login != null && Password != null && Role != null && ModeratorId != -1);
    }
  }
}