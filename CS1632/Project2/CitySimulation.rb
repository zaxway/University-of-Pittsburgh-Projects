require_relative "Driver"

class CitySimulation
  #lets get the arguments first and input them into an array argsArr
  argsArr = ARGV;
  r = Random.new;
  drivers = [Driver.new(1), Driver.new(2), Driver.new(3), Driver.new(4), Driver.new(5)];

  if (argsArr.length > 1 || argsArr.length < 1)
    puts "Too many or too less arguments were passed in. Pass in only one argument."
    exit
  elsif (!(argsArr[0].is_a? Integer))
    argsArr[0] = 0;
  end

  for i in 0..4
    # set the initial location, then move it one step at a time. do this is a while till we return false.
    drivers[i].setFirstLocation();
    while(drivers[i].movingDriver());
    end
    puts "";
  end
end
