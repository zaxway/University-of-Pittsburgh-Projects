import java.util.ArrayList;
import javax.swing.JFrame;

public class MazeFrame
{
	public static void main(String[] args) throws InterruptedException
	{
		int width = 15;
		int height = 10;
		JFrame frame = new JFrame();
		Maze maze = new Maze(width, height);
		ArrayList<Pair<Integer,Integer>> solution = new ArrayList<Pair<Integer,Integer>>();
		MazeComponent mc = new MazeComponent(maze, solution);
		frame.setSize(800,800);
		frame.setTitle("Maze");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(mc);
		frame.setVisible(true);
		solution.add(new Pair<Integer,Integer>(0,0));
		Thread.sleep(1000);
		solveMaze(solution, mc, maze, 0, 0, 0, 0);
		mc.repaint();
	}

	/** Solve Maze: recursively solve the maze
	 *
	 * @param solution   : The array list solution is needed so that every recursive call,
	 *                     a new (or more) next position can be added or removed.
	 * @param mc         : This is the MazeComponent. We need that only for the purpose of
	 *                     animation. We need to call mc.repaint() every time a new position
	 *                     is added or removed. For example,
	 *                       :
	 *                     solution.add(...);
	 *                     mc.repaint();
	 *                     Thread.sleep(sleepTime);
	 *                       :
	 *                     solution.remove(...);
	 *                     mc.repaint();
	 *                     Thread.sleep(sleepTime);
	 *                       :
	 * @param maze       : The maze data structure to be solved.
	 * @return a boolean value to previous call to tell the previous call whether a solution is
	 *         found.
	 * @throws InterruptedException: We need this because of our Thread.sleep(50);
	 */
	public static boolean solveMaze(ArrayList<Pair<Integer,Integer>> solution, MazeComponent mc, Maze maze, int r, int c, int pr, int pc) throws InterruptedException
	{
		// TO DO
		if (r == height - 1 && r -1 = pr) {
			return true;
		}
		else {
			if (isNorthWall(r,c) && (r - 1) == pr) {
				// move north
				boolean p = solveMaze(solution, mc, maze, r - 1, c, r, c);
				if(p) {
					return true;
				}
				else {
					// move back from north
					return;
				}
			}
			if (isSouthWall(r,c) && (r - 1) == pr) {
				// move north
				boolean p = solveMaze(solution, mc, maze, r - 1, c, r, c);
				if(p) {
					return true;
				}
				else {
					// move back from south
					return false;
				}
			}if (isWestWall(r,c) && (r - 1) == pr) {
				// move north
				boolean p = solveMaze(solution, mc, maze, r - 1, c, r, c);
				if(p) {
					return true;
				}
				else {
					// move back from west
					return false;
				}
			}
			if (isEastWall(r,c) && (r - 1) == pr) {
				// move north
				boolean p = solveMaze(solution, mc, maze, r - 1, c, r, c);
				if(p) {
					return true;
				}
				else {
					// move back from east
					return false;
				}
			}
		}
		return false;

	}
}
