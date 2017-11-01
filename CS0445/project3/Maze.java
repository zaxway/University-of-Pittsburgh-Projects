import java.util.Random;
// No other import statement is allowed

public class Maze
{
	// TO DO: Instance Variable
	private int width;
	private int height;
	private boolean [][] horiz;
	private boolean [][] vert;
	Random num = new Random();

	/**
	 * Constructor
	 * @param aWidth the number of chambers in each row
	 * @param aHeight the number of chamber in each column
	 */
	public Maze(int aWidth, int aHeight)
	{
		// TO DO: Constructor
		// Create the dimensions of the maze: height and width. ex. 20 x 23
		// rectangle/square has been formed.
		width = aWidth;
		height = aHeight;
		// creates the maze parts (chambers).
		horiz = new boolean[width + 1][height];
		vert = new boolean[width][height + 1];
		// boolean a = (width > height);
		for (int i = 0; i < ((width > height) ? width: height); i++) {
			if (i == horiz.length - 1 || i == vert.length - 1) {
				break;
			}
			if (i < height) {
				vert[0][i] = true;
				vert[width][i] = true;
			}
			if (i < width) {
				horiz[i][0] = true;
				horiz[i][height] = true;
			}
		}
		// Coordinates
		// (1,1)
		//(width - 1, height -1)
		createChamber(width, height, 1, 1, width - 1, height - 1);


	}

	public void opening(int x1, int y1, int x2, int y2, int [] randomErase) {
		int a = num.nextInt(3 - 0 + 1) + 0;
		if (a != 0) {
			int b = num.nextInt((randomErase[0] - 1) - (x1 - 1) + 1) + (x1 - 1);
			horiz[b][randomErase[1]] = false;
		}
		if (a != 1) {
			int c = num.nextInt((randomErase[1] - 1) - (y1 - 1) + 1) + (y1 - 1);
			vert[randomErase[0]][c] = false;
		}
		if (a != 2) {
			int d = num.nextInt(x2 - randomErase[0] + 1) + randomErase[0];
			horiz[d][randomErase[1]] = false;
		}
		if (a != 3) {
			int e = num.nextInt(y2 - randomErase[1] + 1) + randomErase[1];
			vert[randomErase[0]][e] = false;
		}

	}

	public void createChamber(int w, int h, int x1, int y1, int x2, int y2) {
		if (height > 1 && width > 1) {
			int [] randomErase = randomErases(w, h, x1, y1, x2, y2);
			opening(x1, y1, x2, y2, randomErase);
			createChamber(randomErase[0] - x1 + 1, randomErase[1] - y1 + 1, x1, y1, randomErase[0] - 1, randomErase[1] - 1);
			createChamber(x2 - randomErase[0] + 1, randomErase[1] - y1 + 1, randomErase[0] + 1, y1, x2, randomErase[1] -1);
			createChamber(x2 - randomErase[0] + 1, y2 - randomErase[1] + 1, randomErase[0] + 1, randomErase[1] + 1, x2, y2);

		}
	}

	public int [] randomErases(int w, int h, int x1, int y1, int x2, int y2) {
		int [] randomPoint = {num.nextInt(x2 - x1 + 1) + x1, num.nextInt(y2 - y1 + 1) + y1};
		while (h >= 1) {
			y2 = y2 - 1;
			vert[randomPoint[0]][y2] = true;
			h--;
		}

		while (w >= 1) {
			x2 = x2 - 1;
			horiz[x2][randomPoint[1]] = true;
			w--;
		}
		return randomPoint;
	}

	/**
	 * getWidth
	 * @return the width of this maze
	 */
	public int getWidth()
	{
		// TO DO
		return width;
	}

	/**
	 * getHeight
	 * @return the height of this maze
	 */
	public int getHeight()
	{
		// TO DO
		return height;
	}

	/**
	 * isNorthWall
	 * @param row the row identifier of a chamber
	 * @param column the column identifier of a chamber
	 * @return true if the chamber at row row and column column
	 * contain a north wall. Otherwise, return false
	 */
	public boolean isNorthWall(int row, int column)
	{
		// TO DO
		return horiz[column][row];
	}

	/**
	 * isEastWall
	 * @param row the row identifier of a chamber
	 * @param column the column identifier of a chamber
	 * @return true if the chamber at row row and column column
	 * contain an east wall. Otherwise, return false
	 */
	public boolean isEastWall(int row, int column)
	{
		// TO DO
		return vert[column + 1][row];
	}

	/**
	 * isSouthWall
	 * @param row the row identifier of a chamber
	 * @param column the column identifier of a chamber
	 * @return true if the chamber at row row and column column
	 * contain a south wall. Otherwise, return false
	 */
	public boolean isSouthWall(int row, int column)
	{
		// TO DO
		return horiz[column][row + 1];
	}

	/**
	 * isWestWall
	 * @param row the row identifier of a chamber
	 * @param column the column identifier of a chamber
	 * @return true if the chamber at row row and column column
	 * contain a west wall. Otherwise, return false
	 */
	public boolean isWestWall(int row, int column)
	{
		// TO DO
		return vert[column][row];
	}
}
