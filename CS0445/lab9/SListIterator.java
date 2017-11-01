import java.util.NoSuchElementException;


public class SListIterator<T>
{
	private Node firstNode;
	private int numberOfEntries;

	public SListIterator()
	{
		firstNode = null;
		numberOfEntries = 0;
	}

	public void addToFirst(T aData)
	{
		firstNode = new Node(aData, firstNode);
		numberOfEntries++;
	}

	public T getEntry(int givenPosition)
	{
		T result = null;

		if((givenPosition >= 1) && (givenPosition <= numberOfEntries))
		{
			result = (getNodeAt(givenPosition)).data;
		}

		return result;
	}

	private Node getNodeAt(int givenPosition)
	{
		Node currentNode = firstNode;

		for(int counter = 1; counter < givenPosition; counter++)
		{
			currentNode = currentNode.next;
		}

		return currentNode;
	}

	public Iterator<T> getIterator()
	{
		// TO DO
		return new IteratorForSList();

	}

	private class IteratorForSList implements Iterator<T>
	{
		// TO DO: instance variable for IteratorForSList
		Node nextNode;

		private IteratorForSList()
		{
			// TO DO: constructor
			nextNode = firstNode;
		}

		public boolean hasNext()
		{
			// TO DO
			return nextNode != null;
		}

		public T next()
		{
			// TO DO
			if(hasNext())
			{
				Node returnNode = nextNode;
				nextNode = nextNode.next;
				return returnNode.data;
			}
			else
			{
				throw new NoSuchElementException("Illegal call to next();" + "iterator is after end of list.");
			}

		}

		public T remove()
		{
			throw new UnsupportedOperationException("remove() is not supported by this iterator");
		}
	}

	private class Node
	{
		private T data;
		private Node next;

		private Node(T aData, Node nextNode)
		{
			data = aData;
			next = nextNode;
		}
	}
}
