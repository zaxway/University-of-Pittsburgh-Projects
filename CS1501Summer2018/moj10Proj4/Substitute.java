import java.util.*;
import java.io.*;

public class Substitute implements SymCipher {
  private byte [] key;
  private byte [] permKey;

  public Substitute() {
    key = new byte[256];
    permKey = new byte[256];
    int index = 0;
    int z = 0;
    ArrayList<Byte> permuteKey = new ArrayList<Byte>(256);
    // add byte #s 0 to 255 into arraylist
    for(int i = 0; i < key.length; i++) {
      permuteKey.add((byte) i);
    }

    // Then randomize these
    Collections.shuffle(permuteKey);

    // Then start mapping and load permKey[]
    for (int j = 0; j < key.length; j++) {
      key[j] = (byte) permuteKey.get(j); // put the byte arraylist into the key, so we can access it throughout this class.
      z = key[j];
      if (z < 0) {
        permKey[key[j] & 255] = (byte) j;
      }
      else {
        permKey[key[j]] = (byte) j;
      }

    }
  }

  public Substitute(byte[] tmp) {
    // set byte arrays
    this.key = tmp; // already given the byte array
    permKey = new byte[256];
    int x = 0;
    for (int j = 0; j < permKey.length; j++) {
      // need to handle negative values as well.
      x = key[j];
      if (x < 0) {
        permKey[key[j] & 255] = (byte) j;
      }
      else {
        permKey[key[j]] = (byte) j;
      }
    }
  }

  // key for encoding
  public byte [] encode(String S) {
    // convert the string parameter to an array of bytes.
    // iterate through array
    // substitute appropriate bytes from the key.
    // check for negative values.

    byte [] message = S.getBytes();
    byte [] encodeString = new byte[message.length];
    int y = 0;
    for (int i = 0; i < message.length; i++) {
      // to check for negative values we can simply MASK the message.
      // This will change all the bits on the high end from 1s to 0s.
      // and keep the low end to what we need.
      y = message[i];
      if (y < 0) {
        encodeString[i] = key[message[i] & 255];
      }
      else {
        encodeString[i] = key[message[i]];
      }
    }
    return encodeString;
  }

  public byte [] getKey() {
    return key;
  }

  // permKey for decoding
  public String decode(byte [] bytes) {
    //System.out.println("We are on sub..");
    byte[] decodeMessage = new byte[bytes.length];
    int y = 0;
    for (int i = 0; i < bytes.length; i++) {
      y = bytes[i];
      if (y < 0) { // if x is negative, the MASK it with 255
        decodeMessage[i] = (byte) permKey[bytes[i] & 255];
      }
      else {
        decodeMessage[i] = (byte) permKey[bytes[i]];
      }
    }
    return new String(decodeMessage);
  }
}
