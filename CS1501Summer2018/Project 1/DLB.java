// Mohit Jain
// CS 1501
// 6/7/18
/* README
  DLB includes a node class with two functions: add, searchPrefix
  add will add a word according to the dictionary.txt file.
  searchPrefix will search for a given word based on a StringBuilder
  and will then return 0,1,2,3 based on if it is a prefix, word, or neither */

public class DLB implements DictInterface {
  private Node rootNode;

  public DLB() {
    rootNode = new Node(null, null, '/');
  }

  public boolean add(String s) {
    // used to insert a word into our dlb trie
    // need to create something to signify the end of the word
    s += '^';
    // the first node is the rootNode
    Node currentNode = rootNode;
    for(int a = 0; a < s.length(); a++) {
      // we need to get the characters one by one
      char c = s.charAt(a);
      if(currentNode.downNode == null) {
        currentNode.downNode = new Node(null, null, c); // add the character to a new node
        // set the currentNode to the child node
        currentNode = currentNode.downNode;
      }
      else {
        Node nextNode = currentNode.downNode;
        while(nextNode.rightNode != null) {
          if(nextNode.value == c) {
            break;
          }
          nextNode = nextNode.rightNode;
        }

        if(nextNode.value == c) {
          currentNode = nextNode;
        }
        else {
          nextNode.rightNode = new Node(null, null, c);
          currentNode = nextNode.rightNode;
        }
      }
    }
    return true;
  }

  public int searchPrefix(StringBuilder s)
  {
    int status = 0;
    boolean prefix, word, discoveredLetter;
    Node currentNode = rootNode;
    prefix = false;
    word = false;

    // Iterate through the dlb, until the end or until the
    // key is passed up (since it is sorted).
    for (int i = 0; i < s.length(); i++)
    {
      discoveredLetter = false;

      // Iterate through the key and the current String in the
      // DLB character by character.
      while(currentNode != null) {
        if (currentNode.value == s.charAt(i)) {
          discoveredLetter = true;
          if (currentNode.downNode != null) {
            currentNode = currentNode.downNode;
            break;
          }
          else {
            // nothing was found, so..
            return 0;
          }
        }

        else {
          if(currentNode.rightNode != null) {
            currentNode = currentNode.rightNode;
          }
          else {
            // nothing was found, so..
            return 0;
          }
        }
      }

      if (discoveredLetter) {
        if (i == (s.length() - 1)) {
          while(currentNode != null) {
            if (currentNode.value != '^') {
              prefix = true; // end of word character does not exist
            }
            else {
              word = true; // end of word character exists
            }
            currentNode = currentNode.rightNode;
          }
        }
      }
    }
    if (prefix && word) return 3;
    else if (word) return 2;
    else if (prefix) return 1;
    else return 0;
  }

  public int searchPrefix(StringBuilder s, int start, int end) {
    return 0;
  }

// Node class
  private class Node {
    public Node rightNode; // sibling Node
    public Node downNode; // child Node
    public char value;

    public Node() {

    }

    public Node(Node rightNode, Node downNode, char value) {
      this.rightNode = rightNode;
      this.downNode = downNode;
      this.value = value;
    }
  }
}
