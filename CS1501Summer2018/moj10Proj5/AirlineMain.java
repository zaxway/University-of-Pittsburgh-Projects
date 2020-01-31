import java.io.*;
import java.util.*;


public class AirlineMain {

  private int numCities;
  private int numRoutes;

  private City[] cities;
  private ArrayList<Route> routes = new ArrayList<Route>();

  private Bag<Route>[] adj;
  private Route[] edgeTo;
  private int[] distTo;

  private boolean[] marked;
  private IndexMinPQ<Integer> pq;

  private double[] costTo;
  private IndexMinPQ<Double> costPQ;

  /**
   * Main Airline Constructer
   * used to avoid using static variables
   */
  public AirlineMain(String fname) {
    generateRoutes(fname);
  }

  /**
   * Generates all routes from the specific file and
   * stores them into the global variables.
   */
  public void generateRoutes(String filename) {
    numCities = 0;
    numRoutes = 0;
    String currentCity = "";
    String currentCity2 = "";
    String currentPathAndPrice = "";

    try {
      File f = new File(filename);
      Scanner console = new Scanner(f);
      // search through file
      numCities = console.nextInt();
      cities = new City[numCities];

      console.nextLine();

      for (int i = 0; i < numCities; i++) {
        currentCity = console.nextLine(); // gets the name of the city
        cities[i] = new City(i + 1, currentCity);
      }

      adj = (Bag<Route>[]) new Bag[numCities]; //
      for (int j = 0; j < numCities; j++) {
        adj[j] = new Bag<Route>();
      }

      while(console.hasNext()) {
        currentPathAndPrice = console.nextLine();
        //pathsAndPrice.add(currentPathAndPrice); // will need to split this later
        String[] str = currentPathAndPrice.split("\\s+"); // use regex to split string

        int city1 = Integer.parseInt(str[0]); // get city1 id
        int city2 = Integer.parseInt(str[1]); // get city2 id
        int pathLength = Integer.parseInt(str[2]); // get length of path
        double price = Double.parseDouble(str[3]); // get the price

        Route r = new Route(cities[city1 - 1], cities[city2 - 1], pathLength, price); // create a new route with params
        routes.add(r); // add it to list of routes.
        adj[city1 - 1].add(r);
        adj[city2 - 1].add(r);
        currentPathAndPrice = "";
        numRoutes = numRoutes + 1;
      }
    }
    catch (IOException e) {
      System.out.println("ERROR, FILE NOT FOUND!");
      System.exit(0);
    }
  }

  /**
   * 1st Option
   * used to print all the routes and Prices
   * Does not depend on the MST.
   */
  public void showALL(String fname, int costers, boolean tf) {
    System.out.println("Showing All Routes and Prices");

    ArrayList<String> cities = new ArrayList<String>();
    int numCit = 0;
    String currentCit = "";
    String currentCit2 = "";
    ArrayList<String> pathsAndPric = new ArrayList<String>();
    String currentPathAndPric = "";

    try {
      File f = new File(fname);
      Scanner console = new Scanner(f);
      // search through file
      numCit = console.nextInt();
      console.nextLine();
      for (int i = 1; i <= numCit; i++) {
        currentCit = console.nextLine();
        System.out.println(currentCit);
        cities.add(currentCit);
        currentCit = "";
      }
      while(console.hasNext()) {
        currentPathAndPric = console.nextLine();
        pathsAndPric.add(currentPathAndPric); // will need to split this later
        currentPathAndPric = "";
      }
    }
    catch (IOException e) {
      System.out.println("ERROR, FILE NOT FOUND!");
      System.exit(0);
    }

    int city1 = 0;
    int city2 = 0;
    double price = 0.0;
    int pathLength = 0;

    for (int j = 0; j < pathsAndPric.size(); j++) {
      currentPathAndPric = pathsAndPric.get(j);
      String[] str = currentPathAndPric.split("\\s+");

      city1 = Integer.parseInt(str[0]);
      city2 = Integer.parseInt(str[1]);
      pathLength = Integer.parseInt(str[2]);
      price = Double.parseDouble(str[3]);

      currentCit = cities.get(city1 - 1);
      currentCit2 = cities.get(city2 - 1);
      if (tf == false) {
        System.out.println("Path from " + currentCit + " to " + currentCit2 + " is distance of " + pathLength + " and price for this route is " + price);
      }
      else {
        if (price < costers) {
          System.out.println("Cost: " + price + " (reversed) " + currentCit2 + " " + pathLength + " " + currentCit);
        }
      }
    }
  }

