/* Mohit Jain
CS 0445 Project 1 Part 1
*/

public class FrequencyBag<T>
{
	// TO DO: Instance Variables
	private int numberOfEntries;
	private int numberOfTimes;
	private Node firstNode;
	private Node lastNode;

	/**
	 * Constructor
	 * Constructs an empty frequency bag.
	 */
	public FrequencyBag()
	{
		// TO DO
		firstNode = null;
		lastNode = null;
		numberOfEntries = 0;
	}

	/**
	 * Adds new entry into this frequency bag.
	 * @param aData the data to be added into this frequency bag.
	 */
	public void add(T aData) {
		Node newNode;

		if (numberOfEntries == 0) {
			newNode = new Node(null, aData);
			firstNode = newNode;
			lastNode = firstNode;
			numberOfEntries++;
		}
		else if (numberOfEntries > 0) {
			newNode = new Node(null, aData);
			lastNode.next = newNode;
			lastNode = newNode;
			numberOfEntries++;
		}
	}

	/**
	 * Gets the number of occurrences of aData in this frequency bag.
	 * @param aData the data to be checked for its number of occurrences.
	 * @return the number of occurrences of aData in this frequency bag.
	 */
	public int getFrequencyOf(T aData)
	{
		// TO DO
		Node currentNode = new Node(aData);
		currentNode = firstNode;
		int counter = 0;
		for(int i = 1; i <= numberOfEntries; i++) {
			//what data is in this node right now.
			if (currentNode.data == null) {
				System.out.println("The bag is empty!");
				return 0;
			}
			else if (currentNode.data.equals(aData)) {
				counter++;
			}
			currentNode = currentNode.next;
		}
		return counter;
	}

	/**
	 * Gets the maximum number of occurrences in this frequency bag.
	 * @return the maximum number of occurrences of an entry in this
	 * frequency bag.
	 */
	public int getMaxFrequency()
	{
		// TO DO
		Node currentNode;
		currentNode = firstNode;
		int currentfreq = 0;
		int maxfreqency = currentfreq;
		for (int d = 1; d <= numberOfEntries; d++) {
			currentfreq = getFrequencyOf(currentNode.data);
			if (currentfreq > maxfreqency) {
				maxfreqency = currentfreq;
			}
			currentNode = currentNode.next;
		}
		return maxfreqency;
	}

	/**
	 * Gets the probability of aData
	 * @param aData the specific data to get its probability.
	 * @return the probability of aData
	 */
	public double getProbabilityOf(T aData)
	{
		// TO DO
		Node currentNode = firstNode;
		double freq = 0;
		double probs = 0;
		for(int i = 1; i <= numberOfEntries; i++) {
			freq = getFrequencyOf(aData);
			probs = freq/numberOfEntries;
			currentNode = currentNode.next;
		}
		return probs;
	}

	/**
	 * Empty this bag.
	 */
	public void clear()
	{
		// TO DO
		numberOfEntries = 0;
		firstNode = null;
		lastNode = null;
	}

	/**
	 * Gets the number of entries in this bag.
	 * @return the number of entries in this bag.
	 */
	public int size()
	{
		// TO DO
		return numberOfEntries;
	}

	private class Node {
		public Node next;
		public T data;

		public Node(T aData) {
			data = aData;
			next = null;
		}

		public Node(Node nextNode, T aData) {
			next = nextNode;
			data = aData;
		}
	}
}
