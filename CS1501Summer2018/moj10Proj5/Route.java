public class Route implements Comparable<Route> {
  private final City city1;
  private final City city2;
  private final int distance;
  private final double price;
  public static boolean compareDistance;


  public Route(City city1, City city2, int distance, double price) {
    this.city1 = city1;
    this.city2 = city2;
    this.distance = distance;
    this.price = price;
    compareDistance = true;
  }

  public double getPrice() {
    return price;
  }

  public City getCity1() {
    return city1;
  }

  public int getDistance() {
    return distance;
  }

  public City getCity2() {
    return city2;
  }

  public City other(City vertex) {
    if (vertex.equals(city1)) {
      return city2;
    }
    else if (vertex.equals(city2)) {
      return city1;
    }
    else {
      System.out.println("ERROR!");
      return null;
    }
  }

  public int comparePrice(Route r) {
    double val = this.price - r.price;
    if (val > 0.01) {
      return 1;
    }
    else if (val < -0.01) {
      return -1;
    }
    else {
      return 0;
    }
  }

  public int compareDistances(Route r) {
    // determine how distant each route is from one another
    int result = this.distance - r.distance;
    return result;
  }

  public int compareTo(Route r) {
    if (compareDistance == true) {
      return compareDistances(r);
    }
    else {
      return comparePrice(r);
    }
  }

  // returns txt String representation in this format:
  // Pittsburgh, Allentown 127 200.00
  public String toString() {
    String result = " " + city1.getCityName() + ", " + city2.getCityName() + " " + distance + " " + price + " ";
    return result;
  }
}
