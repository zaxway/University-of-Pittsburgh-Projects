class Token
  def initialize(input)
    @current_input = input.gsub(/\s+/m, ' ').strip.split(' ')
  end

  def parse_input
    # check if the first operand is a let or print
    if (@current_input[1] == 'LET')
      # do something LET a <num/var> <num/var> <operand>
      value_to_set = @current_input[2]
      # call some let.rb class
    elsif (@current_input[1] == 'PRINT')
      # do something
      value_to_print = @current_input[2];
      # call soem print.rb class
    elsif (@current_input[1] == 'QUIT')
      exit
    else # if its none i.e. 4 3 +
      # call some basic.rb class
      if @current_input[2] == ''
      # basic.rb will allow you to check each value until you hit an operand
      # if you hit an operand, then we will break out of the loop, store each
  end

  def check_case(input)
    
end

# I heard there was a lot of security questions. Oh cool, that does not seem too bad honestly. yeah it does, hold up my laptop is
# at 1 % so rip. idk what will happen when I leave this room, but I hope you can still work on this every now and then
# not sure how to split it, but theres a lot of work, so we can just work on it whenever we get time. aight thanks for the info man
# Have a beautiful day. yeah take your time, i'll be studying for the exam for the rest of the day. lets meet tomorrow if necessary.
# yeah thats true I love this haahha. its genius. aight laptop dead cya

# It honestly isn't. The difficult part is remembering what attacks what. If that makes sense. Yikes haha. Okay sounds good.
# Thanks you too man. I have class from 6-8:30 so we will see haha. Sure we just figure out if we really need too now that we have this.

# what's up bro
# hey what' up
#
# there is not much code here yet, but yeah, hope its pretty readable. I plan to create
# multiple classes for each let,print,and quit. I'm going to start out by describing my plan in the comments
# and you can change it however you like after that as long as it works.
#
# Sounds good to me.

# how was the exam?
# I was wondering if you would ask haha. It honestly is not too bad. Know how to write two rantly tests and a bunch of terminology
# Yea it is. You have to know about the CIA InfoTriad and what attacks affect them. And the two anti patterns.
