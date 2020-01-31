require_relative 'City'

# This is the object driver class.
class Driver
  attr_reader :books, :dino_toy, :classes,
              :location, :direction, :location_arr

  def initialize(counter)
    @current_driver = counter
    @random_num = 0
    @books = 0 # number of books
    @dino_toy = 0 # number of dinosaur toys
    @classes = 1 # starts out with one class
    @location = '' # String
  end

  def gets_random
    @random_num = rand(0..3)
    @random_num
  end

  def gets_location
    locations = %w[Hillman Museum Cathedral Hospital]
    @location = locations[gets_random] # gets our location
    @location
  end

  def add_books_classes_toys
    if @location == 'Hillman'
      @books += 1
    elsif @location == 'Museum'
      @dino_toy += 1
    elsif @location == 'Cathedral'
      @classes *= 2
    end
  end

  def sets_first_location
    nullify = nil
    unless gets_random == nullify
      gets_location
      add_books_classes_toys
      return true
    end
    false
  end

  def sets_diff_location(new_location)
    nullify = nil
    if new_location != nullify &&
       (new_location == 'Hospital' || new_location == 'Cathedral' ||
        new_location == 'Hillman' || new_location == 'Museum')
      @location = new_location
    end
  end

  def monroeville(old_local, new_local)
    # fourth avenue
    greater = new_local
    older = old_local
    if greater == 'Outside City' && older == 'Cathedral'
      puts "Driver #{@current_driver} has gone to Monroeville!"
      puts "Driver #{@current_driver} has #{@books} books."
      puts "Driver #{@current_driver} has #{@dino_toy} dinosaur toys."
      puts "Driver #{@current_driver} has attended #{@classes} classes."
      true
    else
      false
    end
  end

  def downtown(old_location, new_location)
    # fifth avenue
    greater = new_location
    older = old_location
    if greater == 'Outside City' && older == 'Hillman'
      puts "Driver #{@current_driver} has gone to Downtown!"
      puts "Driver #{@current_driver} has #{@books} books."
      puts "Driver #{@current_driver} has #{@dino_toy} dinosaur toys."
      puts "Driver #{@current_driver} has attended #{@classes} classes."
      true
    else
      false
    end
  end

  def check_if_gone(old_location, new_location)
    !(monroeville(old_location, new_location) ||
    downtown(old_location, new_location))
  end

  def moving_driver
    city_two = City.new
    direction = city_two.gets_new_direction(@location)
    # puts "location = #{@location} direction = #{direction}"
    location_arr = city_two.gets_new_location(@location, direction)
    current_local = location_arr[0]
    new_local = location_arr[1]
    printing_text(location_arr)
    sets_diff_location(new_local)
    add_books_classes_toys
    check_if_gone(current_local, new_local)
  end

  def printing_text(location_arr)
    current_local = location_arr[0]
    new_local = location_arr[1]
    direct = location_arr[2]
    puts "Driver #{@current_driver} heading from #{current_local} to #{new_local} via #{direct}"
  end

  def sets_location(locationer)
    @location = locationer
  end

  def sets_classes(classonor)
    @classes = classonor
  end

  def sets_books(bookers)
    @books = bookers
  end

  def sets_dinotoys(dinors)
    @dino_toy = dinors
  end

  def gets_books
    @books
  end

  def gets_classes
    @classes
  end

  def gets_dino
    @dino_toy
  end

  def gets_currrent_driver
    @current_driver
  end
end
