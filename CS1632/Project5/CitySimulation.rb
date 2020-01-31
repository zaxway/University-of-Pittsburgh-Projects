require_relative 'Driver'

# This is the main class that we run.
class CitySimulation
  # lets get the arguments first and input them into an array args_arr
  args_arr = ARGV
  # r = Random.new
  drivers = [Driver.new(1), Driver.new(2), Driver.new(3),
              Driver.new(4), Driver.new(5)]

  if args_arr.length > 1 || args_arr.length < 1
    puts 'Too many or too less arguments were passed in.
    Pass in only one argument.'
    exit
  elsif !(args_arr[0].is_a? Integer)
    args_arr[0] = 0
  end

  for current_drive in 0..4
    # set the initial location, then move it one step at a time.
    # do this is a while till we return false.
    drivers[current_drive].sets_first_location
    while (drivers[current_drive].moving_driver)
    end
    puts ''
  end
end
