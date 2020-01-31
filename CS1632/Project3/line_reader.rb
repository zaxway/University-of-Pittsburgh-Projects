class LineReader
  # Returns an array whose first element is the lines and whose second
  # element is a string representing an error if there was one and otherwise is
  # nil.
  def get_lines argv
    if argv.size != 1
      [nil, "Error: invalid number of program arguments"]
    elsif !File.exist? argv[0]
      [nil, "Error: blockchain file not found."]
    else
      file = File.open argv[0]
      lines = file.readlines.map {|line| line.chomp} # Remove trailing newlines.
      file.close
      [lines, nil]
    end
  end
end
