namespace WebLandscape.Models
{
  public class User
  {
    public int Id { get; set; }
    public string Login { get; set; }
    public string Password { get; set; }
    public string Role { get; set; }
    public int ModeratorId { get; set; }
  }
}
