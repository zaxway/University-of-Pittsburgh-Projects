import javax.swing.JFrame;

public class THSolverFrame
{
	public static void main(String[] args) throws InterruptedException
	{
		int numberOfDiscs = 10;
		TowerOfHanoi towers = new TowerOfHanoi(numberOfDiscs);
		THComponent thc = new THComponent(towers);


		JFrame frame = new JFrame();
		frame.setTitle("Tower of Hanoi");
		frame.setSize(500,500);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		int fromTowers = 0;
		int toTowers = 2;
		int helpTower = 1;

		frame.add(thc);

		frame.setVisible(true);

		Thread.sleep(5000);

		solveTower(towers, thc, numberOfDiscs, fromTowers, toTowers, helpTower);

		System.out.println("DONE!!!");
	}

	public static void solveTower(TowerOfHanoi towers, THComponent thc, int numberOfDiscs, int fromTowers, int toTowers, int helpTower) throws InterruptedException
	{
		// TO DO
		if (numberOfDiscs == 1) {
			moveTopDisc(fromTowers, toTowers);
			thc.repaint();
			Thread.sleep(100);
		}
		else {
			solveTower(towers, thc, numberOfDiscs - 1, fromTowers, helpTower, toTowers);
			solveTower(towers, thc, 1, fromTowers, toTowers, helpTower);
			solveTower(towers, thc, numberOfDiscs - 1, fromTowers, toTowers, helpTower);
		}
	}
}
