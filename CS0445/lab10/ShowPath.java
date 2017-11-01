import java.util.Random;


public class ShowPath
{
	public static void main(String[] args)
	{
		int point = 0;
		BinaryNodeInterface<Character> root = generateTree();

		System.out.println("Your string returned from the method getAllPaths() is as follows:");
		String str = getAllPaths(root);
		System.out.println(str);

		System.out.println("Your result of using the method getPathTo() for every character is as follows:");
		for(int i = 0; i < 52; i++)
		{
			if(i < 26)
			{
				System.out.println("Path to " + (char) ('a' + i) + " " + getPathTo(root, (char) ('a' + i)));
			}
			else
			{
				System.out.println("Path to " + (char) ('A' + (i - 26)) + " " + getPathTo(root, (char) ('A' + (i - 26))));
			}
		}

		System.out.println();

		if(!checkGetAllPaths(root, str))
		{
			point = point + 5;
		}

		System.out.println("Your current point is " + point + ".");

		if(!checkGetPathTo(root))
		{
			point = point + 5;
		}

		System.out.println("Your total point is " + point + ".");
	}

	private static String getAllPaths(final BinaryNodeInterface<Character> root)
	{
		// TO DO
		// // need a helper method!!!!
		// if(root != null) {
		// 	System.out.printf("%d", root.getData());
		// 	getAllPaths(root.getLeftChild());
		// 	getAllPaths(root.getRightChild());
		// }
		// return "";
		StringBuilder builder = new StringBuilder();
		getAllPaths2(root, builder, "");
		// fully prints out string (dont need to print out string in helper method) use append method
		return builder.toString();
	}
	private static void getAllPaths2(BinaryNodeInterface<Character> currentRoot, StringBuilder builder, String currentPlace) {
		// preorder traversal
		if (currentRoot != null) {
			builder.append(currentRoot.getData() + " " + currentPlace + "\n");
			getAllPaths2(currentRoot.getLeftChild(), builder, currentPlace + "0");
			getAllPaths2(currentRoot.getRightChild(), builder, currentPlace + "1");
		}
	}

	private static String getPathTo(final BinaryNodeInterface<Character> root, char c)
	{
		// TO DO
		// String currentPlace = "";
		// if (root.getData().equals(c)) {
		// 	return currentPlace;
		// }
		// else {
		// 	// need to create a helper method... for recursion
		// }
		String a = getPath2(root, c, "");
		return a;
	}

	private static String getPath2(BinaryNodeInterface<Character> currentRoot, char c, String currentPlace) {
		if (currentRoot != null) {
			if(currentRoot.getData().equals(c)) {
				return currentPlace;
			}
			else {
				// preorder traversal starts at left child
				String b = getPath2(currentRoot.getLeftChild(), c, currentPlace + "0");
				if (b != null) {
					return b;
				}
				else {
					String d = getPath2(currentRoot.getRightChild(), c, currentPlace + "1");
					return d;
				}
			}
		}
		else {
			return null;
		}
	}

	private static boolean checkGetAllPaths(BinaryNodeInterface<Character> root, String str)
	{
		boolean error = false;
		String[] list = str.split("\n");

		// check for duplicate characters and number of character

		for(int i = 0; i < list.length; i++)
		{
			if(!list[i].equals(""))
			{
				char c = list[i].charAt(0);

				for(int j = i + 1; j < list.length; j++)
				{
					if(!list[j].equals(""))
					{
						if(c == list[j].charAt(0))
						{
							System.out.println("There are more than one character '" + c + "' in your output string.");
							error = true;
						}
					}
				}
			}
		}

		// Check paths

		for(int i = 0; i < list.length; i++)
		{
			String temp = list[i];

			if(!temp.equals(""))
			{
				char c = temp.charAt(0);
				String path = temp.substring(2);
				BinaryNodeInterface<Character> currentNode = root;

				for(int j = 0; j < path.length(); j++)
				{
					if(path.charAt(j) == '0')
					{
						currentNode = currentNode.getLeftChild();
					}
					else
					{
						currentNode = currentNode.getRightChild();
					}
				}

				char nodeCharacter = currentNode.getData();

				if(c != nodeCharacter)
				{
					System.out.println("The line \"" + list[i] + "\" says the path to the character " + c + " is " + path + ".");
					System.out.println("But the path " + path + " goes to the node containing the character " + nodeCharacter + ".");
					error = true;
				}
			}
		}

		System.out.print("Testing the method getAllPath(): ");

		if(!error)
		{
			System.out.println("PASS");
		}
		else
		{
			System.out.println("FAIL");
		}

		return error;
	}

	private static boolean checkGetPathTo(BinaryNodeInterface<Character> root)
	{
		boolean error = false;

		for(int i = 0; i < 52; i++)
		{
			char c;

			if(i < 26)
			{
				c = (char) ('a' + i);
			}
			else
			{
				c = (char) ('A' + (i - 26));
			}

			String path = getPathTo(root, c);
			BinaryNodeInterface<Character> currentNode = root;

			for(int j = 0; j < path.length(); j++)
			{
				if(path.charAt(j) == '0')
				{
					currentNode = currentNode.getLeftChild();
				}
				else
				{
					currentNode = currentNode.getRightChild();
				}
			}

			char nodeCharacter = currentNode.getData();

			if(c != nodeCharacter)
			{
				System.out.println("Your method getPathTo() says the path to the character " + c + " is " + path + ".");
				System.out.println("But the path " + path + " goes to the node containing the character " + nodeCharacter + ".");
				error = true;
			}
		}

		System.out.print("Testing the method getPathTo(): ");

		if(!error)
		{
			System.out.println("PASS");
		}
		else
		{
			System.out.println("FAIL");
		}

		return error;
	}

	// _______________________________________________________________________________
	// _______________________________________________________________________________

	private static BinaryNodeInterface<Character> generateTree()
	{
		char[] charList = new char[52];

		for(int i = 0; i < 52; i++)
		{
			if(i < 26)
			{
				charList[i] = (char) ('a' + i);
			}
			else
			{
				charList[i] = (char) ('A' + (i - 26));
			}
		}

		Random rand = new Random();
		rand.setSeed(System.currentTimeMillis());

		for(int i = 0; i < 1000; i++)
		{
			int index1 = rand.nextInt(52);
			int index2 = rand.nextInt(52);
			char temp = charList[index1];
			charList[index1] = charList[index2];
			charList[index2] = temp;
		}

		BinaryNodeInterface<Character> root = new BinaryNode<Character>(charList[0]);
		SimpleQueue<BinaryNodeInterface<Character>> queue = new SimpleQueue<BinaryNodeInterface<Character>>();
		queue.enqueue(root);

		for(int i = 1; i < 52; i++)
		{
			BinaryNodeInterface<Character> currentNode = queue.getFront();
			BinaryNodeInterface<Character> newNode = new BinaryNode<Character>(charList[i]);

			if(!currentNode.hasLeftChild())
			{
				currentNode.setLeftChild(newNode);
			}
			else if(!currentNode.hasRightChild())
			{
				currentNode.setRightChild(newNode);
			}
			else
			{
				queue.dequeue();
				currentNode = queue.getFront();
				currentNode.setLeftChild(newNode);
			}
			queue.enqueue(newNode);
		}

		return root;
	}
}
