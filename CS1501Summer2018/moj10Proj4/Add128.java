import java.util.*;
import java.io.*;

public class Add128 implements SymCipher {
  private byte [] add128; // this is the key

  public Add128() {
    Random rand = new Random();
    add128 = new byte[128];
    rand.nextBytes(add128); // popluate the array with random bytes
  }

  public Add128(byte [] arr) {
    this.add128 = arr;
  }

  public byte [] encode(String S) {
    int iKey = 0;
    int iMess = 0;
    int total = 0;
    int currentKeyIndex = 0;
    byte [] message = S.getBytes(); // this is the message
    byte [] b = new byte[message.length];
    int lenMessage = message.length;
    for (int i = 0; i < message.length; i++) {
      iKey = add128[i%128];
      iMess = message[i];
      total = iKey + iMess; // adds two ints together
      b[i] = (byte) total; // gets the byte array, adds it current
    }

    return b;
  }

  public byte [] getKey() {
    return add128;
  }

  public String decode(byte [] bytes) {
    //System.out.println("We are on add..");
    int iKey = 0;
    int iMess = 0;
    int total = 0;
    int currentKeyIndex = 0;
    byte [] message = bytes; // this is the message
    byte [] b = new byte[message.length];
    int lenMessage = message.length;
    System.out.println(message.length);
    for (int i = 0; i < message.length; i++) {
      iKey = add128[i%128];
      iMess = message[i];
      total = iMess - iKey; // subtract key from message
      b[i] = (byte) total; // gets the byte array, adds it current
    }

    return new String(b);
  }
}
