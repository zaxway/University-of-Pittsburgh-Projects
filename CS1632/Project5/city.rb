require_relative 'Going'
# Mohit Jain
# CS 1632
# This is the city class.
class City
  attr_reader :direction, :new_location_arr, :current_location
  def initialize
    @locations = %w[Hillman Museum Cathedral Hospital]
    # display locations for interesections and streets they are on.
    @hillman = ['Fifth Avenue', 'Foo St.']
    @hospital = ['Fourth Avenue', 'Foo St.']
    @cathedral = ['Fourth Avenue', 'Bar St.']
    @museum = ['Fifth Avenue', 'Bar St.']
  end

  def gets_new_location(current_location, direction)
    going = Going.new
    nulled = [nil, nil, nil]
    nulled_function(current_location, direction, nulled)
    new_location = going.gets_direction(direction, current_location)
    new_location_arr = [current_location, new_location, direction]
    new_location_arr
  end

  def nulled_function(current_local, direct, nulled)
    nullify = nil
    current_location = current_local
    direction = direct
    if current_location == nullify
      nulled
    elsif direction == nullify
      randoms = rand(0..3)
      @locations[randoms]
    end
  end

  def gets_new_direction(current_local)
    # nullify = nil
    current_location = current_local
    # return nil if current_location == nullify
    new_direction = rand(0..1)
    if current_location == 'Cathedral'
      return @cathedral[new_direction]
    elsif current_location == 'Hillman'
      return @hillman[new_direction]
    elsif current_location == 'Museum'
      return @museum[new_direction]
    elsif current_location == 'Hospital'
      return @hospital[new_direction]
    else
      return nil
    end
  end
end
