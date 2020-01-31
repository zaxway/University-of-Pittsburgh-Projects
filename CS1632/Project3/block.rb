require_relative "transaction.rb"
require_relative "timestamp.rb"

class Block
  attr_accessor :block_num, :previous_block_hash, :transactions, :timestamp, :hash

  def parse_line line
    regex = "^\\d+\\|"\
            "\\h+\\|"\
            "([A-Za-z]{,6}>[A-Za-z]{,6}\\(\\d+\\):)*[A-Za-z]{,6}>[A-Za-z]{,6}\\(\\d*\\)\\|"\
            "\\d+\\.\\d+\\|"\
            "\\h*$"
    if line.match regex
      elements = line.split("|")
      block = Block::new
      block.block_num = elements[0].to_i
      block.previous_block_hash = elements[1]
      block.transactions = parse_transactions elements[2]
      block.timestamp = parse_timestamp elements[3]
      block.hash =  elements[4]
      return [block, nil]
    else
      # Return the block as nil and give an error message.
      [nil, (error_msg line, "syntax", "valid", "invalid")]
    end
  end

  def parse_transactions str
    transaction_strs = str.split ":"
    transactions = []
    transaction_strs.each do |s|
      sender, rest = s.split(">")
      receiver, rest2 = rest.split "\("
      amount = rest2[0...rest2.size - 1].to_i # Remove the parenthesis at the end.
      transactions.push (Transaction.new sender, receiver, amount)
    end
    return transactions
  end

  def parse_timestamp str
    seconds_since_epoch_str, num_nanoseconds_str = str.split "."
    return TimeStamp.new seconds_since_epoch_str.to_i, num_nanoseconds_str.to_i
  end

  def update_balances balances, current_block, previous_block, line
    error = block_error current_block, previous_block, line
    if error
      return error
    else
      current_block.transactions.each do |t|
        if t.sender != "SYSTEM"
          balances[t.sender] -= t.amount
        end
        balances[t.receiver] += t.amount
      end
      current_block.transactions.each do |t|
        if balances[t.sender] < 0
          return error_msg line, "#{t.sender}'s balance", "nonnegative", balances[t.sender]
        end
      end
    end
    nil
  end

  def block_error current_block, previous_block, line
    checker_functions = [:block_num_error,
                         :previous_block_hash_error,
                         :no_reward_error,
                         :too_many_transactions_error,
                         :timestamp_error,
                         :current_block_hash_error]

    # Call each function in the array "checker_functions" to check for errors.
    checker_functions.each do |checker_function|
      error = send checker_function, current_block, previous_block, line
      if error
        return error
      end
    end
    nil
  end


  def block_num_error current_block, previous_block, line
    if !previous_block && current_block.block_num != 0
      return error_msg line, "current block's block number", 0, current_block.block_num
    elsif previous_block && current_block.block_num != previous_block.block_num + 1
      return error_msg line, "current block's block number", previous_block.block_num + 1,
                       current_block.block_num
    end
  end

  def previous_block_hash_error current_block, previous_block, line
    if current_block.block_num == 0 && current_block.previous_block_hash != "0"
      return error_msg line, "current block's recording of the previous block's hash",
                "0", current_block.previous_block_hash
    elsif current_block.block_num > 0 && previous_block.hash != current_block.previous_block_hash
      return error_msg line, "current block's recording of the previous block's hash",
                       previous_block.hash, current_block.previous_block_hash
    end
  end

  def no_reward_error current_block, previous_block, line
    # my_array[-1] is shorthand for my_array[my_array.size - 1]
    sender = current_block.transactions[-1].sender
    if sender != "SYSTEM"
      return error_msg line, "sender of the last transaction in the block", "SYSTEM", sender
    end
  end

  def too_many_transactions_error current_block, previous_block, line
    size = current_block.transactions.size
    if current_block.block_num == 0 && size != 1
      return error_msg line, "number of transactions on the zeroith line", 1, size
    end
  end

  def timestamp_error current_block, previous_block, line
    return unless previous_block
    ct = current_block.timestamp
    pt = previous_block.timestamp
    if (ct.seconds_since_epoch == pt.seconds_since_epoch &&
       ct.num_nanoseconds <= pt.num_nanoseconds) ||
       (ct.seconds_since_epoch < pt.seconds_since_epoch)
      return error_msg line, "time recorded in the current block",
                "greater than the time recorded in the previous block",
                "less than the time recorded in the previous block"
    end
  end

  def current_block_hash_error current_block, previous_block, line
    if (make_hash current_block) != current_block.hash
      return error_msg line, "current block's hash", (make_hash current_block), current_block.hash
    end
  end

  def make_hash block
    str = "#{block.block_num}|#{block.previous_block_hash}|"\
          "#{stringify_transactions block.transactions}|"\
          "#{stringify_timestamp block.timestamp}"
    values = str.unpack("U*")
    hash = 0
    values.each do |x|
      hash += (x ** 2000) * ((x + 2) ** 21) - ((x + 5) ** 3)
    end
    hash %= 65536
    hash.to_s(16) # Convert to base 16.
  end

  def stringify_transactions transactions
    str = ""
    transactions.each do |t|
      str += "#{t.sender}>#{t.receiver}(#{t.amount}):"
    end
    return str.chomp ":" # Remove the trailing ":".
  end

  def stringify_timestamp timestamp
    "#{timestamp.seconds_since_epoch}.#{timestamp.num_nanoseconds}"
  end

  def error_msg line, trait, expected_value, actual_value
    "An error occurred when verifying the blockchain on the line:\n  #{line.to_s}\n"\
    "The #{trait.to_s} was expected to be #{expected_value.to_s} "\
    "but was instead #{actual_value.to_s}."
  end
end
