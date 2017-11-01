import java.util.ArrayList;
import java.util.Random;


public class BNHTester
{
	public static void main(String[] args)
	{
		int numElements = 15;
		
		Integer[] data = getRandomIntArray(numElements);
		ArrayList<BinaryNode<Integer>> nodes = new ArrayList<BinaryNode<Integer>>();
		
		System.out.print("Data: ");
		printArray(data);
		
		BinaryNodeInterface<Integer> bstRoot = genBST(data, nodes);
		
		System.out.println("Smallest Value: " + getMin(data));
		System.out.println("Left Most Data: " + BNHelper.getLeftMostNode(bstRoot).getData());

		System.out.println("Largest Value: " + getMax(data));
		System.out.println("Right Most Data: " + BNHelper.getRightMostNode(bstRoot).getData());
		
		System.out.print("Print Inorder Left First: ");
		printInorderLeft(bstRoot);
		
		Object[] temp1 = BNHelper.getArrayInorderLeftFirst(bstRoot);
		System.out.print("Print Ascending Order  : ");
		printArray(temp1);
		
		System.out.print("Print Inorder Right First: ");
		printInorderRight(bstRoot);

		Object[] temp2 = BNHelper.getArrayInorderRightFirst(bstRoot);
		System.out.print("Print Descending Order  : ");
		printArray(temp2);
		
		// Mix up the Tree
		
		Random rand = new Random();
		rand.setSeed(System.currentTimeMillis());
		
		for(int i = 0; i < 100; i++)
		{
			int first = rand.nextInt(numElements);
			int second = rand.nextInt(numElements);
			BinaryNodeInterface<Integer> firstNode = nodes.get(first);
			BinaryNodeInterface<Integer> secondNode = nodes.get(second);
			
			int temp = firstNode.getData();
			firstNode.setData(secondNode.getData());
			secondNode.setData(temp);
		}
		
		System.out.print("\nInorder after shuffle: ");
		printInorderLeft(bstRoot);

		System.out.println("Searching for 0 to 9 in this new tree:");
		
		for(int i = 0; i < 10; i++)
		{
			BinaryNodeInterface<Integer> result = BNHelper.getReferenceTo(bstRoot, i);
			if(result == null)
			{
				System.out.println("No " + i + " in this tree.");
			}
			else
			{
				System.out.println("There is a " + result.getData() + " in this tree.");
			}
		}
		
	}
	
	public static BinaryNodeInterface<Integer> genBST(Integer[] data, ArrayList<BinaryNode<Integer>> nodes)
	{
		if(data.length == 0)
		{
			return null;
		}
		else
		{
			BinaryNodeInterface<Integer> root = new BinaryNode<Integer>(data[0]);
			nodes.add((BinaryNode<Integer>) root);

			for(int i = 1; i < data.length; i++)
			{
				BinaryNodeInterface<Integer> currentNode = root;
				boolean done = false;
				
				while(!done)
				{
					if(data[i].compareTo(currentNode.getData()) < 0)
					{
						if(currentNode.getLeftChild() != null)
						{
							currentNode = currentNode.getLeftChild();
						}
						else
						{
							BinaryNodeInterface<Integer> newNode = new BinaryNode<Integer>(data[i]);
							nodes.add((BinaryNode<Integer>) newNode);
							currentNode.setLeftChild(newNode);
							done = true;
						}
					}
					else
					{
						if(currentNode.getRightChild() != null)
						{
							currentNode = currentNode.getRightChild(); 
						}
						else
						{
							BinaryNodeInterface<Integer> newNode = new BinaryNode<Integer>(data[i]);
							nodes.add((BinaryNode<Integer>) newNode);
							currentNode.setRightChild(newNode);
							done = true;
						}
					}
				}
			}
			
			return root;
		}
	}
	
	public static Integer[] getRandomIntArray(int numElements)
	{
		Integer[] result = new Integer[numElements];
		Random rand = new Random();
		rand.setSeed(System.currentTimeMillis());

		result[0] = rand.nextInt(5) + 1;
		
		for(int i = 1; i < numElements; i++)
		{
			result[i] = result[i - 1] + rand.nextInt(5) + 1;
		}
		
		for(int i = 0; i < 100; i++)
		{
			int first = rand.nextInt(numElements);
			int second = rand.nextInt(numElements);
			int temp = result[first];
			result[first] = result[second];
			result[second] = temp;
		}
		
		return result;
	}
	
	public static Integer getMax(Integer[] array)
	{
		Integer max = array[0];
		
		for(int i = 1; i < array.length; i++)
		{
			if(array[i].compareTo(max) > 0)
			{
				max = array[i];
			}
		}
		
		return max;
	}
	
	public static Integer getMin(Integer[] array)
	{
		int min = array[0];
		
		for(int i = 1; i < array.length; i++)
		{
			if(array[i].compareTo(min) < 0)
			{
				min = array[i];
			}
		}
		
		return min;
	}
	
	public static <T> void printInorderLeft(BinaryNodeInterface<T> root)
	{
		printInorderLeftRec(root);
		System.out.println();
	}
	
	public static <T> void printInorderLeftRec(BinaryNodeInterface<T> root)
	{
		if(root != null)
		{
			printInorderLeftRec(root.getLeftChild());
			System.out.print(root.getData() + " ");
			printInorderLeftRec(root.getRightChild());
		}
	}

	public static <T> void printInorderRight(BinaryNodeInterface<T> root)
	{
		printInorderRightRec(root);
		System.out.println();
	}
	
	public static <T> void printInorderRightRec(BinaryNodeInterface<T> root)
	{
		if(root != null)
		{
			printInorderRightRec(root.getRightChild());
			System.out.print(root.getData() + " ");
			printInorderRightRec(root.getLeftChild());
		}
	}

	public static <T> void printArray(T[] array)
	{
		System.out.print("[");
		
		for(int i = 0; i < array.length - 1; i++)
		{
			System.out.print(array[i] + ",");
		}
		
		if(array.length > 0)
		{
			System.out.print(array[array.length - 1]);
		}
		
		System.out.println("]");
	}
}
