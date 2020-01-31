import java.lang.*;
import java.util.*;

public class PHPArray<V> implements Iterable<V> {

  private int lengthOfArray; // size of hash table
  private int currNumElements; // current number of elements within the table
  private Node<V>[] hashTable;
  private Node<V> first;
  private Node<V> last;
  private Node<V> currentNode;
  private int numKeyValuePairs; // number of key value pairs


  public PHPArray(int size) {
    this.lengthOfArray = size;
    currNumElements = 0;
    hashTable = (Node<V>[]) new Node<?>[lengthOfArray];
    first = null;
    last = null;
    currentNode = null;
  }

  private void resize(int newLength) {
    Node<V>[] tmp = (Node<V>[]) new Node<?>[newLength];
    for (int i = 0; i < lengthOfArray; i++) {
      if (hashTable[i] != null) {
        tmp[hash(hashTable[i].data.key, newLength)] = hashTable[i];
      }
    }
    // set hashTable to the new length
    hashTable = tmp;
    lengthOfArray = newLength;
  }

  private void checkInitialValues(String key, V value) {
    if (value == null) {
      // delete key created
      unset(key);
    }
    if(currNumElements >= (lengthOfArray/2)) {
      // check if the number of current elements has covered
      // half the number of elements in the hashTable
      resize(2*lengthOfArray);
    }
  }

  private void checkFirstAndLastNodes(int i) {
    if (first == null) {
      first = hashTable[i];
      currentNode = first;
    }
    if (last == null) {
      last = hashTable[i];
    }
  }

  public void put(String key, V value) {
    checkInitialValues(key, value);
    // we have now added one element into the table
    currNumElements = currNumElements + 1;
    // set value for key
    int i = hash(key, lengthOfArray);
    while (hashTable[i] != null) {
      if(hashTable[i].data.key.equals(key)) {
        hashTable[i].data.value = value;
        return;
      }
      i++;
    }
    hashTable[i] = new Node<V>(new Pair<V>(key,value));
    checkFirstAndLastNodes(i);
    hashTable[i].prevNode = last;
    last.nextNode = hashTable[i];
    last = hashTable[i];
  }

  // handles the case if first argument is an Integer
  // make it a string, and run the put(String,V) function
  public void put(Integer integ, V value) {
    String key = integ.toString();
    if (value == null) {
      unset(key);
    }
    put(key, value);
  }

  public Iterator<V> iterator() {
    return new LinkedListIterator();
  }

  // retrieves the value associated with the key
  public V get(String key) {
    for (int i = hash(key, lengthOfArray); hashTable[i] != null; i = (i + 1) % lengthOfArray) {
      // check if the hashtable contains the key we are looking for
      if (hashTable[i].data.key.equals(key)) {
        return hashTable[i].data.value;
      }
    }
    // if not return null.
    return null;
  }

  public V get(Integer i) {
    String key = i.toString();
    return get(key);
  }

  // debugging methods**
  private void setFirstAndLast(int counter) {
    if (last == hashTable[counter]) {
      last = hashTable[counter].prevNode;
    }
    if (first == hashTable[counter]) {
      first = hashTable[counter].nextNode;
    }
  }

  private void setHashTableNodes(int i) {
    hashTable[i].prevNode.nextNode = hashTable[i].nextNode;
    hashTable[i].nextNode.prevNode = hashTable[i].prevNode;
    hashTable[i] = null;
  }
  // debugging methods end

  // simple helper method
  private int setCounter(int i) {
    return (i + 1) % lengthOfArray;
  }
  // deletes the selected key if it exists within the hashtable
  public void unset(String key) {
    if (!(get(key) != null)) {
      return;
    }
    else {
      int i = hash(key, lengthOfArray);
      while(!key.equals(hashTable[i].data.key)) {
        i = setCounter(i);
      }
      // set first node/last node
      setFirstAndLast(i);
      setHashTableNodes(i);
      i = setCounter(i);
      while(hashTable[i] != null) {
        String keyToHashAgain = hashTable[i].data.key;
        V val = hashTable[i].data.value;
        hashTable[i] = null;
        int hashNew = hash(keyToHashAgain, lengthOfArray);
        while(hashTable[hashNew] != null) {
          hashNew++; // gets an index of an empty hash
        }
        hashTable[hashNew] = new Node<V>(new Pair<V>(keyToHashAgain, val));
        i = setCounter(i);
      }
    }
    currNumElements = currNumElements - 1;
  }

