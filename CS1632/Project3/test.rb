# NOTE: this code doesn't work now that the methods in the rest of the project aren't static.
require_relative "block.rb"

def test_parser_gibberish
  if (Block.parse_line "lasdj|sadfj|fleasjdf")[0] == nil
    puts "Passed: gibberish test"
  else
    puts "FAILED: gibberish test"
  end
end

def test_bad_hash
  previous_block = (Block.parse_line "0|0|SYSTEM>Gaozu(100)|1518893687.329767000|fd18")[0]
  line = "1|fd18|Gaozu>Cyrus(15):Yaa>Edward(1):SYSTEM>Pakal(100)|187.3000|8c56"
  current_block = (Block.parse_line line)[0]
  if Block.block_error current_block, previous_block, line
    puts "Passed: bad hash test"
  else
    puts "FAILED: bad hash test"
  end
end

test_parser_gibberish
test_bad_hash
