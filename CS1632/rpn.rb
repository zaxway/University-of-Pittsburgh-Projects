require_relative 'token.rb'

class Rpn
  prompt = '> '
  loop do
    print prompt
    input = gets.chomp
    tokens = Token.new(input)
    tokens.parse_input
  end
end