  /**
   * 2nd Option
   * Uses Prim's Algorithm to generate a
   * Minimum Spanning Tree of the graph.
   * The program then prints out this minimum spanning
   * tree to the console.
   */
  public void loadMST() {
    edgeTo = new Route[numCities];
    distTo = new int[numCities];
    marked = new boolean[numCities];
    pq = new IndexMinPQ<Integer>(numCities);
    System.out.println("MINIMUM SPANNING TREE");
    System.out.println("---------------------");
    for (int i = 0; i < numCities; i++) {
      distTo[i] = Integer.MAX_VALUE;
    }
    for (int i = 0; i < numCities; i++) {
      if (!marked[i]) {
        ArrayList<String> al = new ArrayList<String>();
        ArrayList<String> resultAL = prim(al, i);
        if (al.size() > 0) {
          System.out.println();
          System.out.println("Connected Component");
          for (int b = 0; b < resultAL.size(); b++) {
            System.out.println(resultAL.get(b));
          }
        }
      }
    }
  }

  /**
   * Prim's Algorithm
   * Used to generate a minimum spanning tree
   */
    private ArrayList<String> prim(ArrayList<String> al, int s) {
        distTo[s] = 0;
        pq.insert(s, distTo[s]);
        while (!pq.isEmpty()) {
            int v = pq.delMin();
            if (v != s) {
              Route r = edgeTo[v];
              String str = r.getCity1().getCityName() + ", " + r.getCity2().getCityName() + " : " + r.getDistance();
              al.add(str);
            }
            scan(v);
        }
        return al;
    }

    // scan vertex v
    private void scan(int v) {
        marked[v] = true;
        for (Route r : adj[v]) { // edge is the route
            int w = r.other(cities[v]).getCityID() - 1;
            if (marked[w])
            {
            	continue;         // v-w is obsolete edge
            }
            if (r.getDistance() < distTo[w]) { // weight is the distance
                distTo[w] = r.getDistance();
                edgeTo[w] = r;
                if (pq.contains(w))
                {
                		pq.change(w, distTo[w]);
                }
                else
                {
                		pq.insert(w, distTo[w]);
                }
            }
            else {

            }

        }
    }

    /**
     * Helper Method to avoid repeated code
     */
    public City[] setCities(String c1, String c2) {
      City city1 = null;
      City city2 = null;
      for (int i = 0; i < numCities; i++) {
        if (cities[i].getCityName().equals(c1)) {
          city1 = cities[i];
        }
        else if (cities[i].getCityName().equals(c2)) {
          city2 = cities[i];
        }
      }
      City[] c = new City[2];
      c[0] = city1;
      c[1] = city2;
      return c;
    }

