
public class Pair<T1,T2> implements PairInterface<T1,T2>
{
	// TO DO: Instance Variables
	private T1 x;
	private T2 y;

	public Pair(T1 aFirst, T2 aSecond)
	{
		// TO DO: Constructor
		x = aFirst;
		y = aSecond;
	}

	/**
	 * Gets the first element of this pair.
	 * @return the first element of this pair.
	 */
	public T1 fst()
	{
		// TO DO
		return x;
	}

	/**
	 * Gets the second element of this pair.
	 * @return the second element of this pair.
	 */
	public T2 snd()
	{
		// TO DO
		return y;
	}

	/**
	 * Sets the first element to aFirst.
	 * @param aFirst  the new first element
	 */
	public void setFst(T1 aFirst)
	{
		// TO DO
		this.x = aFirst;
	}

	/**
	 * Sets the second element to aSecond.
	 * @param aSecond  the new second element
	 */
	public void setSnd(T2 aSecond)
	{
		// TO DO
		this.y = aSecond;
	}

	/**
	 * Checks whether two pairs are equal. Note that the pair
	 * (a,b) is equal to the pair (x,y) if and only if a is
	 * equal to x and b is equal to y.
	 * @return true if this pair is equal to aPair. Otherwise
	 * return false.
	 */
	public boolean equals(Object otherObject)
	{
		if(otherObject == null)
		{
			return false;
		}

		if(getClass() != otherObject.getClass())
		{
			return false;
		}

		// TO DO
		Pair<T1,T2> myObject= (Pair<T1,T2>) otherObject;
		if(myObject.fst().equals(x) && myObject.snd().equals(y)){
			return true;
		}else{
			return false;
		}
		}

	/**
	 * Generates a string representing this pair. Note that
	 * the String representing the pair (x,y) is "(x,y)". There
	 * is no whitespace unless x or y or both contain whitespace
	 * themselves.
	 * @return a string representing this pair.
	 */
	public String toString()
	{
		// TO DO
		String z = new String("(" + x + "," + y + ")");
		return z;
	}
}
