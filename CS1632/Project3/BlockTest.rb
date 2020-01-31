require 'minitest/autorun'
require_relative "block"
require_relative "transaction.rb"
require_relative "timestamp.rb"

class BlockTest< Minitest::Test

  def test_parseLine
    b, error = Block::new.parse_line("2|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
    assert_equal b.block_num, 2
    assert_equal b.previous_block_hash, "8c56";
    assert_equal b.hash, "71c9";
    # timestamp and transcations are tested in seperate methods
  end


  def test_parseTransactions
    b = Block::new;
    tmp = b.parse_transactions("Cyrus>Tang(3)")[0];
    assert_equal "Cyrus", tmp.sender;
    assert_equal "Tang", tmp.receiver;
    assert_equal 3, tmp.amount;
  end

  def test_parseTimestamp
    b = Block::new;
    tmp = b.parse_timestamp("1518893687.348124000");
    assert_equal 1518893687, tmp.seconds_since_epoch;
    assert_equal 348124000, tmp.num_nanoseconds;
  end

  def test_blockNumError
    b = Block::new; # previous block
    b,err = b.parse_line("2|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
    a = Block::new; # currebt block
    a,e = a.parse_line("4|71c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|1518893687.355456000|6e18");
    tmp = b.error_msg("4|71c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|1518893687.355456000|6e18", "current block's block number", 3, 4);
    #assert_equal b.block_num, 2; # used to test if true
    #assert_equal a.block_num, 4; # used to test if true

    assert_equal tmp, b.block_num_error(a, b, "4|71c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|1518893687.355456000|6e18");
  end

  def test_prevBlockHashError
    b = Block::new; # previous block
    b,err = b.parse_line("2|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
    a = Block::new; #current block
    a,e = a.parse_line("3|61c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|1518893687.355456000|6e18");
    tmp = b.error_msg("3|61c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|1518893687.355456000|6e18", "current block's recording of the previous block's hash", "71c9", "61c9");

    assert_equal tmp, b.previous_block_hash_error(a, b, "3|61c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|1518893687.355456000|6e18");
  end

  def test_noRewardError
    b = Block::new; # previous block
    b,err = b.parse_line("2|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
    a = Block::new; # current block
    a,e = a.parse_line("3|71c9|Cyrus>Mary(1):BOOM>Xerxes(100)|1518893687.355456000|6e18");
    tmp = b.error_msg("3|71c9|Cyrus>Mary(1):BOOM>Xerxes(100)|1518893687.355456000|6e18", "sender of the last transaction in the block", "SYSTEM", "BOOM");
    assert_equal tmp, b.no_reward_error(a, b, "3|71c9|Cyrus>Mary(1):BOOM>Xerxes(100)|1518893687.355456000|6e18");
  end

  def test_tooManyTransactions
   b = Block::new; # previous block
   b,err = b.parse_line("5|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
   a = Block::new; # current block
   a,e = a.parse_line("0|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
   tmp = b.error_msg("0|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9", "number of transactions on the zeroith line", 1, 3);
   assert_equal tmp, b.too_many_transactions_error(a, b, "0|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
 end

 def test_timestampError
   b = Block::new; # previous block
   b,err = b.parse_line("2|8c56|Gaozu>Pakal(16):Cyrus>Tang(3):SYSTEM>Peter(100)|1518893687.348124000|71c9");
   a = Block::new; # current block
   a,e = a.parse_line("3|71c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|5.5|6e18");
   tmp = b.error_msg("3|71c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|5.5|6e18", "time recorded in the current block",
             "greater than the time recorded in the previous block",
             "less than the time recorded in the previous block");
   assert_equal tmp, b.timestamp_error(a, b, "3|71c9|Cyrus>Mary(1):SYSTEM>Xerxes(100)|5.5|6e18");
 end

 def test_stringifyTransactions
   b = Block::new;
   tmp = b.parse_transactions("Cyrus>Tang(3)");
   strng = "Cyrus>Tang(3)"
   assert_equal strng, b.stringify_transactions(tmp);
 end

 def test_stringifyTimestamp
   b = Block::new;
   tmp = b.parse_timestamp("1518893687.348124000");
   strng = "1518893687.348124000";
   assert_equal strng, b.stringify_timestamp(tmp);
 end

 def test_errorMsg
   b = Block::new;
   strng = "An error occurred when verifying the blockchain on the line:\n  blah\n"\
   "The boom was expected to be 3 "\
   "but was instead 4."
   assert_equal strng, b.error_msg("blah", "boom", 3, 4);
 end

 def test_blockError
   # all the errors are already checked in other unit tests, so for this, we will just assert that no block error exists.
   # If a block error exists even though we gave in parameters that should pass, then the test has failed, and there
   # is something wrong with the code.
   c = Block::new;
   b = Block::new;
   b,err = b.parse_line("1|1c12|SYSTEM>George(100)|1518892051.740967000|abb2");
   a = Block::new;
   a,e = a.parse_line("2|abb2|George>Amina(16):Henry>James(4):Henry>Cyrus(17):Henry>Kublai(4):George>Rana(1):SYSTEM>Wu(100)|1518892051.753197000|c72d");
   assert_nil c.block_error(a,b,"2|abb2|George>Amina(16):Henry>James(4):Henry>Cyrus(17):Henry>Kublai(4):George>Rana(1):SYSTEM>Wu(100)|1518892051.753197000|c72d");
 end


end
