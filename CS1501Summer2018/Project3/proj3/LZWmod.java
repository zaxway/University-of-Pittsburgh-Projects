public class LZWmod {
  // private variable declarations
  private static String compressionMode;
  private static final int R = 256;        // number of input chars
  private static int L = 512;       // number of codewords = 2^W
  private static int W = 9;         // codeword width, 9 bit (initial)
  private static final int MAXWORDS = 65536; // 2^16 codewords
  private static final int MAXWIDTH = 16; // Max Codeword width, 16 bits (final)
  private static double ratio1 = 0; // old ratio
  private static double ratio2 = 0; // new ratio
  private static int uncompressedData = 0; // numerator of ratio
  private static int compressedData = 0; // denominator of ratio
  private static boolean monitorRatio = true;

  public static void main(String [] args) {
    if (args[0].equals("-")) {
      compressionMode = args[1];
      compress();
    }
    else if (args[0].equals("+")) expand();
    else throw new IllegalArgumentException("Illegal command line argument");
  }

  public static void compress() {

      // saves the mode

      if (compressionMode.equals("n")) {
        BinaryStdOut.write('n', 8);
      }
      else if (compressionMode.equals("r")) {
        BinaryStdOut.write('r', 8);
      }
      else if (compressionMode.equals("m")) {
        BinaryStdOut.write('m', 8);
      }
      String input = BinaryStdIn.readString();

      // very important code for reseting.
      TST<Integer> st = new TST<Integer>();
      for (int i = 0; i < R; i++)
          st.put("" + (char) i, i);
      int code = R+1;  // R is codeword for EOF



      while (input.length() > 0) {
          L = (int) (Math.pow(2,W)); // update # of codewords

          String s = st.longestPrefixOf(input);  // Find max prefix match s.
          uncompressedData = s.length() * 8; // set numerator

          BinaryStdOut.write(st.get(s), W);      // Print s's encoding.
          compressedData += W; // set denominator

          ratio1 = (uncompressedData/compressedData); // set old ratio

          int t = s.length();
          if (t < input.length() && code < L) {   // Add s to symbol table.
            st.put(input.substring(0, t + 1), code++);
          }

          //System.out.println("debug");

          if ((code == L)  && (W < 16)) {
            // st.put(input.substring(0, t + 1), code++);
            //System.out.println("debug");
            W++;
            L = (int) (Math.pow(2,W));
            st.put(input.substring(0, t + 1), code++);
          }


          // input = input.substring(t);            // Scan past s in input.
          // RESET
          if (compressionMode == "r" && code == MAXWORDS) {
            // reset Mode
            st = new TST<Integer>();
            for (int d = 0; d < R; d++) {
              st.put("" + (char) d, d);
            }
            // ratio1 = 0;
            // ratio2 = 0;
            W = 9;
            L = 512;
            code = R + 1;
          }
          // Monitor Mode
          else if (compressionMode == "m" && code == MAXWORDS) {
            if (monitorRatio) { // first case must be true to set new ratio (ratio2)
              ratio2 = ratio1;
              monitorRatio = false;
            }
            if ((ratio2 / ratio1) > 1.1) { // if (new ratio/old ratio > 1.1) {reset}
              // reset Mode
              st = new TST<Integer>();
              for (int e = 0; e < R; e++) {
                st.put("" + (char) e, e);
              }
              // ratio1 = 0;
              // ratio2 = 0;
              W = 9;
              L = 512;
              code = R + 1;
              // also reset ratios
              ratio1 = 0;
              ratio2 = 0;
              monitorRatio = true;
            }
          }
          input = input.substring(t);            // Scan past s in input.
      }
      BinaryStdOut.write(R, W);
      BinaryStdOut.close();
  }


  public static void expand() {
      // first we need to retrieve the compression Mode
      // compressionMode = BinaryStdIn.readString();
      // Since our compression Mode is a string, we need to make a new char

      char c;
      c = BinaryStdIn.readChar(8);
      // sets compression mode based on what we read
      // compressionMode = c;
      if (c =='r') {
        compressionMode = "r";
      }
      else if (c == 'n') {
        compressionMode = "n"; // to be frank, we could have just ignored this
      }
      else if (c == 'm') {
        compressionMode = "m";
      }


      // String[] st = new String[L];
      String[] st = new String[MAXWORDS];
      int i; // next available codeword value

      // initialize symbol table with all 1-character strings
      for (i = 0; i < R; i++)
          st[i] = "" + (char) i;
      st[i++] = "";                        // (unused) lookahead for EOF

      int codeword = BinaryStdIn.readInt(W);
      if (codeword == R) return;           // expanded message is empty string
      String val = st[codeword];

      while (true) {
          BinaryStdOut.write(val);
          uncompressedData = val.length() * 8; // sets numerator

          codeword = BinaryStdIn.readInt(W);
          compressedData += W; // sets denominator

          ratio1 = (uncompressedData/compressedData); // set old ratio

          if (codeword == R) break;
          String s = st[codeword];
          if (i == codeword) s = val + val.charAt(0);   // special case hack
          if (i < L-1) st[i++] = val + s.charAt(0); // ****

          if (i == L-1 && W < 16) { // *****
            st[i++] = val + s.charAt(0);
            W++;
            L = (int) (Math.pow(2,W));
          }

          val = s;

          // RESET MODE
          if (compressionMode == "r" && i == MAXWORDS - 1) { //****
            st = new String[MAXWORDS];
            for (i = 0; i < R; i++) {
              st[i] = "" + (char) i;
            }
            W = 9;
            L = 512;
          }

          // MONITOR MODE
          else if (compressionMode == "m" && i == MAXWORDS - 1) { // ******
            if (monitorRatio) { // first case must be true to set new ratio (ratio2)
              ratio2 = ratio1;
              monitorRatio = false;
            }
            if ((ratio2 / ratio1) > 1.1) { // if (new ratio/old ratio > 1.1) {reset}
              // reset Mode
              st = new String[MAXWORDS];
              for (i = 0; i < R; i++) {
                st[i] = "" + (char) i;
              }
              W = 9;
              L = 512;
              //code = R + 1;
              // also reset ratios
              ratio1 = 0;
              ratio2 = 0;
              monitorRatio = true;
          }
      }
      //BinaryStdOut.close();
  }
  BinaryStdOut.close();

}
}
