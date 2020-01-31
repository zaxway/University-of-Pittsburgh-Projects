require 'simplecov'
SimpleCov.start
require 'minitest/autorun'
require_relative "Driver"
require_relative "City"

class DriverTest< Minitest::Test

  #UNIT TESTS
  # gets_currrent_driver() Method
  # FUN-FUN-DRIVERS Requirement, Test checks drivers' names and makes sure that every driver is given a
  # different digit or number
  def test_IfCurrentDriverDigitMatchesProperly()
    one = Driver.new(1)
    two = Driver.new(2)
    three = Driver.new(3)
    four = Driver.new(4)
    five = Driver.new(5)

    assert_equal 1, one.gets_currrent_driver
    assert_equal 2, two.gets_currrent_driver
    assert_equal 3, three.gets_currrent_driver
    assert_equal 4, four.gets_currrent_driver
    assert_equal 5, five.gets_currrent_driver
  end

  # UNIT TESTS
  # geadd_books_classes_toys
  # FUN-CITY-LOCS Requirement,
  # This test checks that when a random number is entered, one of the four locations is properly picked
  # and is included in our collection of locations.
  def test_CheckIfAllFourLocationsAreDefined
    driver = Driver.new(1)
    assert_includes ['Hillman', 'Museum', 'Hospital', 'Cathedral'], driver.gets_location
  end

  # UNIT TESTS
  # setFirstLocation() Method
  #FUN-START-LOC
  # This test returns true when the initial location is successfully set. If the test returns false,
  # then this test has failed and the initial location has not been set.
  def test_DriverStartsInAnyLocation
    driver = Driver.new(1)
    assert_equal true, driver.sets_first_location
  end

  # UNIT TESTS
  # setsDiffLocation() Method
  # This test checks that a different location is added successfully into our location variable
  # given the location for which we want to set it to.
  def test_setDiffLocation
    driver = Driver.new(1)
    assert_equal 'Hospital', driver.sets_diff_location('Hospital')
  end

  # This test checks that when the user enters a parameter that is not a defined location, that location
  # will not pass successfully, and our location variable will not be updated.
  # EDGE CASE
  def test_setDiffLocationForWrongInput
    driver = Driver.new(1)
    assert_nil driver.sets_diff_location('Barbie Shop')
  end

  # UNIT TESTS
  # addBooksClassesToys() Method
  # Checks if One book is added when the location is hillman
  def test_ifHillmanIsLocAddOneBook
    driver = Driver.new(1)
    def driver.location; driver.location = 'Hillman'; end
    driver.sets_location('Hillman')
    driver.sets_books(0)
    driver.add_books_classes_toys
    assert_equal 1, driver.gets_books
  end

  #Checks if one dinosaur toy is added when location is museum
  def test_ifMuseumIsLocAddOneDinosaurToy
    driver = Driver.new(1)
    def driver.location; driver.location = 'Museum'; end
    driver.sets_location('Museum')
    driver.sets_dinotoys(0)
    driver.add_books_classes_toys
    assert_equal 1, driver.gets_dino
  end

  # Checks if number of classes is multiplied by 2 when location is cathedral
  def test_ifCathedralIsLocMultiplyClassesByTwo
    driver = Driver.new(1)
    def driver.location; driver.location = 'Cathedral'; end
    driver.sets_location('Cathedral')
    driver.sets_classes(4)
    driver.add_books_classes_toys
    assert_equal 8, driver.gets_classes
  end

  # Checks that when an invalid location is passed, the number of classes is not doubled
  # and only nil is returned.
  # EDGE CASE
  def test_ifLocationDoesNotExistWhenWeTryToAddClassesBooksDinos
    driver = Driver.new(1)
    driver.sets_location('Hooters')
    driver.sets_classes(4)
    assert_nil driver.add_books_classes_toys
  end

  # UNIT TESTS
  # checkIfGone() Method, Essential to the movingDriver() Method
  # checks if driver has gone to monroeville after all conditions have been met.
  def test_movingDriverGoesToMonroeVille
    driver = Driver.new(1)
    assert_equal false, driver.check_if_gone('Cathedral', 'Outside City')
  end

  # checks if driver has gone to downtown after all conditions have been met.
  def test_movingDriverGoesToDowntown
    driver = Driver.new(1)
    assert_equal false, driver.check_if_gone('Hillman', 'Outside City')
  end

  # UNIT TESTS
  # This test checks the overall function for moving_driver().
  # In this function we return true if the driver has not yet reached his location.
  # This test checks a certain case in which the driver will not have reached
  # his location and makes sure that its output is true.
  def test_movingDriverOverall
    driver = Driver.new(1)
    city = City.new()
    location_arr = city.gets_new_location("Hillman", "Foo St.")
    driver.sets_diff_location("Hospital")
    assert_equal true, driver.check_if_gone("Hillman", "Hospital")
    assert_equal true, driver.moving_driver
  end

  # UNIT TESTS
  # This tests tests the method printing_text(location_arr).
  # In this test, for a given array inclduing current_location, new_location,
  # and direction, we test that the ouput is printed out correctly.
  def test_printingText
    driver = Driver.new(1)
    location_arr = ["Hillman", "Cathedral", "Foo St."]
    assert_output (/Driver 1 heading from Hillman to Cathedral via Foo St./) { driver.printing_text(location_arr) }
  end
end
