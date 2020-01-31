import java.util.*;
import java.io.*;

public class crosswordSolver {

  public static ArrayList<String> dictionaryWords;
  public static DictInterface dict; // used for determining DLB or MyDictionary
  public static int n; // number of rows and columns
  public static char[][] arr; // board, holds entire crossword
  public static int secondCounterForAtoZ = 0;

  public static void main(String [] args) throws FileNotFoundException {
    if (args.length != 2) {
      System.out.println("Enter in a file name and (DLB or DICT)");
      System.exit(1);
    }
    String dictType = args[1];

    // This will read all of
    Scanner fileScan = new Scanner(new FileInputStream("dict8.txt"));
    String st;
		StringBuilder sb;
    if (dictType.equals("DLB")) {
      dict = new DLB();
    }
    else {
      dict = new MyDictionary();
    }
    while (fileScan.hasNext())
		{
			st = fileScan.nextLine();
      //dictionaryWords.add(st); // adds it to the arraylist
			dict.add(st); // adds it to the DictInterface (MyDict or DLB)
		}

    // This will parse through the cross word file and put the entire cross word inside a
    // 2 dimensional array.

    // I am going to assume everything in the file is properly formatted
    // and that the file is a .txt file by default.
    Scanner console;
    File f = new File(args[0]);
    char[] alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q'
    ,'r','s','t','u','v','w','x','y','z'};

    try {
      console = new Scanner(f);
      n = console.nextInt();
      console.nextLine();
      arr = new char[n][n];
      System.out.println(n);
      String [] line = new String[n];
      for (int i = 0; i < n; i++) {
        line[i] = console.nextLine(); // gets line to parse
        for (int j = 0; j < n; j++) {
          arr[i][j] = line[i].charAt(j); // parses character of each line
          System.out.print(arr[i][j]);
        }
        System.out.println();
      }
      System.out.println();
    }
    catch(Exception e) {
      System.out.println("No file found.");
      System.exit(1);
    }
    sb = new StringBuilder();

