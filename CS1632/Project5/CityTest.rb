require 'simplecov'
SimpleCov.start
require 'minitest/autorun'
require_relative 'Driver'
require_relative 'City'
# This is the class to test our city object.
class CityTest< Minitest::Test

  # UNIT TESTS
  # for method gets_new_direction()
  # Checks if they include all possible directions per location.
  # Checks for location of cathedral
  def test_gets_new_directionForCathedralLocation
    city = City.new()
    assert_includes ['Fourth Avenue', 'Bar St.'], city.gets_new_direction('Cathedral')
  end

  # This tests the get_new_direction(current_location) method.
  # It assures that we get one of the following directions on random when
  # when we provide a location parameter.
  # Checks for location of hillman
  def test_gets_new_directionForHillmanLocation
    city = City.new()
    assert_includes ['Fifth Avenue', 'Foo St.'], city.gets_new_direction('Hillman')
  end

  # This test tests the gets_new_direction(current_location) method.
  # It assures that we get one of the following directions on random when
  # when we provide a location parameter.
  def test_gets_new_directionForMuseumLocation
    city = City.new()
    assert_includes ['Fifth Avenue', 'Bar St.'], city.gets_new_direction('Museum')
  end

  # Checks for location of hospital
  def test_gets_new_directionForHospitalLocation
    city = City.new()
    assert_includes ['Fourth Avenue', 'Foo St.'], city.gets_new_direction('Hospital')
  end

  # EDGE CASE
  # This test checks that if we enter an invalid location for the parameter, we should get nil.
  def test_gets_new_directionForInvalidLocation
    city = City.new()
    assert_nil city.gets_new_direction('Primantis')
  end

  # UNIT TESTS
  # for method getNewLocation()
  # Checks for one simple test that if the currentLocation is hospital and our direction is on Fourth Avenue,
  # then it will return the specified array.
  def test_gets_new_location
    city = City.new()
    assert_equal ['Hospital', 'Cathedral', 'Fourth Avenue'], city.gets_new_location('Hospital', 'Fourth Avenue')
  end

  # UNIT TEST
  # For method get_direction, tests if certain locations are entered,
  # the correct output for each location is returned into the
  # new location variable.
  def test_gets_just_direction
    city = Going.new()
    assert_equal 'Cathedral', city.gets_direction('Fourth Avenue', 'Hospital')
    assert_equal 'Outside City', city.gets_direction('Fourth Avenue', 'Cathedral')
    assert_equal 'Hillman', city.gets_direction('Fifth Avenue', 'Museum')
    assert_equal 'Outside City', city.gets_direction('Fifth Avenue', 'Hillman')
    assert_equal 'Hospital', city.gets_direction('Foo St.', 'Hillman')
    assert_equal 'Hillman', city.gets_direction('Foo St.', 'Hospital')
    assert_equal 'Museum', city.gets_direction('Bar St.', 'Cathedral')
    assert_equal 'Cathedral', city.gets_direction('Bar St.', 'Museum')
  end

end
