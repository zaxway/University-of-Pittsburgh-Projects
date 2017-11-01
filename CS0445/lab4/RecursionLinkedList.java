
public class RecursionLinkedList
{
	private Node firstNode;
	private int numberOfEntries;

	public RecursionLinkedList()
	{
		firstNode = null;
		numberOfEntries = 0;
	}

	public void add(int aData)
	{
		if(numberOfEntries == 0)
		{
			firstNode = new Node(aData);
		}
		else
		{
			firstNode = new Node(aData, firstNode);
		}

		numberOfEntries++;
	}

	/**
	 * boolean contains(int aData)
	 *
	 * See whether this RecursionLinkedList contains aData
	 * @param aData  a data to be located
	 * @return true if this RecursionLinkedList contains aData,
	 *         or false otherwise.
	 */
	public boolean contains(int aData, Node currentNode) {
		if (currentNode == null) {
			return false;
		}
		else if (currentNode.data == aData) {
			return true;
		}
		else {
			return contains(aData, currentNode.next);
		}
	}

	public boolean contains(int aData)
	{
		// TO DO
		Node currentNode = firstNode;
		boolean a = contains(aData, firstNode);
		return a;
	}

	/**
	 * int getFrequencyOf(int aData)
	 *
	 * Counts the number of times a given data appears in this
	 * RecursionLinkedList.
	 *
	 * @param aData  the data to be counted
	 * @return the number of times aData appears in this RecursionLinkedList
	 */
	public int getFrequencyOf(int aData, Node currentNode) {
		int counter = 0;
		if (currentNode == null) {
			return 0;
		}
		else if (currentNode.data == aData) {
			counter = 1 + getFrequencyOf(aData, currentNode.next);
			// getFrequencyOf(aData, currentNode.next);
		}
		else {
			counter = getFrequencyOf(aData, currentNode.next);
		}
		return counter;
	}
	public int getFrequencyOf(int aData)
	{
		// TO DO
		Node currentNode = firstNode;
		int a = getFrequencyOf(aData, firstNode);
		return a;
	}

	/**
	 * String toString()
	 *
	 * Return a string representation of this RecursionLinkedList. For example,
	 * if this RecursionLinkedList contains 1, 2, 3, 5, 2 and 3 from the first
	 * index to the last index, the returned string should be
	 * "[1,2,3,5,2,3]"
	 * @return the string representation of this RecursionLinkedList.
	 */
	public String toString(Node currentNode, String string) {
		if (currentNode == null) {
			return string + "]";
		}
		else {
			if (string.equals("[")) {
				return toString(currentNode.next, string + currentNode.data);
			} else {
				return toString(currentNode.next, string + "," + currentNode.data);
			}
			// string = string + ""," + toString(currentNode.next, string);
		}
	}

	public String toString()
	{
		// TO DO
		// Node currentNode = firstNode;
		String a = toString(firstNode, "[");
		return a;
	}

	/**
	 * int getIndexOf(int aData)
	 *
	 * Return the index of the first aData where the first index of
	 * the first item in this RecursionLinkedList is 0.
	 *
	 * @param aData  the data to be located
	 * @return the index of the first aData.
	 */
	public int getIndexOf(int aData, Node currentNode) {
		int index = 0;
		if (currentNode == null) {
			return -1;
		}
		// else if (currentNode.data != aData) {
		// 	return -1;
		// }
		else if (currentNode.data == aData) {
			// index = getIndexOf(aData, currentNode.next);
			return index;
		}
		// if (currentNode.data != aData) {
		// 	return -1;
		// }
		else {
			int temp = getIndexOf(aData, currentNode.next);
			if (temp == -1) {
				return -1;
			}
			else  {
				return 1 + temp;
			}
		}
	}
	public int getIndexOf(int aData)
	{
		// TO DO
		Node currentNode = firstNode;
		int index = 0;
		if (currentNode.data == aData) {
			return index;
		}
		else {
			index = getIndexOf(aData, currentNode);
			return index;
		}
	}

	private class Node
	{
		private int data;
		private Node next;

		private Node(int aData, Node nextNode)
		{
			data = aData;
			next = nextNode;
		}

		private Node(int aData)
		{
			this(aData, null);
		}
	}
}
