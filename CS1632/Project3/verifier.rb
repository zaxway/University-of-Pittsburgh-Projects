#require "flamegraph"
require_relative "block.rb"
require_relative "line_reader.rb"
require_relative "balance_printer.rb"

#Flamegraph.generate('deliverable3.html') do

lines, file_error = LineReader.new.get_lines ARGV
  if file_error
    abort file_error # Print the error and abort.
  end

  balances = Hash.new(0) # Make 0 be the default (starting) balance for everyone.
  previous_block = nil
  current_block = nil
  lines.each do |line|
    current_block, parse_error = Block.new.parse_line line
    if parse_error
      abort parse_error
    end

    block_error = Block.new.update_balances balances, current_block, previous_block, line
    if block_error
      abort block_error
    end

    previous_block = current_block
  end
BalancePrinter.new.print balances
#end