    /**
     * 3rd Option
     * Uses Dijkstra's algorithm to retrieve the shortest
     * path using distance as the main weight.
     */
    public void shortestPath(String c1, String c2) {
      System.out.println("SHORTEST DISTANCE PATH from " + c1 + " to " + c2 + ".");
      System.out.println("---------------------");
      City[] twoCities = setCities(c1, c2);
      City city1 = twoCities[0];
      City city2 = twoCities[1];
      if (c1.equals(c2) || city1 == null || city2 == null) {
        System.out.println("Invalid city choice!");
        return;
      }
      distTo = new int[numCities];
      edgeTo = new Route[numCities];
      for(int i = 0; i < numCities; i++) {
        distTo[i] = Integer.MAX_VALUE;
      }
      distTo[city1.getCityID() - 1] = 0;
      pq = new IndexMinPQ<Integer>(numCities);
      pq.insert(city1.getCityID() - 1, distTo[city1.getCityID() - 1]);
      while(!pq.isEmpty()) {
        int v = pq.delMin();
        for (Route r : adj[v]) {
          relaxDistance(r,v);
        }
      }
      if (distTo[city2.getCityID() - 1] == Integer.MAX_VALUE) {
        System.out.println("No path found!");
        return;
      }
      System.out.println("Shortest distance from " + c1 + " to " + c2 + " is " + distTo[city2.getCityID() - 1]);
      City currentCity = city2;
      Route newRoute = edgeTo[city2.getCityID() - 1];
      System.out.println("In reverse order");
      while (newRoute != null) {
        System.out.print(currentCity.getCityName() + " " + newRoute.getDistance() + " ");
        currentCity = newRoute.other(currentCity);
        newRoute = edgeTo[currentCity.getCityID() - 1];
      }
      System.out.print(currentCity.getCityName());
    }

    // relax edge e and update pq if changed
    private void relaxDistance(Route r, int v) {
        City city2 = r.other(cities[v]);
        int w = city2.getCityID() - 1;
        if (distTo[w] > distTo[v] + r.getDistance()) {
            distTo[w] = distTo[v] + r.getDistance();
            edgeTo[w] = r;
            if (pq.contains(w)) pq.change(w, distTo[w]);
            else                pq.insert(w, distTo[w]);
        }
    }

    /**
     * 4th Option
     * Uses Dijkstra's algorithm to retrieve the cheapest
     * path using price as the main weight.
     */
     public void cheapestPath(String c1, String c2) {
      System.out.println("CHEAPEST PATH from " + c1 + " to " + c2 + ".");
      System.out.println("---------------------");
      City[] twoCities = setCities(c1, c2);
      City city1 = twoCities[0];
      City city2 = twoCities[1];

      if (c1.equals(c2) || city1 == null || city2 == null) {
        System.out.println("Invalid city choice!");
        return;
      }
      costTo = new double[numCities];
      edgeTo = new Route[numCities];
      for(int i = 0; i < numCities; i++) {
        costTo[i] = Double.POSITIVE_INFINITY;
      }
      costTo[city1.getCityID() - 1] = 0;
      costPQ = new IndexMinPQ<Double>(numCities);
      costPQ.insert(city1.getCityID() - 1, costTo[city1.getCityID() - 1]);
      while(!costPQ.isEmpty()) {
        int v = costPQ.delMin();
        for (Route r : adj[v]) {
          relaxCost(r,v);
        }
      }
      if (costTo[city2.getCityID() - 1] == Double.POSITIVE_INFINITY) {
        System.out.println("No path found!");
        return;
      }
      System.out.println("Best price from " + c1 + " to " + c2 + " is " + costTo[city2.getCityID() - 1]);
      Route newRoute = edgeTo[city2.getCityID() - 1];
      City currentCity = city2;
      System.out.println("In reverse order");
      while (newRoute != null) {
        System.out.print(currentCity.getCityName() + " " + newRoute.getPrice() + " ");
        currentCity = newRoute.other(currentCity);
        newRoute = edgeTo[currentCity.getCityID() - 1];
      }
      System.out.print(currentCity.getCityName());
    }

    // relax edge e and update pq if changed
    private void relaxCost(Route r, int v) {
        City city2 = r.other(cities[v]);
        int w = city2.getCityID() - 1;
        if (costTo[w] > costTo[v] + r.getPrice()) {
            costTo[w] = costTo[v] + r.getPrice();
            edgeTo[w] = r;
            if (costPQ.contains(w)) costPQ.change(w, costTo[w]);
            else                costPQ.insert(w, costTo[w]);
        }
    }

