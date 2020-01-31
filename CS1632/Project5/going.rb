# Seperate class for
class Going
  def initialize
    @useless = 0
  end

  def check_fourth(older)
    @useless = 1
    odd = older
    if odd == 'Hospital'
      'Cathedral'
    else # older == 'Cathedral'
      'Outside City'
    end
  end

  def check_fifth(old)
    @useless = 2
    odds = old
    if odds == 'Museum'
      'Hillman'
    else # older == 'Hillman'
      'Outside City'
    end
  end

  def check_foo(aged)
    @useless = 3
    dying = aged
    if dying == 'Hillman'
      'Hospital'
    else # older == 'Hospital'
      'Hillman'
    end
  end

  def check_bar(ages)
    @useless = 4
    death = ages
    if death == 'Cathedral'
      'Museum'
    else # older == 'Museum'
      'Cathedral'
    end
  end

  def gets_direction(directing, current_locals)
    @useless = 5
    older = current_locals
    hello = directing
    new_location =
      case hello
      when 'Fourth Avenue'
        check_fourth(older)
      when 'Fifth Avenue'
        check_fifth(older)
      when 'Foo St.'
        check_foo(older)
      when 'Bar St.'
        check_bar(older)
      else
        older
      end
    new_location
  end
end
