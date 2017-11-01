import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class Login extends JPanel {
  private JButton logined;

  public Login() {
    setLayout(new GridLayout(1,1));
    logined = new JButton("Login");
    add(logined);
    // What will happen if the user clicks on the login button?
    logined.addActionListener(new LoginButtonListener());
  }
}

// Placed the LoginButtonListener class within the Login class to make things more efficient.
class LoginButtonListener implements ActionListener {
  private int [] voterid;

  public void actionPerformed(ActionEvent e) {
    try {
      // reads the ballots.txt file with all the voter ids.
      Scanner console = new Scanner(new File("ballots.txt"));
      while (console.hasNextLine()) {
        int totalppl = console.nextInt();
        console.nextLine();
        voterid = new int[totalppl];
        for(int x = 0; x < totalppl; x++) {
          voterid[x] = console.nextInt();
          console.nextLine();
        }
      }
      // This part is just the action part. It shows what happens when you press the login button.
      // JOptionPanes appear and greet you prompting you to vote.
      String voter = JOptionPane.showInputDialog("Enter Voter ID: ");
      int number = Integer.parseInt(voter);
      for(int y = 0; y < voterid.length; y++) {
        if (number == voterid[y]) {
          JOptionPane.showMessageDialog(null, "Hello voter ID #" + number + ". Please make your choices.");
        }
      }
    }
    catch (FileNotFoundException d) {
      System.out.println("File not found.");
    }
  }
}
