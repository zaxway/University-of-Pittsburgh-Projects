class City
  attr_accessor :direction, :newLocationArr, :currentLocation
  def initialize
    @locations = ["Hillman", "Museum", "Cathedral", "Hospital"];
    # display locations for interesections and streets they are on.
    @hillman = ["Fifth Avenue", "Foo St."];
    @hospital = ["Fourth Avenue", "Foo St."];
    @cathedral = ["Fourth Avenue", "Bar St."];
    @museum = ["Fifth Avenue", "Bar St."];

  end


  def getNewLocation(currentLocation, direction)
    newLocation = "";
    nulled = [nil,nil,nil];
    nulled2 = [currentLocation, currentLocation, nil];
    if (currentLocation == nil)
      return nulled;
    elsif (direction == nil)
      r = 0 + Random.rand(3);
      return @locations[r]; # might need to check if 4 is inclusive or exclusive, check for 0 too
    end
    puts "!!!"
    case direction
    when "Fourth Avenue"
      if (currentLocation == "Hospital")
        newLocation = "Cathedral";
      elsif (currentLocation == "Cathedral")
        newLocation = "Outside City";
      end
      #break;
    when "Fifth Avenue"
      if (currentLocation == "Museum")
        newLocation = "Hillman";
      elsif(currentLocation == "Hillman")
        newLocation = "Outside City";
      end
      #break if true;
    when "Foo St."
      if (currentLocation == "Hospital")
        newLocation = "Hillman";
      elsif(currentLocation == "Hillman")
        newLocation = "Hospital";
      end
      #break if true;
    when "Bar St."
      if (currentLocation == "Cathedral")
        newLocation = "Museum";
      elsif(currentLocation == "Museum")
        newLocation = "Cathedral";
      end
      #break if true;
    else
      newLocation = currentLocation;
      #break if true;
    end

    newLocationArr = [currentLocation, newLocation, direction];
    puts "newLocationArr = #{newLocationArr}"
    return newLocationArr;
  end

  def getNewDirection(currentLocation)
    if (currentLocation == nil)
      return nil;
    end


    newDirection = 0 + Random.rand(2);
    if (currentLocation == "Cathedral")
      return @cathedral[newDirection];
    elsif(currentLocation == "Hillman")
      return @hillman[newDirection];
    elsif(currentLocation == "Museum")
      return @museum[newDirection];
    elsif(currentLocation == "Hospital")
      return @hospital[newDirection];
    else
      return nil;
    end
  end
end