    solve(0, 0, 0, alphabet, arr, sb);
  }

  public static char[] grabRow(char[][] board, int row) {
    char[] rowArr = new char[n];
    for(int i = 0; i < n; i++) {
      rowArr[i] = board[row][i];
    }
    return rowArr;
  }

  public static char[] grabCol(char[][] board, int col) {
    char[] colArr = new char[n];
    for(int i = 0; i < n; i++) {
      colArr[i] = board[i][col];
    }
    return colArr;
  }

  // copied most of this method from
  //https://stackoverflow.com/questions/18581531/in-java-how-can-i-determine-if-a-char-array-contains-a-particular-character
  // used to find out if the certain characater is a letter in the alphabet.
  public static boolean contains(char c, char[] array) {
    char c1 = Character.toLowerCase(c);
    for (char x : array) {
        if (x == c1) {
            return true;
        }
    }
    return false;
  }
  // starts at location 0.
  public static void solve(int location, int counterForN, int counterForAtoZ,
  char[] alphabet, char[][] board, StringBuilder sb) {
    //System.out.println(location);
    if (location == n*n) {
      // solved
      System.out.println("Solved");
      System.exit(0);
    }
    int row = location / n; // gets the row number
    int col = location % n; // gets the column number
    char[] getRow = grabRow(board, row);
    char[] getCol = grabCol(board, col);
    if (counterForAtoZ == 26) {
      // reset alphabet and the counter
      alphabet = new char[] {'a','b','c','d','e','f','g','h','i','j','k','l','m',
      'n','o','p','q', 'r','s','t','u','v','w','x','y','z'};
      counterForAtoZ = 0;
    }
    char letterToTry = alphabet[counterForAtoZ];
    if (!contains(getRow[counterForN], alphabet)) {
      sb.append(letterToTry);
    }
    int wordOrNot = dict.searchPrefix(sb);
    //System.out.println(sb);

    if (getRow[counterForN] == '+') {
      if (wordOrNot == 0) {
        // not a prefix/word
        // delete the last character of the stringbuilder
        if (sb.length() > 0) {
          sb.setLength(sb.length() - 1);
        }
        // check if all letters have been checked
        if (counterForAtoZ == 25) {
          // then backtrack one location
          sb.setLength(sb.length() - 1);
          solve(location - 1, counterForN - 1, 0, alphabet, board, sb);
        }
        // otherwise at the currentlocation try a new letter
        solve(location, counterForN, counterForAtoZ + 1, alphabet, board, sb);
      }
      else if (wordOrNot == 1) {
        // prefix but not a word
        //System.out.println("CounterForN = " + counterForN);
        if (counterForN == n-1) {
          sb.setLength(sb.length() - 2);
          // backtrack back 1 time to the location for which we started from
          // but this time increase the alphabet counter by 1 so that it starts at b/c/d...
          if (secondCounterForAtoZ == 25) {
            secondCounterForAtoZ = 0;
          }
          secondCounterForAtoZ++;
          solve(location - 1, counterForN - 1, secondCounterForAtoZ, alphabet, board, sb);
        }
        // otherwise go forward one square, increase counterForN, reset alphabet counter to 0
        solve(location + 1, counterForN + 1, 0, alphabet, board, sb);
      }
      else if (wordOrNot == 2) {
        // its a word and that's the end, no prefix
        // check if the length of our stringbuilder is not equal to the number of sqaures we need to cover.
        if (sb.length() != n) {
          // if so, then this word is not the word we want so
          // delete the last character of the stringBuilder
          if (sb.length() > 0) {
            sb.setLength(sb.length() - 1);
          }
          solve(location, counterForN, counterForAtoZ + 1, alphabet, board, sb);
        }
        else {
          // then this is the word we want so
          // set the word
          System.out.println(sb);
          sb.setLength(0);

        }
      }
      else if (wordOrNot == 3) {
        // word and prefix
        // if our stringBuilder is equal to the length of the number
        // of sqaures that we need to cover
        if (sb.length() == n) {
          // then we set the word in those squares.
          //System.out.println("This is the word!");
          System.out.println(sb);
          sb.setLength(0);
          getRow = new char[getRow.length];
          getCol = new char[getCol.length];
          solve(location + 1, 0, 0, alphabet, board, sb);
          //System.exit(0);
        }
        else {
          // if our stringBuilder is not equal to the length of the number of squares yet
          // then we go forward one square, increase the counter for N, and reset the
          // alphabet counter
          solve(location + 1, counterForN + 1, 0, alphabet, board, sb);
        }
      }
    }


    else if (getRow[counterForN] == '-') {
      // skip this block
    }



    else if (contains(getRow[counterForN], alphabet)) {
        // append the letter to the sb
        sb.append(getRow[counterForN]);
        // figure out if our new stringbuilder is a prefix or a word or neither
        // if a prefix and EOW(end of word), then backtrack to previous location
        // and look at a new letter
        wordOrNot = dict.searchPrefix(sb);
        //System.out.println("At contains part = " + sb);
        if (wordOrNot == 0) {
          // not a prefix/word
          // delete the last character of the stringbuilder
          if (sb.length() > 0 && counterForN > 1) {
            sb.setLength(sb.length() - 2);
          }
          // check if all letters have been checked
          if (counterForAtoZ == 25) {
            // then backtrack one more location
            sb.setLength(sb.length() - 1);
            solve(location - 1, counterForN - 1, 0, alphabet, board, sb);
          }
          // otherwise at the currentlocation - 1 try a new letter
          solve(location - 1, counterForN - 1, counterForAtoZ + 1, alphabet, board, sb);
        }
        else if (wordOrNot == 1) {
          // prefix but not a word
          //System.out.println("CounterForN = " + counterForN);
          if (counterForN == n-1) {
            sb.setLength(sb.length() - 2);
            // backtrack back 1 time to the location for which we started from
            // but this time increase the alphabet counter by 1 so that it starts at b/c/d...
            if (secondCounterForAtoZ == 25) {
              secondCounterForAtoZ = 0;
            }
            secondCounterForAtoZ++;
            solve(location - 1, counterForN - 1, secondCounterForAtoZ, alphabet, board, sb);
          }
          // otherwise go forward one square, increase counterForN, reset alphabet counter to 0
          solve(location + 1, counterForN + 1, 0, alphabet, board, sb);
        }
        else if (wordOrNot == 2) {
          // its a word and that's the end, no prefix
          // check if the length of our stringbuilder is not equal to the number of sqaures we need to cover.
          if (sb.length() != n) {
            // if so, then this word is not the word we want so
            // delete the last character of the stringBuilder before the set letter
            if (sb.length() > 0) {
              sb.setLength(sb.length() - 2);
            }
            solve(location - 1, counterForN - 1, counterForAtoZ + 1, alphabet, board, sb);
          }
          else {
            // then this is the word we want so
            // set the word
            System.out.println(sb);
            sb.setLength(0);
            solve(location + 1, 0, 0, alphabet, board, sb);

          }
        }
        else if (wordOrNot == 3) {
          // word and prefix
          // if our stringBuilder is equal to the length of the number
          // of sqaures that we need to cover
          if (sb.length() == n) {
            // then we set the word in those squares.
            //System.out.println("This is the word!");
            System.out.println(sb);
            sb.setLength(0);
            getRow = new char[getRow.length];
            getCol = new char[getCol.length];
            solve(location + 1, 0, 0, alphabet, board, sb);
            //System.exit(0);
          }
          else {
            // if our stringBuilder is not equal to the length of the number of squares yet
            // then we go forward one square, increase the counter for N, and reset the
            // alphabet counter
            solve(location + 1, counterForN + 1, 0, alphabet, board, sb);
          }
        }

    }

  }
}
