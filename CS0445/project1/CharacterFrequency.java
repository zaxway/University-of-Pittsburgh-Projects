/* Mohit Jain
Project 1 Part 2 CS 0445
*/
import java.util.Scanner;
import java.io.*;
import java.util.*;


public class CharacterFrequency {
  public static void main (String [] args) throws IOException {
    Scanner console = new Scanner(new File("letter1.txt")); //encoding file within Scanner.
    HashMap<Character, Integer> lettermap = new HashMap<Character, Integer>(); // create new HashMap
    System.out.println();
    System.out.println("Character Frequency Calculator");
    System.out.println("==============================");
    // Reads the file.
    while (console.hasNextLine()) {
      // Changes all characters in the file to lower case and puts it inside the array.
      char [] letters = console.nextLine().toLowerCase().toCharArray();
      for (Character a : letters) {
        if (!Character.isLetter(a)) {
          continue;
        }
        // checks if the mapping contains a mapping for the Character key 'a'.
        // If it does store the key (a) and the value for the key.
        if (lettermap.containsKey(a)) {
          lettermap.put(a, lettermap.get(a) + 1); // + 1 to update the mapping.
        }
        else {
          lettermap.put(a,1); // update the mapping.
        }
      }
    }

    // Prints out letters in order from a to z as well as the number value of frequency
    // next to the letter.
    for (HashMap.Entry<Character, Integer> printout : lettermap.entrySet()) { //entrySet() returns set view of mappings.
      System.out.println(printout.getKey() + ": " + printout.getValue());
    }
  }
}
