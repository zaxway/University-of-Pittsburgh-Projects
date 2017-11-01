
public class TowerOfHanoi
{
	// DONE: Instance Variables
	private int[] firstTower;
	private int[] secondTower;
	private int[] thirdTower;
	private int firstDisc;
	private int secondDisc;
	private int thirdDisc;

	/* Construct the Towers of Hanoi (3 towers) with aNumDisc
	 * on the first tower. Each tower can be identified by an
	 * integer number (0 for the first tower, 1 for the second
	 * tower, and 2 for the third tower). Each disc can be identified
	 * by an integer number starting from 0 (for the smallest disc)
	 * and (aNumDisc - 1) for the largest disc.
	 */
	public TowerOfHanoi(int aNumDiscs)
	{
		// DONE: Constructor
		firstTower = new int[aNumDiscs];

        for(int i = 0; i < aNumDiscs; i++)
        {
            firstTower[i] = aNumDiscs- 1 - i;
        }
        secondTower = new int[aNumDiscs];
        secondTower[0] = aNumDiscs;
        secondTower[0] = 0;

        thirdTower = new int[aNumDiscs];
        thirdTower[0] = aNumDiscs;
        thirdTower[0] = 0;

        firstDisc = aNumDiscs;
        secondDisc = 0;
        thirdDisc = 0;
	}

	/* Returns an array of integer representing the order of
	 * discs on the tower (from bottom up). The bottom disc should
	 * be the first element in the array and the top disc should be
	 * the last element of the array. The size of the array MUST
	 * be the number of discs on the tower. For example, suppose
	 * the tower 0 contains the following discs 0,1,4,6,7,8 (from top
	 * to bottom). This method should return the array [8,7,6,4,1,0]
	 * (from first to last).
	 * @param tower the integer identify the tower number.
	 * @return an array of integer representing the order of discs.
	 */
	public int[] getArrayOfDiscs(int tower)
	{
		// DONE
	   	int[] temporal;

        	if(tower == 0)
        	{
	            temporal = new int[firstDisc];
	            for(int i = 0; i < firstDisc; i++)
	             {
	                    temporal[i] = firstTower[i];
	             }
	             return temporal;
                // return firstTower;
	        }
	         if(tower == 1)
            {
	            temporal = new int[secondDisc];
	            for(int i = 0; i < secondDisc; i++)
	            {
	                temporal[i] = secondTower[i];
	            }
	            return temporal;
                // return secondTower;
	        }
	         if(tower == 2)
            {
	            temporal = new int[thirdDisc];
	             for(int i = 0; i < thirdDisc; i++)
	             {
	                    temporal[i] = thirdTower[i];
	             }
	             return temporal;
                // return thirdTower;
	        }
	        return firstTower;
	}

	/* Gets the total number of discs in this Towers of Hanoi
	 * @return the total number of discs in this Towers of Hanoi
	 */
	public int getNumberOfDiscs()
	{
		// DONE
		int sum = firstDisc+secondDisc+thirdDisc;
		return sum;
	}

	/* Gets the number of discs on a tower.
	 * @param tower the tower identifier (0, 1, or 2)
	 * @return the number of discs on the tower.
	 */
	public int getNumberOfDiscs(int tower)
	{
		// DONE
		if(tower==0)
		{
			return firstDisc;
		}
		if(tower==1)
		{
			return secondDisc;
		}
		if(tower==2)
		{
			return thirdDisc;
		}
		return 0;
	}

	/* Moves the top disc from fromTower to toTower. Note that
	 * this operation has to follow the rule of the Tower of Hanoi
	 * puzzle. First fromTower must have at least one disc and second
	 * the top disc of toTower must not be smaller than the top disc
	 * of the fromTower.
	 * @param fromTower the source tower
	 * @param toTower the destination tower
	 * @return true if successfully move the top disc from
	 *         fromTower to toTower.
	 */
	public boolean moveTopDisc(int fromTower, int toTower)
	{
		// DONE
		    if((fromTower == 0 && firstDisc == 0)||(fromTower == 1 && secondDisc == 0) || (fromTower == 2 && thirdDisc == 0))
		    {
                return false;
            }
            if(fromTower == 0)
            {
                if(toTower == 1)
                {
                    if(secondDisc != 0&&firstTower[firstDisc-1]>secondTower[secondDisc-1])
                    {
                   		 return false;
              	  	}
                	else
                	{
                        secondTower[secondDisc]=firstTower[firstDisc-1];
                        firstTower[firstDisc-1] = 0;
                        firstDisc--;
                        secondDisc++;
                        return true;
                	}
                }
                if(toTower == 2)
                {
                    if(thirdDisc != 0&&firstTower[firstDisc-1] > thirdTower[thirdDisc-1])
                    {
                        return false;
                    }
                    else
                    {
                        thirdTower[thirdDisc] = firstTower[firstDisc-1];
                        firstTower[firstDisc-1] = 0;
                        firstDisc--;
                        thirdDisc++;
                        return true;
                    }
                }
            }
            if(fromTower == 1)
            {
                if(toTower == 0)
                {
                    if(firstDisc != 0&&secondTower[secondDisc-1]>firstTower[firstDisc-1])
                    {
                        return false;
                    }
                    else
                    {
                        firstTower[firstDisc]=secondTower[secondDisc-1];
                        secondTower[secondDisc-1] = 0;
                        secondDisc--;
                        firstDisc++;
                        return true;
                    }
                }
                if(toTower == 2)
                {
                    if(thirdDisc!= 0&&secondTower[secondDisc-1] > thirdTower[thirdDisc-1])
                    {
                        return false;
                    }
                    else
                    {
                        thirdTower[thirdDisc] = secondTower[secondDisc-1];
                        secondTower[secondDisc-1] = 0;
                        secondDisc--;
                        thirdDisc++;
                        return true;
                    }
                }
            }

            if (fromTower == 2)
            {
                if (toTower == 0)
                {
                    if (firstDisc != 0 && thirdTower[thirdDisc - 1] > firstTower[firstDisc - 1])
                    {
                    	return false;
                	}
                    else
                    {
                        firstTower[firstDisc]=thirdTower[thirdDisc-1];
                        thirdTower[thirdDisc-1] = 0;
                        thirdDisc--;
                        firstDisc++;
                        return true;
                    }
                }
                if(toTower == 1)
                {
                    if(secondDisc !=0&&thirdTower[thirdDisc-1] > secondTower[secondDisc-1])
                    {
                        return false;
                    }
                    else
                    {
                        secondTower[secondDisc] = thirdTower[thirdDisc-1];
                        thirdTower[thirdDisc-1] = 0;
                        thirdDisc--;
                        secondDisc++;
                        return true;
                    }
                }
            }
          	return false;
	}
	}
