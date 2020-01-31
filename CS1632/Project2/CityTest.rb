require 'minitest/autorun'
require_relative "Driver"
require_relative "City"

class CityTest< Minitest::Test
  # UNIT TESTS
  # for method getNewDirection()
  # Checks if they include all possible directions per location.
  # Checks for location of cathedral
  def test_getNewDirectionForCathedralLocation
    city = City::new();
    assert_includes ["Fourth Avenue", "Bar St."], city.getNewDirection("Cathedral")
  end
  # Checks for location of hillman
  def test_getNewDirectionForHillmanLocation
    city = City::new();
    assert_includes ["Fifth Avenue", "Foo St."], city.getNewDirection("Hillman")
  end
  # Checks for location of museum
  def test_getNewDirectionForMuseumLocation
    city = City::new();
    assert_includes ["Fifth Avenue", "Bar St."], city.getNewDirection("Museum")
  end
  # Chcks for location of hospital
  def test_getNewDirectionForHospitalLocation
    city = City::new();
    assert_includes ["Fourth Avenue", "Foo St."], city.getNewDirection("Hospital")
  end

  # EDGE CASE
  # This test checks that if we enter an invalid location for the parameter, we should get nil.
  def test_getNewDirectionForInvalidLocation
    city = City::new();
    assert_nil city.getNewDirection("Primantis")
  end

  # UNIT TESTS
  # for method getNewLocation()
  # Checks for one simple test that if the currentLocation is hospital and our direction is on Fourth Avenue,
  # then it will return the specified array.
  def test_getNewLocation
    city = City::new();
    assert_equal ["Hospital", "Cathedral", "Fourth Avenue"], city.getNewLocation("Hospital", "Fourth Avenue")
  end

end