    /**
     * 5th Option
     * Uses Breadth first search to find the least Number
     * of hops from one vertex in the graph to a different
     * vertex in the graph. This is not the same as the shortest
     * path. We are looking for how can we get to the end vertex
     * by without taking multiple paths or cycling across the entire
     * graph.
     */
    public void leastHopsPath(String c1, String c2) {
      System.out.println("FEWEST HOPS from " + c1 + " to " + c2 + ".");
      System.out.println("---------------------");
      City[] twoCities = setCities(c1, c2);
      City city1 = twoCities[0];
      City city2 = twoCities[1];
      if (c1.equals(c2) || city1 == null || city2 == null) {
        System.out.println("Invalid city choice!");
        return;
      }

      marked = new boolean[numCities];
      distTo = new int[numCities];
      edgeTo = new Route[numCities];

      for(int i = 0; i < numCities; i++) {
        distTo[i] = Integer.MAX_VALUE;
      }
      bfs(city1.getCityID() -1);

      if (distTo[city2.getCityID() - 1] == Integer.MAX_VALUE) {
        System.out.println("No path found!");
        return;
      }

      System.out.println("Fewest hops from " + c1 + " to " + c2 + " is " + distTo[city2.getCityID() - 1]);
      City currentCity = city2;
      Route newRoute = edgeTo[city2.getCityID() - 1];
      System.out.println("In reverse order");
      while (newRoute != null) {
        System.out.print(currentCity.getCityName() + " ");
        currentCity = newRoute.other(currentCity);
        newRoute = edgeTo[currentCity.getCityID() - 1];
      }
      System.out.print(currentCity.getCityName());
    }

    private void bfs(int s) {
        Queue<Integer> q = new Queue<Integer>();
        distTo[s] = 0;
        marked[s] = true;
        q.enqueue(s);

        while (!q.isEmpty()) {
            int v = q.dequeue();
            for (Route r : adj[v]) {
              int w = r.other(cities[v]).getCityID() - 1;
                if (!marked[w]) {
                    edgeTo[w] = r;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.enqueue(w);
                }
            }
        }
    }

    /**
     * Helper Method for Adding and Removing Routes.
     */
    public void updateADJandRoutes(City city1, City city2, Route r, Route newRoute, boolean add, boolean delete) {
      if (add) {
        routes.add(r);
        adj[city1.getCityID() - 1].add(r);
        adj[city2.getCityID() - 1].add(r);
        numRoutes = numRoutes + 1;
      }
      else if (delete) {
        //adj[city1.getCityID() - 1].remove(newRoute);
        //adj[city2.getCityID() - 1].remove(newRoute);
        routes.remove(newRoute);
        numRoutes = numRoutes - 1;
      }
    }

    /**
     * 7th Option
     * Adds a route to the graph. Asks the user for input on
     * both the cities he wishes to add a path to, the distance of
     * the path, and the cost of the path. This method will create
     * a new route object, and then add it to the bag and then to the
     * ArrayList of Routes.
     */
    public void addRoute(String c1, String c2, int distance, double price) {
      City[] twoCities = setCities(c1, c2);
      City city1 = twoCities[0];
      City city2 = twoCities[1];

      if (c1.equals(c2) || city1 == null || city2 == null || distance < 0 || price < 0) {
        System.out.println("Invalid city choice!");
        return;
      }
      Route r = new Route(city1, city2, distance, price);
      updateADJandRoutes(city1, city2, r, null, true, false);
    }

    /**
     * 8th Option
     * Removes a route from the graph. Asks the user for input on
     * both the cities he wishes to add a path to, the distance of
     * the path, and the cost of the path. This method will search
     * through all the routes within the bag, and then retrieve that
     * route. It shall then delete the route from the bag and the
     * arraylist of routes.
     */
    public void deleteRoute(String c1, String c2) {
      City[] twoCities = setCities(c1, c2);
      City city1 = twoCities[0];
      City city2 = twoCities[1];

      if (c1.equals(c2) || city1 == null || city2 == null) {
        System.out.println("Invalid city choice!");
        return;
      }
      Route newRoute = null;
      for (Route r : adj[city1.getCityID() - 1]) {
        if (r.other(city1).equals(city2)) {
          newRoute = r;
          break;
        }
      }
      updateADJandRoutes(city1, city2, null, newRoute, false, true);
    }