  public void unset(Integer i) {
    String key = i.toString();
    unset(key);
  }

  public void showTable() {
    System.out.println("Raw Hash Table Contents: ");
    System.out.println();
    for (int i = 0; i < lengthOfArray; i++) {
      if(hashTable[i] != null) {
        System.out.println("Key = " + hashTable[i].data.key + " Value = " + hashTable[i].data.value);
      }
      else {
        System.out.println("null");
      }
    }
  }

  public Pair<V> each() {
    if (currentNode == null) {
      return null;
    }
    else {
      Pair<V> currentPair = currentNode.data;
      currentNode = currentNode.nextNode;
      return currentPair;
    }
  }

  public void sort() {
    // error checking
    if (first == null || first.nextNode == null) {
      return;
    }

    return;
  }

  public void asort() {
    // error checking
    if (first == null || first.nextNode == null) {
      return;
    }
    return;
  }

  public int length() {
    return currNumElements;
  }

  public void reset() {
    currentNode = first;
  }

  public ArrayList<V> values() {
    Node<V> currNode = first;
    ArrayList<V> listOfValues = new ArrayList<>();
    for (int i = 0; i < lengthOfArray; i++) {
      if (currNode == null) {
        break;
      }
      listOfValues.add(currNode.data.value);
      currNode = currNode.nextNode;
    }
    return listOfValues;
  }

  public ArrayList<String> keys() {
    Node<V> currNode = first;
    ArrayList<String> listOfKeys = new ArrayList<>();
    for (int i = 0; i < lengthOfArray; i++) {
      if (currNode == null) {
        break;
      }
      listOfKeys.add(currNode.data.key);
      currNode = currNode.nextNode;
    }
    return listOfKeys;
  }

  public PHPArray<String> array_flip() {
    // create a new PHPArray object and set it to the length of the
    // current HashTable. We don't want it to go over haha.
    PHPArray<String> flippedArray = new PHPArray<>(lengthOfArray);
    Node<V> currNode = first;
    for (int i = 0; i < lengthOfArray; i++) {
      if (currNode == null) {
        break;
      }
      flippedArray.put((String) currNode.data.value, currNode.data.key);
      currNode = currNode.nextNode;
    }
    return flippedArray;
  }

  // tried to make array_flip support integers but did not work :(

  // public PHPArray<Integer> array_flip() {
  //   // create a new PHPArray object and set it to the length of the
  //   // current HashTable. We don't want it to go over haha.
  //   PHPArray<Integer> flippedArray = new PHPArray<>(lengthOfArray);
  //   Node<V> currNode = first;
  //   for (int i = 0; i < lengthOfArray; i++) {
  //     if (currNode == null) {
  //       break;
  //     }
  //     flippedArray.put((Integer) currNode.data.value, currNode.data.key);
  //     currNode = currNode.nextNode;
  //   }
  //   return flippedArray;
  // }

  private int hash(String key, int length) {
    return ((key.hashCode() & 0x7fffffff) % length);
  }

  public static class Pair<V> {
    public String key;
    public V value;

    public Pair(String k, V val) {
      key = k;
      value = val;
    }

  }

  // holds pair information and linked list
  private static class Node<V> implements Comparable<Node<V>> {
    private Pair<V> data;
    private Node<V> nextNode;
    private Node<V> prevNode;

    private Node(Pair<V> datas) {
      data = datas;
    }

    public int compareTo(Node<V> someNode) {
      V thisData = this.data.value;
      V val = someNode.data.value;
      int compare = 0;
      return compare = ((Comparable)thisData).compareTo(val);
    }
  }


  private class LinkedListIterator implements Iterator<V> {
    private Node<V> currNode;

    public LinkedListIterator() {
      currNode = first;
    }

    public boolean hasNext() {
      if (currNode != null) {
        return true;
      }
      else {
        return false;
      }
    }

    public V next() {
      V val = currNode.data.value;
      currNode = currNode.nextNode;
      return val;
    }
  }

  // Extra Credit Functions
  public Integer array_sum() {
    // first get the values of the array
    ArrayList<V> sumOfVals = values();
    // set a total counter
    Integer total = 0;
    int i = 0;
    Integer nextValue = 0;
    while (i < sumOfVals.size()) {
      nextValue = (Integer) sumOfVals.get(i);
      total += nextValue;
      i = i + 1;
    }
    return total;

  }

}
