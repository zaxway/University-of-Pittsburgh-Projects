require 'minitest/autorun'
require_relative "Driver"
require_relative "City"

class DriverTest< Minitest::Test

  #UNIT TESTS
  # getCurrrentDriver() Method
  # FUN-FUN-DRIVERS Requirement, Test checks drivers' names and makes sure that every driver is given a
  # different digit or number
  def test_IfCurrentDriverDigitMatchesProperly()
    one = Driver::new(1);
    two = Driver::new(2);
    three = Driver::new(3);
    four = Driver::new(4);
    five = Driver::new(5);

    assert_equal 1, one.getCurrrentDriver;
    assert_equal 2, two.getCurrrentDriver;
    assert_equal 3, three.getCurrrentDriver;
    assert_equal 4, four.getCurrrentDriver;
    assert_equal 5, five.getCurrrentDriver;
  end

  # UNIT TESTS
  # getLocation() Method
  # FUN-CITY-LOCS Requirement,
  # This test checks that when a random number is entered, one of the four locations is properly picked
  # and is included in our collection of locations.
  def test_CheckIfAllFourLocationsAreDefined
    driver = Driver::new(1);
    assert_includes ["Hillman", "Museum", "Hospital", "Cathedral"], driver.getLocation;
  end

  # UNIT TESTS
  # setFirstLocation() Method
  #FUN-START-LOC
  # This test returns true when the initial location is successfully set. If the test returns false,
  # then this test has failed and the initial location has not been set.
  def test_DriverStartsInAnyLocation
    driver = Driver::new(1);
    assert_equal true, driver.setFirstLocation;
  end

  # UNIT TESTS
  # setDiffLocation() Method
  # This test checks that a different location is added successfully into our location variable
  # given the location for which we want to set it to.
  def test_setDiffLocation
    driver = Driver::new(1);
    assert_equal "Hospital", driver.setDiffLocation("Hospital")
  end

  # This test checks that when the user enters a parameter that is not a defined location, that location
  # will not pass successfully, and our location variable will not be updated.
  # EDGE CASE
  def test_setDiffLocationForWrongInput
    driver = Driver::new(1);
    assert_nil driver.setDiffLocation("Barbie Shop");
  end

  # UNIT TESTS
  # addBooksClassesToys() Method
  # Checks if One book is added when the location is hillman
  def test_ifHillmanIsLocAddOneBook
    driver = Driver::new(1);
    def driver.location; driver.location = "Hillman"; end
    driver.location = "Hillman";
    driver.books = 0;
    driver.addBooksClassesToys;
    assert_equal 1, driver.getBooks;
  end

  #Checks if one dinosaur toy is added when location is museum
  def test_ifMuseumIsLocAddOneDinosaurToy
    driver = Driver::new(1);
    def driver.location; driver.location = "Museum"; end
    driver.location = "Museum";
    driver.dinoToy = 0;
    driver.addBooksClassesToys;
    assert_equal 1, driver.getDino;
  end

  # Checks if number of classes is multiplied by 2 when location is cathedral
  def test_ifCathedralIsLocMultiplyClassesByTwo
    driver = Driver::new(1);
    def driver.location; driver.location = "Cathedral"; end
    driver.location = "Cathedral";
    driver.classes = 4;
    driver.addBooksClassesToys;
    assert_equal 8, driver.getClasses;
  end

  # Checks that when an invalid location is passed, the number of classes is not doubled
  # and only nil is returned.
  # EDGE CASE
  def test_ifLocationDoesNotExistWhenWeTryToAddClassesBooksDinos
    driver = Driver::new(1);
    driver.location = "Hooters";
    driver.classes = 4;
    assert_nil driver.addBooksClassesToys;
  end

  # UNIT TESTS
  # checkIfGone() Method, Essential to the movingDriver() Method
  # checks if driver has gone to monroeville after all conditions have been met.
  def test_movingDriverGoesToMonroeVille
    driver = Driver::new(1);
    assert_equal false, driver.checkIfGone("Cathedral", "Outside City");
  end

  # checks if driver has gone to downtown after all conditions have been met.
  def test_movingDriverGoesToDowntown
    driver = Driver::new(1);
    assert_equal false, driver.checkIfGone("Hillman", "Outside City");
  end

end
