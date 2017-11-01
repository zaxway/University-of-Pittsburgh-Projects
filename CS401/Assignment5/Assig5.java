import javax.swing.*;
import java.awt.*;
import java.util.*;

public class Assig5 extends JFrame{

  private Ballot ballot;
  private Ballot2 ballot2;
  private Login login;
  public int [] voterid;
  private CastVote castvote;

  //Constructor for creating the JFrame.

  public Assig5() {
    // Creates the JFrame
    setTitle("Title");
    setSize(500,200);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    // Program has 2 ballots
    ballot = new Ballot();
    ballot2 = new Ballot2();
    // Program has a login.
    login = new Login();
    //Program has a Cast your Vote button.
    castvote = new CastVote();
    // Adds the panels to the Frame.
    add(ballot, BorderLayout.WEST);
    add(ballot2, BorderLayout.CENTER);
    add(login, BorderLayout.NORTH);
    add(castvote, BorderLayout.SOUTH);
    pack();
    setVisible(true);
  }
  public static void main(String [] args) {
    new Assig5();
  }
}
