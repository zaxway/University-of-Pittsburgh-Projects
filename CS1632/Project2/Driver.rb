require_relative "City"

class Driver
  attr_accessor :books, :dinoToy, :classes, :location, :direction, :locationArr

  def initialize(counter)
    @currentDriver = counter;
    @randomNum = 0;
    @books = 0; # number of books
    @dinoToy = 0; # number of dinosaur toys
    @classes = 1; # starts out with one class
    @location = ""; # String
  end

  def getRandom()
    @randomNum = 0 + Random.rand(4);
    return @randomNum;
  end

  def getLocation()
    locations = ["Hillman", "Museum", "Cathedral", "Hospital"];
    @location = locations[getRandom()]; # gets our location
    return @location;
  end

  def addBooksClassesToys()
    if(@location == "Hillman")
      @books = @books + 1;
    elsif (@location == "Museum")
      @dinoToy = @dinoToy + 1;
    elsif (@location == "Cathedral")
      @classes = @classes * 2;
    end
  end
  
  def setFirstLocation()
    if (getRandom() != nil)
      getLocation();
      addBooksClassesToys();
      return true
    else
      return false
    end
  end

  def setDiffLocation(newLocation)
    if (newLocation != nil && (newLocation == "Hospital" || newLocation == "Cathedral" || newLocation == "Hillman" || newLocation == "Museum"))
      @location = newLocation;
    end
  end

  def checkIfGone(oldLocation, newLocation)
    if (monroeville(oldLocation, newLocation) || downtown(oldLocation, newLocation))
      return false
    else
      return true
    end
  end

  def movingDriver()
    city2 = City.new;
    direction = city2.getNewDirection(@location);
    locationArr = city2.getNewLocation(@location, direction);
    puts "Driver #{@currentDriver} heading from #{locationArr[0]} to #{locationArr[1]} via #{locationArr[2]}";
    setDiffLocation(locationArr[1]);
    addBooksClassesToys();
    tf = checkIfGone(locationArr[0], locationArr[1]);
    return tf;
  end

  def getCurrrentDriver()
    return @currentDriver;
  end

  def getBooks()
    return @books;
  end

  def addBook()
    @books = @books + 1;
  end

  def getClasses()
    return @classes;
  end

  def doubleClasses() # updates the number of classes.
    @classes = @classes * 2;
  end

  def getDino()
    return @dinoToy;
  end

  def addDino()
    @dinoToy = @dinoToy + 1;
  end

  def monroeville(oldLocation, newLocation)
    # fourth avenue
    if (newLocation == "Outside City" && oldLocation == "Cathedral")
      puts "Driver #{@currentDriver} has gone to Monroeville!";
      puts "Driver #{@currentDriver} has #{@books} books.";
      puts "Driver #{@currentDriver} has #{@dinoToy} dinosaur toys.";
      puts "Driver #{@currentDriver} has attended #{@classes} classes.";
      return true;
    else
      return false;
    end
  end

  def downtown(oldLocation, newLocation)
    # fifth avenue
    if (newLocation == "Outside City" && oldLocation == "Hillman")
      puts "Driver #{@currentDriver} has gone to Downtown!";
      puts "Driver #{@currentDriver} has #{@books} books.";
      puts "Driver #{@currentDriver} has #{@dinoToy} dinosaur toys.";
      puts "Driver #{@currentDriver} has attended #{@classes} classes.";
      return true;
    else
      return false;
    end
  end
end
