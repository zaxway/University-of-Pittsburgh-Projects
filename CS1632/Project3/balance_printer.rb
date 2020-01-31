class BalancePrinter
  def print balances
    puts "Addresses and their associated number of billcoins:"
    balances.each do |account, balance|
      if balance != 0
        puts "#{account}: #{balance}"
      end
    end
  end
end
