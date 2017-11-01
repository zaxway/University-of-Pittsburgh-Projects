/* Mohit Jain
	CS 0445 Professor Tan
	March 16, 2016 */

	// Quick Note about this program. Multiply method has not been implemented yet, but when it runs,
	// It adds all the numbers properly, except for the fact that it returns them in their backwards form.
	// For example if you perform the operation 32 + 32, instead of returning 64 it will return 46. If you
	// perform the operation 50 + 50 it will return 001, instead of returning 100.


public class LInfiniteInteger implements InfiniteIntegerInterface
{
	private Node firstNode;
	private Node lastNode;
	private Node middleNode;
	private int middlePosition;
	private int numberOfDigits;
	private boolean isNegative;

	/**
	 * Constructor: Constructs this infinite integer from a string
	 * representing an integer.
	 * @param s  a string represents an integer
	 */
	public LInfiniteInteger(String s)
	{
		// TO DO
		int newNumber = 0;
		firstNode = null;
		lastNode = null;
		middleNode = null;
		middlePosition = 0;
		numberOfDigits = 0;
		isNegative = false;
		for (int i = 0; i < s.length(); i++) {
			newNumber = (int) s.charAt(i) -48;
			s = s.replaceFirst("^(-?)0+(?!$)", "");
			if (newNumber == (int) '-') {
				isNegative = true;
			}
			else if (newNumber >= 0) {
				this.add(newNumber);
			}
		}
	}

	/**
	 * Constructor: Constructs this infinite integer from an integer.
	 * @param anInteger  an integer
	 */
	public LInfiniteInteger(int anInteger)
	{
		// TO DO
		firstNode = null;
		lastNode = null;
		middleNode = null;
		middlePosition = 0;
		numberOfDigits = 0;
		isNegative = false;
		if (anInteger < 0) {
			isNegative = true;
		}
		else if (anInteger >= 0) {
			add2(anInteger);
		}
	}

	/**
	 * Gets the number of digits of this infinite integer.
	 * @return an integer representing the number of digits
	 * of this infinite integer.
	 */
	public int getNumberOfDigits()
	{
		// TO DO
		// removeLeadingZeros(this);
		if (isNegative == true) {
			numberOfDigits = numberOfDigits - 1;
		}
		return numberOfDigits;
	}
	// public void removeLeadingZeros(LInfiniteInteger anInfiniteInteger)
	// {
	// 	Node currentNode = firstNode;
	// 	while ((currentNode.data == 0)) {
	// 		currentNode = currentNode.next;
	// 		numberOfDigits--;
	// 	}
	// }

	/**
	 * Checks whether this infinite integer is a negative number.
	 * @return true if this infinite integer is a negative number.
	 * Otherwise, return false.
	 */
	public boolean isNegative()
	{
		// TO DO
		return isNegative;
	}