    /**
     * Extra Credit Option.
     * This method allows you to add a new city (vertex) to the graph.
     * However, it does not automatically add a path to it.
     * You can do that by using the add route method, and that
     * will add the specified route to it. 
     */
    public void addCity(String newCity) {
      if (newCity == null || newCity.length() == 0) {
        System.out.println("Enter a valid city that is not null or of length 0.");
        return;
      }
      int index = numCities + 1; // index of new city
      City city1 = new City(index, newCity);
      if (numCities >= cities.length) {
        int newSize = 2 * cities.length;
        City[] temp = new City[newSize];
        Bag<Route>[] temp2 = (Bag<Route>[]) new Bag[newSize];
        for (int i = 0; i < numCities; i++) {
          temp[i] = cities[i];
          temp2[i] = adj[i];
        }
        cities = temp;
        adj = temp2;
      }

      cities[numCities] = city1;
      adj[numCities] = new Bag<Route>();
      numCities = index;
    }



  public static void main(String [] args) {
    if (args.length != 1) {
      System.out.println("Please enter in only one argument.");
      System.exit(0);
    }
    System.out.println("INPUT FILE: " + args[0]);
    System.out.println("---------------------");
    AirlineMain a = new AirlineMain(args[0]);
    //a.generateRoutes(args[0]);
    Scanner console = new Scanner(System.in);
    System.out.println("Enter a number.");
    System.out.println("1. See all direct routes and prices.");
    System.out.println("2. Find the minimum spanning tree.");
    System.out.println("3. Find the shortest distance path.");
    System.out.println("4. Find the path that will cost the least.");
    System.out.println("5. Find the path that will have the fewest hops");
    System.out.println("6. Choose a cost and find trips under that cost.");
    System.out.println("7. Add a route.");
    System.out.println("8. Remove a route.");
    System.out.println("9. Add a City");
    System.out.println("10. Quit the program.");

    while (true) {
      System.out.println();
      System.out.print("Enter Number: ");
      int input = console.nextInt();
      System.out.println();
      if (input == 1) {
        a.showALL(args[0], 0, false);
      }
      else if (input == 2) {
        a.loadMST();
      }
      else if (input == 3) {
        console.nextLine();
        System.out.println("Enter first City: ");
        String city1 = console.nextLine();
        System.out.println("Enter second City: ");
        String city2 = console.nextLine();
        a.shortestPath(city1, city2);
      }
      else if (input == 4) {
        console.nextLine();
        System.out.println("Enter first City: ");
        String city1 = console.nextLine();
        System.out.println("Enter second City: ");
        String city2 = console.nextLine();
        a.cheapestPath(city1, city2);
      }
      else if (input == 5) {
        console.nextLine();
        System.out.println("Enter first City: ");
        String city1 = console.nextLine();
        System.out.println("Enter second City: ");
        String city2 = console.nextLine();
        a.leastHopsPath(city1, city2);
      }
      else if (input == 6) {
        console.nextLine();
        System.out.println("Choose a cost: ");
        int choiceCost = console.nextInt();
        a.showALL(args[0], choiceCost, true);
      }
      else if (input == 7) {
        console.nextLine();
        System.out.println("Enter first City: ");
        String city1 = console.nextLine();
        System.out.println("Enter second City: ");
        String city2 = console.nextLine();
        System.out.println("Enter the distance between the two cities: ");
        int distances = console.nextInt();
        System.out.println("Enter the price between the two cities: ");
        double prices = console.nextDouble();
        a.addRoute(city1, city2, distances, prices);
      }
      else if (input == 8) {
        console.nextLine();
        System.out.println("Enter first City: ");
        String city1 = console.nextLine();
        System.out.println("Enter second City: ");
        String city2 = console.nextLine();
        a.deleteRoute(city1, city2);
      }
      else if (input == 9) {
        console.nextLine();
        System.out.println("Enter new City: ");
        String newCity = console.nextLine();
        a.addCity(newCity);
      }
      else if (input == 10) {
        break;
      }
    }

    System.exit(0);
  }
}
