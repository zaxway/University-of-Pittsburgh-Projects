public class City {
  private int id;
  private String cityName;

  public City(int i, String cn) {
    this.id = i;
    this.cityName = cn;
  }

  public int getCityID() {
    return id;
  }

  public String getCityName() {
    return cityName;
  }
}
