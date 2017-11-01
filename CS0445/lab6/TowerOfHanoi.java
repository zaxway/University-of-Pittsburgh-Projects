
public class TowerOfHanoi
{
	// TO DO: Instance Variables
	private int [] tower1;
	private int [] tower2;
	private int [] tower3;
	private int [] disca;

	/* Construct the Towers of Hanoi (3 towers) with aNumDisc
	 * on the first tower. Each tower can be identified by an
	 * integer number (0 for the first tower, 1 for the second
	 * tower, and 2 for the third tower). Each disc can be identified
	 * by an integer number starting from 0 (for the smallest disc)
	 * and (aNumDisc - 1) for the largest disc.
	 */
	public TowerOfHanoi(int aNumDiscs)
	{
		// TO DO: Constructor
		disca = new int [aNumDiscs];
		tower1 = new int[disca.length];
		tower2 = new int[0];
		tower3 = new int[0];
		for (int d = 0; d < disca.length; d++) {
			tower1[d] = d;
		}


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
		// TO DO
		if (tower == 0) {
			for (int i = tower1.length; i < 0; i--) {
				tower1[i] = i;
			}
			return tower1;
		}
		else if (tower == 1) {
			for (int d = tower2.length; d < 0; d--) {
				tower2[d] = d;
			}
			return tower2;
		}
		else if (tower == 2) {
			for (int e = tower3.length; e < 0; e--) {
				tower3[e] = e;
			}
			return tower3;
		}
		else {
			return null;
		}
	}

	/* Gets the total number of discs in this Towers of Hanoi
	 * @return the total number of discs in this Towers of Hanoi
	 */
	public int getNumberOfDiscs()
	{
		// TO DO
		return disca.length;

	}

	/* Gets the number of discs on a tower.
	 * @param tower the tower identifier (0, 1, or 2)
	 * @return the number of discs on the tower.
	 */
	public int getNumberOfDiscs(int tower)
	{
		// TO DO
		if (tower == 0) {
			return tower1.length;
		}
		else if (tower == 1) {
			return tower2.length;
		}
		else if (tower == 2) {
			return tower3.length;
		}
		else {
			return 0;
		}
	}

	/* Moves the top disc from fromTower to toTower. Note that
	 * this operation has to follow the rule of the Tower of Hanoi
	 * puzzle. First fromTower must have at least one disc and second
	 * the top disc of toTower must not be smaller than the top disc
	 * of the fromTower.
	 * @param fromTower the source tower
	 * @param toTower the destination tower
	 * @return ture if successfully move the top disc from
	 *         fromTower to toTower.
	 */

	// public boolean hasDisc(int [] tower1, int [] tower2, int [] tower3) {
	// 	return true;
	//
	// }
	//
	// public boolean notSmaller(int [] disca) {
	// 	return true;
	//
	// }

	public boolean moveTopDisc(int fromTower, int toTower)
	{
		// TO DO
		// if (hasDisc() && notSmaller()) {
		// 	return true;
		//
		// }
		// else {
			return true;
		//}
	}
}