	/**
	 * Calculates the result of this infinite integer plus anInfiniteInteger
	 * @param anInfiniteInteger the infinite integer to be added to this
	 * infinite integer.
	 * @return a NEW infinite integer representing the result of this
	 * infinite integer plus anInfiniteInteger
	 */
	public InfiniteIntegerInterface plus(final InfiniteIntegerInterface anInfiniteInteger)
	{
		// TO DO
		// this
		// anInfiniteInteger
		// this.firstNode
		// LInfiniteInteger temp = (LInfiniteInteger) anInfiniteInteger;
		// temp.firstNode
		int carryOver = 0;
		int answer = 0;
		LInfiniteInteger firstNumber = new LInfiniteInteger(this.toString());
		LInfiniteInteger secondNumber = new LInfiniteInteger(anInfiniteInteger.toString());
		LInfiniteInteger thirdNumber = new LInfiniteInteger("");
		Node currentNode1 = firstNumber.lastNode;
		Node currentNode2 = secondNumber.lastNode;

		// Both are negative!!
		if ((firstNumber.isNegative == true) && (secondNumber.isNegative == true)) {
			firstNumber.isNegative = false;
			secondNumber.isNegative = false;
			LInfiniteInteger temp = new LInfiniteInteger(firstNumber.plus(secondNumber).toString());
			Node currentNode = temp.firstNode;
			while (currentNode != null) {
				thirdNumber.add(currentNode.data);
				currentNode = currentNode.next;
			}
			thirdNumber.isNegative = true;
			// firstNumber.isNegative = false;
			// secondNumber.isNegative = false;

			return thirdNumber;
		}


		// Paper method requires you to subtract in this case.
		// firstNumber is positive and second is negative. positive - negative = thirdNumber.
		else if ((firstNumber.isNegative == false) && (secondNumber.isNegative == true)) {
			if (firstNumber.compare2(secondNumber) == 1) {
				secondNumber.isNegative = false;
				LInfiniteInteger temp = new LInfiniteInteger(firstNumber.minus(secondNumber).toString()); // subtract
				Node currentNode = temp.firstNode;
				while (currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				return thirdNumber;
			}

			else if (firstNumber.compare2(secondNumber) == 0) {
				thirdNumber.add(0);
				return thirdNumber;
			}

			else {
				secondNumber.isNegative = false;
				LInfiniteInteger temp = new LInfiniteInteger(firstNumber.minus(secondNumber).toString());
				Node currentNode = temp.firstNode;
				while (currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				thirdNumber.isNegative = true;
				return thirdNumber;

			}
		}


		// FirstNumber is negative and second is positive.
		// Positive - negative = second - first = temp
		else if ((firstNumber.isNegative == true) && (secondNumber.isNegative == false)) {
			if (firstNumber.compare2(secondNumber) == 1) {
				// secondNumber.isNegative = false;
				LInfiniteInteger temp = new LInfiniteInteger(secondNumber.minus(firstNumber).toString());
				Node currentNode = temp.firstNode;
				while (currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				return thirdNumber;
			}

			else if (firstNumber.compare2(secondNumber) == 0) { // might need to edit the compare2 method.
				thirdNumber.add(0);
				return thirdNumber;
			}

			else {
				// secondNumber.isNegative == false;
				LInfiniteInteger temp = new LInfiniteInteger(secondNumber.minus(firstNumber).toString());
				Node currentNode = temp.firstNode;
				while (currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				thirdNumber.isNegative = true;
				return thirdNumber;

			}
		}

		// both are positive
		else {
			while ((currentNode1 != null) && (currentNode2 != null)) {
				answer = currentNode1.data + currentNode2.data + carryOver;
				thirdNumber.add2((answer % 10));
				carryOver = answer/10;
				currentNode2 = currentNode2.previous;
				currentNode1 = currentNode1.previous;
			}
			if (currentNode1 == null) {
				while(currentNode2 != null) {
					answer = currentNode2.data + carryOver;
					thirdNumber.add2((answer % 10));
					carryOver = answer/10;
				}
			}
			else if (currentNode2 == null) {
				while(currentNode1 != null) {
					answer = currentNode1.data + carryOver;
					thirdNumber.add2((answer % 10));
					carryOver = answer/10;
			}
		}
		if (carryOver > 0) {
			thirdNumber.add2(carryOver);
		}
		return thirdNumber;
	}
}

	/**
	 * Calculates the result of this infinite integer subtracted by anInfiniteInteger
	 * @param anInfiniteInteger the infinite integer to subtract.
	 * @return a NEW infinite integer representing the result of this
	 * infinite integer subtracted by anInfiniteInteger
	 */
	public InfiniteIntegerInterface minus(final InfiniteIntegerInterface anInfiniteInteger)
	{
		// TO DO
		int answer = 0;
		boolean negativeAnswer = false;
		LInfiniteInteger firstNumber = new LInfiniteInteger(this.toString());
		LInfiniteInteger secondNumber = new LInfiniteInteger(anInfiniteInteger.toString());
		LInfiniteInteger thirdNumber = new LInfiniteInteger("");
		Node currentNode1 = firstNumber.lastNode;
		Node currentNode2 = secondNumber.lastNode;
		if ((firstNumber.isNegative == false) && (secondNumber.isNegative == false)) {
			if (firstNumber.compare2(secondNumber) == 1) {
				while ((currentNode1 != null) && (currentNode2 != null)) {
					if (currentNode1.data > currentNode2.data) {
						answer = currentNode1.data - currentNode2.data;
						thirdNumber.add2(answer);
					}
					else if (currentNode1.data < currentNode2.data) {
						currentNode1.data = currentNode1.data + 10;
						currentNode1 = currentNode1.previous;
						currentNode1.data = currentNode1.data - 1;
						answer = currentNode1.data - currentNode2.data;
						thirdNumber.add2(answer);
					}
				}
				if (currentNode1 == null) {
					while (currentNode2 != null) {
						thirdNumber.add2(currentNode2.data);
						currentNode2 = currentNode2.previous;
					}
				}
				else if (currentNode2 == null) {
					while(currentNode1 != null) {
						thirdNumber.add2(currentNode1.data);
						currentNode1 = currentNode1.previous;
					}
				}
				return thirdNumber;
			}

			else if(firstNumber.compare2(secondNumber) == 0) {
				thirdNumber.add(0);
				return thirdNumber;
			}

			else {
				LInfiniteInteger temp = new LInfiniteInteger(firstNumber.minus(secondNumber).toString());
				Node currentNode = temp.firstNode;
				while (currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				thirdNumber.isNegative = true;
				return thirdNumber;
			}
		}

		else if ((firstNumber.isNegative == false) && (secondNumber.isNegative == true)) {
			secondNumber.isNegative = false;
			LInfiniteInteger temp = new LInfiniteInteger(firstNumber.plus(secondNumber).toString()); //might need to edit this one
			Node currentNode = temp.firstNode;
			while (currentNode != null) {
				thirdNumber.add(currentNode.data);
				currentNode = currentNode.next;
			}
			return thirdNumber;
		}

		else if ((firstNumber.isNegative == true) && (secondNumber.isNegative == false)) {
			firstNumber.isNegative = false;
			LInfiniteInteger temp = new LInfiniteInteger(firstNumber.plus(secondNumber).toString());
			Node currentNode = temp.firstNode;
			while (currentNode != null) {
				thirdNumber.add(currentNode.data);
				currentNode = currentNode.next;
			}
			return thirdNumber;
		}

		else {
			if (firstNumber.compare2(secondNumber) == -1) {
				firstNumber.isNegative = false;
				secondNumber.isNegative = false;
				LInfiniteInteger temp = new LInfiniteInteger(firstNumber.minus(secondNumber).toString());
				Node currentNode = temp.firstNode;
				while(currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				return thirdNumber;

			}
			else if (firstNumber.compare2(secondNumber) == 0) {
				thirdNumber.add(0);
				return thirdNumber;
			}
			else {
				firstNumber.isNegative = false;
				secondNumber.isNegative = false;
				LInfiniteInteger temp = new LInfiniteInteger(firstNumber.minus(secondNumber).toString());
				Node currentNode = temp.firstNode;
				while(currentNode != null) {
					thirdNumber.add(currentNode.data);
					currentNode = currentNode.next;
				}
				thirdNumber.isNegative = true;
				return thirdNumber;
			}
		}


	}

	/**
	 * Generates a string representing this infinite integer. If this infinite integer
	 * is a negative number a minus symbol should be in the front of numbers. For example,
	 * "-12345678901234567890". But if the infinite integer is a positive number, no symbol
	 * should be in the front of the numbers (e.g., "12345678901234567890").
	 * @return a string representing this infinite integer number.
	 */
	public String toString()
	{
		// TO DO
		Node currentNode = firstNode;
		String returnInfiniteInteger = "";
		if (isNegative == true) {
			returnInfiniteInteger = "-";
		}
		while (currentNode != null) {
			returnInfiniteInteger = returnInfiniteInteger + currentNode.data;
			currentNode = currentNode.next;
		}
		return returnInfiniteInteger;
	}

	/**
	 * Compares this infinite integer with anInfiniteInteger
	 * @return either -1, 0, or 1 as follows:
	 * If this infinite integer is less than anInfiniteInteger, return -1.
	 * If this infinite integer is equal to anInfiniteInteger, return 0.
	 * If this infinite integer is greater than anInfiniteInteger, return 1.
	 */
	public int compareTo(InfiniteIntegerInterface anInfiniteInteger)
	{
		// TO DO
		LInfiniteInteger a = new LInfiniteInteger(this.toString());
		LInfiniteInteger b = new LInfiniteInteger(anInfiniteInteger.toString());
		if ((a.isNegative == true) && (b.isNegative == false)) {
			// so now a is less than b
			return -1;
		}
		else if ((a.isNegative == false) && (b.isNegative == true)) {
			// a is greater than b
			return 1;
		}
		else if ((a.isNegative == false) && (b.isNegative == false)) {
			// a and b are positive
			if (a.numberOfDigits < b.numberOfDigits) {
				return -1;
			}
			else if (a.numberOfDigits > b.numberOfDigits) {
				return 1;
			}
			else {
				Node currentNode1 = a.firstNode;
				Node currentNode2 = b.firstNode;
				while((currentNode1 != null) && (currentNode2 != null)) {
					if (currentNode1.data < currentNode2.data) {
						return -1;
					}
					else if (currentNode1.data > currentNode2.data) {
						return 1;
					}
					// else if (currentNode1.data = currentNode2.data) {
					// 	return 0;
					// }
					else {
						currentNode1 = currentNode1.next;
						currentNode2 = currentNode2.next;
					}
				}
			}
		}

		else {
			if (a.numberOfDigits < b.numberOfDigits) {
				return -1;
			}
			else if (a.numberOfDigits > b.numberOfDigits) {
				return 1;
			}
			else {
				Node currentNode1 = a.firstNode;
				Node currentNode2 = b.firstNode;
				while((currentNode1 != null) && (currentNode2 != null)) {
					if (currentNode1.data < currentNode2.data) {
						return -1;
					}
					else if (currentNode1.data > currentNode2.data) {
						return 1;
					}
					else {
						currentNode1 = currentNode1.next;
						currentNode2 = currentNode2.next;
					}
				}
				return 0;
			}
		}
		return 0;
	}

	public int compare2(InfiniteIntegerInterface anInfiniteInteger) {
		LInfiniteInteger a = new LInfiniteInteger(this.toString());
		LInfiniteInteger b = new LInfiniteInteger(anInfiniteInteger.toString());
		a.isNegative = false;
		b.isNegative = false;
		if (a.numberOfDigits < b.numberOfDigits) {
			return -1;
		}
		else if (b.numberOfDigits < a.numberOfDigits) {
			return 1;
		}
		else {
			Node currentNode1 = a.firstNode;
			Node currentNode2 = b.firstNode;
			while((currentNode1 != null) && (currentNode2 != null)) {
				if (currentNode1.data > currentNode2.data) {
					return 1;
				}
				else if (currentNode1.data < currentNode2.data) {
					return -1;
				}
				else {
					currentNode1 = currentNode1.next;
					currentNode2 = currentNode2.next;
				}
			}
		}
		return 0;
	}

	/**
	 * Calculates the result of this infinite integer multiplied by anInfiniteInteger
	 * @param anInfiniteInteger the multiplier.
	 * @return a NEW infinite integer representing the result of this
	 * infinite integer multiplied by anInfiniteInteger.
	 */
	public InfiniteIntegerInterface multiply(final InfiniteIntegerInterface anInfiniteInteger)
	{
		// TO DO
		return anInfiniteInteger;

	}




	// Implement DLinkedlist add method
	public void add(int newNumber) {
		if(firstNode == null)
		{
			firstNode = new Node(null, newNumber, null);
			lastNode = firstNode;
		}
		else
		{
			Node newNode = new Node(lastNode, newNumber, null);
			lastNode.next = newNode;
			lastNode = newNode;
		}

		numberOfDigits++;

		if(numberOfDigits % 2 == 1)
		{
			if(middleNode == null)
			{
				middleNode = firstNode;
			}
			else
			{
				middleNode = middleNode.next;
			}
			middlePosition++;
		}
	}

	public void add2(int anInteger) {
		if(firstNode == null)
		{
			firstNode = new Node(null, anInteger, null);
			lastNode = firstNode;
		}
		else
		{
			Node newNode = new Node(lastNode, anInteger, null);
			lastNode.next = newNode;
			lastNode = newNode;
		}

		numberOfDigits++;

		if(numberOfDigits % 2 == 1)
		{
			if(middleNode == null)
			{
				middleNode = firstNode;
			}
			else
			{
				middleNode = middleNode.previous;
			}
			middlePosition++;
		}
	}


	// End of Implementaion

	private class Node
	{
		private int data;
		private Node next;
		private Node previous;

		private Node(Node previousNode, int aData, Node nextNode)
		{
			previous = previousNode;
			data = aData;
			next = nextNode;
		}

		private Node(int aData)
		{
			this(null, aData, null);
		}
	}
}
