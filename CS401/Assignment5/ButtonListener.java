import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class ButtonListener implements ActionListener {
  private int [] vote;


  public void actionPerformed(ActionEvent e) {
    JButton button = (JButton) e.getSource();
    // Action Command will refer to the Buttons.
    String actionCommand = e.getActionCommand();
    // Creates 8 different votes, 4 votes for each ballot.
    vote = new int[8];
    // if user presses the "whatever String" button, then the color of the button will be changed
    // to red or blue and its vote will increment.
    if (actionCommand.equals("Oreo")) {
      button.setForeground(Color.RED);
      vote[0]++;
    }
    else if (actionCommand.equals("Chips Ahoy")) {
      button.setForeground(Color.RED);
      vote[1]++;
    }
    else if (actionCommand.equals("Sunny Select")) {
      button.setForeground(Color.RED);
      vote[2]++;
    }
    else if (actionCommand.equals("Mother's")) {
      button.setForeground(Color.RED);
      vote[3]++;
    }
    else if (actionCommand.equals("YOLO")) {
      button.setForeground(Color.BLUE);
      vote[4]++;
    }
    else if (actionCommand.equals("LOL")) {
      button.setForeground(Color.BLUE);
      vote[5]++;
    }
    else if (actionCommand.equals("IDK")) {
      button.setForeground(Color.BLUE);
      vote[6]++;
    }
    else if (actionCommand.equals("IKR")) {
      button.setForeground(Color.BLUE);
      vote[7]++;
    }
    else {
      button.setForeground(Color.BLACK);
    }
    // Creates an array of Strings that represent each of the buttons.
    String [] str = {"oreo", "chipsahoy", "sunnyselect", "mothers", "YOLO", "LOL", "IDK", "IKR"};
    // Makes a for loop that prints out the String and its number of votes.
    for(int q = 0; q < vote.length; q++) {
      System.out.println(str[q] + ": " + vote[q]);
    }
    // if (e.getSource() == button) {
    //   button.setForeground(Color.RED);
    // }
    // else {
    //   button.setForeground(Color.BLACK);
    // }
    System.out.println("Thanks for voting.");

  }
}
